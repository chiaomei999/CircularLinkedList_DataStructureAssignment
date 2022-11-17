
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <ctime>
#include <iostream>
#include <random> //亂數函式庫
using namespace std;

typedef struct node
{
	int data;
	struct node *next;
}Node;

void add_node(Node **start, int value);
void print_list(Node *node);
void free_list(Node *node);
int list_length(Node *head);
void deleteNode(Node** head, int key, int length);
node *bomb(struct node* head, int SendPeople);

/*
node joiner_list(int JoinPeople);

node joiner_list(int JoinPeople)
{
  int newData = 1;
  for( int i=0; i<JoinPeople ; i++ ){  
    add_node(&head, newData);
    newData += 1;
  }
}
*/


void add_node(Node **start, int value)
{
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node -> data = value;
	new_node -> next = NULL;
	
	if(*start == NULL) {
		*start = new_node;
		(*start)->next = *start;
		return;
	}
	else {
		Node *current;	
		current = *start;
		while(current->next != *start) {
			current = current->next;
		}
		current->next = new_node;
		new_node->next = *start;
		return;
	}
}

void print_list(Node *node)
{
	Node *first_node = node;
  cout << node->data << "->";
	//printf("%d ", node->data);
	node = node->next; 
	
	while(node != NULL) {
		if(node == first_node) break;
    cout << node->data << "->";
		//printf("%d ", node->data); 
		node = node->next;
	}
	//printf("%d\n", node->data);
  cout << node->data << "\n";
}

void free_list(Node *node) //不確定有沒有用到?
{
	int total_node = 1;
	Node *first = node;
	node = node->next;
	while(node != first) {
		node = node->next;
		total_node++;
	}

	Node *current = first;
	Node *temp;
	int i;
	for(i = 0; i < total_node; i++) {
		temp = current;
		current = current->next;
		free(temp);
	}
}

int list_length(Node *head)
{
  // function to calculate the current length of the circular linked list
  Node *t;
  int i = 0;
  if (head == NULL){
    // handle underflow condition
    return 0;
  }
  t = head -> next;
  do
  {
    // handle traversal through the list t = t -> next; i++; 
    return i;
  }while (t != head -> next);
}

node *bomb(struct node * head, int SendPeople)
{
  int len = list_length(head);
  int count = 0;
  int r = rand() % 5;  //0.4的爆炸機率，餘數 {0,1} 爆炸
  struct node *prev = head, *temp = prev -> next;

  //傳炸彈
  while(count < SendPeople-1) //0<2-1  2-1結束
  {
    prev = prev -> next; //1指向2
    temp = temp -> next; //2指向3 死者將為3
    head = prev; //head = 2
    count += 1; //1
  }

  //引爆與否
  if( r <=1 ) //沒爆
  {
    prev = temp; //prev 2指向3
    temp = temp -> next; //temp 3指向4
    head = prev; //head 2指向3
    return head; //head = 3 從3開始繼續傳
  }
  else //爆炸 (3消失)
  {
    head = temp -> next; //head 2指向4
    prev -> next = temp -> next; //prev 2指向4
    temp = prev -> next; //temp 3指向5
    return head; //從 4 開始傳球
  }
}


int main(int argc, char* argv[])
{
	// create first node "head"
	Node *head = NULL;
  int JoinPeople = 0;
  //int len = list_length(head);

  cout << "炸死倒楣鬼遊戲開始\n總共幾人參加?(請輸入4-10): ";
  cin >> JoinPeople;
  //joiner_list(JoinPeople);

  //生成Circular Linked List
  int newData = 1;
  for( int i=0; i<JoinPeople ; i++ ){  
    add_node(&head, newData);
    newData += 1;
  }

  //如果人數剩下超過1人(head!=tail)
  while( head != head -> next ){
    //目前的 circular linked list 內容
    cout << "Before: ";
    print_list(head);
    
    int SendPeople = 0;
    cout << "炸彈在" << head -> data << "號手上，要往下傳幾人: ";
    // random 往下傳的人數 0-3，還沒寫完～～
    //int SendPeople = rand() % 4;
    cin >> SendPeople ;
    
    head = bomb(head, SendPeople);
    cout << "After: ";
    print_list(head); 
    cout << "------" << endl;
  }
  cout << "最後生存者為:" << head -> data << endl;

	free_list(head);  //結束程式前，釋出記憶體
	
	return 0;	
}

