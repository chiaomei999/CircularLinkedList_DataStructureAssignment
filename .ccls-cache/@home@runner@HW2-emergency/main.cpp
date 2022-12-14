
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <ctime>
#include <iostream>
#include <random> //亂數函式庫
using namespace std;

typedef struct node
{
  public:
  	int data;
  	struct node *next;
    struct node *head;
    struct node *dead;
    int len;
}Node;

void add_node(Node **start, int value);
void print_list(Node *node);
void free_list(Node *node);
int list_length(Node *head);
node *bomb(Node *head, int SendPeople, Node *dead, int len);
node *dead_node(Node *dead, int newvalue);



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

int list_len(int len)
{}

int list_length(Node *head)
{
  // function to calculate the current length of the circular linked list
  Node *t = head -> next; //head = 1, t = 2
  int i = 0;
  while( t != head )
  {
    head = head -> next; //當 head 指到1
    i += 1;
  }
  return i;

  /*
  t = head -> next;
  do
  {
    // handle traversal through the list t = t -> next; i++; 
    return i;
  }while (t != head -> next);
  */
}

node *bomb(Node *head, int SendPeople, Node *dead, int len)
{
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
    //int len = list_length(head); //人數不對
    head = temp -> next; //head 2指向4
    prev -> next = temp -> next; //prev 2指向4

    len -= 1;
    cout << "●炸彈爆炸●"　<< temp -> data << "號出局，還剩" << len << "人" << endl;

    //把死者存入死亡筆記本
    //dead_node(dead, temp -> data);  這行跟這個function出問題

    temp = prev -> next; //temp 3指向5, 死者3消失

    return head; //從 4 開始傳球
  }
}

node *dead_node(Node *dead, int newvalue) //還沒改完
{
	Node *newdead_node = NULL;
  dead -> next = newdead_node;
	newdead_node -> data = newvalue;
	newdead_node -> next = NULL;

  return dead;	
}


int main(int argc, char* argv[])
{
	// create first node "head"
	Node *head = NULL; //存生者
  Node *dead = NULL; //存死者
  int JoinPeople = 0;
  int len = 0;

  cout << "炸死倒楣鬼遊戲開始\n總共幾人參加?(請輸入4-10): ";
  cin >> JoinPeople;
  //joiner_list(JoinPeople);
  len = JoinPeople;
  cout << "len now is : " << len << endl; 


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
    SendPeople = rand() % 4;     // random 往下傳的人數 0-3
    cout << SendPeople << endl;

    //int len = list_length(head); //數不到正確人數
    
    
    head = bomb(head, SendPeople, dead, len);
    cout << "After: ";
    print_list(head); 
    cout << "現在剩下" << len << "人" << endl;
    cout << "------" << endl;
  }
  cout << "最後生存者為:" << head -> data << endl;
  cout << "死亡筆記本: ";
  print_list(dead);

	free_list(head);  //結束程式前，釋出記憶體
	
	return 0;	
}

