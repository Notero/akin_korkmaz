#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define ROW 6
#define COL 5
typedef struct Node Node;
typedef struct LL LL;
typedef struct Queue Queue;
struct Node {
Node * next;
int value;
};
struct LL {
Node * head, * tail;
};
struct Queue {
LL list;
};
// Linked List prototypes
Node * createNode(int value);
void addToTail(LL * list, int value);
void removeHead(LL * list);
// Queue prototypes
void enqueue(Queue * q, int value);
void dequeue(Queue * q);
int front(Queue * q);
// Linked List function
Node * createNode(int value) {
Node * res = (Node *) malloc(sizeof(Node));
res->value = value;
res->next = NULL;
return res;
}
void addToTail(LL * list, int value) {
Node * newTail = createNode(value);
// 0 Node list case
if (list->head == NULL) {
assert(list->tail == NULL);
list->head = list->tail = newTail;
return;
}
// Make the old tail point to the new one
list->tail->next = newTail;
// Update the tail stored in the list
list->tail = newTail;
}
void removeHead(LL * list) {
// 0 Node list case
if (list->head == NULL) {
return; // WHY ARE YOU REMOVING!?!?
}
// 1 Node list case
if (!list->head->next) {
free(list->head);
// list->head->???
// *list->head
// list->head[#]
list->head = list->tail = NULL;
return;
}
// 2 or more Node list case
Node * newHead = list->head->next;
free(list->head);
list->head = newHead;
}
// Queue Functions
void enqueue(Queue * q, int value) {
addToTail(&(q->list), value);
}
void dequeue(Queue * q) {
removeHead(&(q->list));
}
int front(Queue * q) {
return q->list.head->value;
}
void printVisited(int grid[][COL], char map[][COL+1]) {
for (int i = 0; i < ROW; i++) {
for (int j = 0; j < COL; j++) {
if (map[i][j]=='x')
printf("#");
else
printf("%d", grid[i][j]);
}
printf("\n");
}
printf("\n");
}
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
// The main
int main() {
// Initialize
// Start and End
int str = 0;
int stc = 4;
int enr = 4;
int enc = 0;
// Queue
Queue q;
q.list.head = q.list.tail = NULL;
enqueue(&q, str);
enqueue(&q, stc);
// Make a map
char map[ROW][COL + 1] = {
"_x_x_",
"xxxx_",
"____x",
"xxx__",
"__x__",
"__x__"
};
// Make a visited grid
int visited[ROW][COL];
for (int i = 0; i < ROW; i++) {
for (int j = 0; j < COL; j++) {
visited[i][j] = 0;
}
    
}
visited[str][stc] = 1; // visit the first location
// Flood loop
while (q.list.head) {
// Get the current location
int curR = front(&q); dequeue(&q);
int curC = front(&q); dequeue(&q);
visited[curR][curC] = 2;
printVisited(visited, map);
// Try all possible direction
for (int i = 0; i < 8; i++) {
int newR = curR + dx[i];
int newC = curC + dy[i];
// bounds check (invalid cases will continue)
if (newR >= ROW) continue;
if (newC >= COL) continue;
if (newR < 0) continue;
if (newC < 0) continue;
// wall check
if (map[newR][newC] == 'x') continue;
// visited check
if (visited[newR][newC]) continue;
enqueue(&q, newR);
enqueue(&q, newC);
visited[newR][newC] = 1;
}
visited[curR][curC] = 3;
}
// Read out the results
if (visited[enr][enc]) {
printf("Flooded..\n");
} else {
printf("SAFE!!!\n");
}
// Clean up memory
// NO DYNAMIC MEMORY :D
// Exit
return 0;
}
