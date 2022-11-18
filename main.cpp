
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
    int JoinPeople;
    int DeadArr;
}Node;

void add_node(Node **start, int value);
void print_list(Node *node);
void free_list(Node *node);
int countNodes(Node* head);
node *bomb(Node *head, int SendPeople, Node *dead, int JoinPeople, int DeadArr[10]);
void dead_list(Node *head, int JoinPeople, int newDead, int DeadArr);


void dead_list(Node *head, int JoinPeople, int newDead, int DeadArr[10])
{
  int index;
  index = JoinPeople - countNodes(head); //死亡人數=參與遊戲人數-存活人數
  DeadArr[index] = newDead;
}

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
	node = node->next; 
	
	while(node != NULL) {
		if(node == first_node) break;
    cout << node->data << "->";
		node = node->next;
	}
  cout << node->data << "\n";
}

void free_list(Node *node)
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

int countNodes(Node* head)
{
    Node* temp = head;
    int result = 0;
    if (head != NULL) {
        do {
            temp = temp->next;
            result++;
        } while (temp != head);
    }
  
    return result;
}

node *bomb(Node *head, int SendPeople, Node *dead, int JoinPeople, int DeadArr[])
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
    
    cout << "炸彈沒有爆炸，還剩" << countNodes(head) << "人" << endl;
    return head; //head = 3 從3開始繼續傳
  }
  else //爆炸 (3消失)
  {
    head = temp -> next; //head 2指向4
    prev -> next = temp -> next; //prev 2指向4

    cout << "QQ炸彈爆炸" << temp -> data << "號出局，還剩" << countNodes(head) << "人" << endl;

    //把死者存入死亡筆記本
    dead_list( head, JoinPeople, temp -> data, DeadArr);

    temp = prev -> next; //temp 3指向5, 死者3消失

    return head; //從 4 開始傳球
  }
}


int main(int argc, char* argv[])
{
	// create first node "head"
	Node *head = NULL; //存生者
  Node *dead = NULL; //存死者
  int JoinPeople = 0;
  int PlayCount = 0; //遊戲回合數
  int DeadArr[10] = {};

  cout << "總共幾人參加?(請輸入4-10): ";
  cin >> JoinPeople;
  cout << "炸死倒楣鬼遊戲開始！" << endl << "-----" <<endl;

  //生成Circular Linked List 參加者序號與名單
  int newData = 1;
  for( int i=0; i<JoinPeople ; i++ ){  
    add_node(&head, newData);
    newData += 1;
  }
    
  //如果人數剩下超過1人(head!=tail)
  while( head != head -> next ){
    //目前的 circular linked list 內容
    PlayCount += 1;
    cout << "目前玩家順序: ";
    print_list(head);
    
    int SendPeople = 0;
    SendPeople = rand() % 4;     // random 往下傳的人數 0-3
    cout << "第" << PlayCount << "回合，由" << head -> data << "開始，往下傳給" << SendPeople << "位玩家" << endl;
    
    head = bomb(head, SendPeople, dead, JoinPeople, DeadArr);
    cout << "------" << endl;
  }
  cout << "最後生存+獲勝者:" << head -> data << endl;
  cout << "死亡順序筆記本: ";
  for( int i=1; i <= JoinPeople -1; i++)
    {
        cout << DeadArr[i] << "->";
    }

	free_list(head);  //結束程式前，釋出記憶體
	return 0;	
}

