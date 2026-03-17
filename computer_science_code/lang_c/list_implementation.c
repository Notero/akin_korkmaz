//
//  main.c
//  List
//
//  Created by Akin Korkmaz on 8/28/24.
//

#include <stdio.h>
#include <stdlib.h>

//use it like this
typedef struct Node Node;
typedef struct LL LL;

//there is the data part and it also has a node pointer which will ultimately will be the next node in the list
struct Node{
    int data;
    Node * next;
};
//list is going tobe empty if head address is NULL
//this is a Linked List so that it can keep Node addresses
struct LL{
    Node * head, * tail;
};

void addToTail(LL * list, int value);
void addToHead(LL * list, int value);
void printList(LL * list);


// Should add to the given list a node containing the value as the new head of the list
void addToHead(LL * list , int value){
    
    Node * newHead = (Node *) malloc(sizeof(Node));
    if (list -> head == NULL)
    {
        //empty list
        newHead-> next  = list->head;
        list->head = newHead;
        newHead -> data = value;
    }else 
    {
        //non empty list
        newHead -> next = list->head;
        list -> head    = newHead;
        newHead -> data = value;
    }
    
}

void addToTail(LL * list, int value){
    Node * newTail = (Node *) malloc(sizeof(Node));
    newTail->data = value;
    newTail->next = NULL;
    if (list->head == NULL) {
        //empty list
        
        list->head = newTail;
    }else{
        //finds the old tail of the list
        Node * oldtail;
        oldtail = list->head;
        while (oldtail->next) {
            oldtail = oldtail->next;
        }
        
        //link the old and new tail
        oldtail->next   = newTail;
    }
}

void printList(LL * list){
    Node * walker = list->head;
    while(walker){
        printf("%d -> ", walker->data);
        walker  = walker->next;
    }
    printf("NULL");
}
void freelist(LL list){
    Node * walker = list.head;
    while(walker)
    {
        Node * next = walker->next;
        free(walker);
        walker = next;
    }
}


int main(int argc, const char * argv[]) {
    
    LL akin;
    int x = 0;
    while(x != 3){
        
        x++;
    }
    printList(&akin);
    
    freelist(akin);
    
    return 0;
}
