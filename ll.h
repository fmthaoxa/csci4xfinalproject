#include <iostream>
using namespace std;

struct node {
	int data;
	node *next;
};

class list {
Private:
	node *head, *tail;
Public:
	list(){
		head = NULL;
		tail = NULL;
	}

};

//new node at end of LL
void createnode(int value){
	node *temp=new node;
	temp -> data=value;
	temp -> next=NULL;
	if(head==NULL){
		head=temp;
		tail=temp;
		temp=NULL;
	}
	else{
		tail -> next=temp;
		tail=temp;
	}
}

//displaying the list
void display() {
	node *temp=new node;
	temp=head;
	while(temp != NULL){
		cout << temp -> data << "\t";
		temp=temp -> next;
	}
}

//insert at start
void insert_start(int value) {
	node *temp=new node;
	temp -> data=value;
	temp -> next=head;
	head=temp;
}

//insert at any position
void insert_position(int pos, int value) {
	node *pre=new node;
	node *cur=new node;
	node *temp=new node;
	cur=head;
	for(int i=1; i < pos; i++) {
		pre=cur;
		cur=cur -> next;
	}
	temp -> data=value;
	pre -> next=temp;
	temp -> next=cur;
}

//delete first node
void delete_first()
{
	node *temp=new node;
	temp=head;
	head=head->next;
	delete temp;
}

//delete last node
void delete_last()
{
	node *current=new node;
	node *previous=new node;
	current=head;
	while(current->next!=NULL)
	{
		previous=current;
		current=current->next;	
	}
	tail=previous;
	previous->next=NULL;
	delete current;
}


//delete anywhere
void delete_position(int pos)
{
	node *current=new node;
	node *previous=new node;
	current=head;
	for(int i=1;i<pos;i++)
	{
		previous=current;
		current=current->next;
	}
	previous->next=current->next;
}
