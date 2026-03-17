//
//  main.c
//  Magic Leak Detection
//
//  Created by Akin Korkmaz on 9/18/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct board board;
typedef struct Node Node;
typedef struct linkedList linkedList;
typedef struct Queue queue;
typedef struct point point;

struct point {
    long long xPos;
    long long yPos;
};

struct Node {
    point value;
    Node * next;
};

struct linkedList {
    Node * head;
    Node * tail;
};

struct Queue {
    linkedList * LL;
};

struct board {
    char * arr;
    int * regionMap;
};

// ***Function Declarations***
long long magicpaircalculation(long long pairs);
board * InitBoard(board * inputRune, long long rows, long long column);

Node * createNode(point value);
void addTail(linkedList * linkedList, point value);
void removeHead(linkedList * linkedList);

point getfirst(queue * que);
void enqueue(queue * que, point value);
void dequeue(queue * que);


void floodFill(board * board, long long regionCount, long long * dotPerRegion, point startPoint, queue * que, long long rows, long long column){
    
    enqueue(que, startPoint);
    board[startPoint.xPos].regionMap[startPoint.yPos] = regionCount;
    dotPerRegion[regionCount]++;
    
    while (que->LL->head != NULL) {
        point p = getfirst(que);
        dequeue(que);
        
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        
        for (int i = 0; i < 4; i++) {
            long long nx = p.xPos + dx[i];
            long long ny = p.yPos + dy[i];
            
            if (nx >= 0 && nx < rows && ny >= 0 && ny < column) {
                if (board[nx].arr[ny] == '.' && board[nx].regionMap[ny] == 0) {
                    board[nx].regionMap[ny] = regionCount;
                    dotPerRegion[regionCount]++;
                    
                    point newP = {nx, ny};
                    enqueue(que, newP);
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {

    ///------------------------
    ///       #Variables#
    ///------------------------
    long long finalResult = 0;
    long long XaroundMagic = 0;
    long long XaroundMagicMax = 0;
    int xcount = 0;
    long long pairs;
    long long rows = 0;
    long long column = 0;
    point point = {0,0};
    queue * que = (queue*) malloc(sizeof(queue));
    que->LL = (linkedList*) malloc(sizeof(linkedList));
    que->LL->head = NULL;
    que->LL->tail = NULL;
    int RegionCount = 1;
    board * inputRune = NULL;
    ///------------------------
    
    ///--------------------------------------------
    ///       #Initialization and Get Board#
    ///--------------------------------------------

    //step 1 - get the dimensions of the rune
    if(scanf("%llu", &rows) != 1) return 1;
    if(scanf("%llu", &column) != 1) return 1;
    
    //step 2 - initialize the board
    //memorry allocation and setting all char values to #
    inputRune = InitBoard(inputRune, rows, column);
    
    long long * dotPerRegion = (long long*) calloc((rows * column) + 2, sizeof(long long));
    bool * bestXVisited = (bool*) calloc((rows * column) + 2, sizeof(bool));
    
    //consumes the last \n char from the last scanf input
    getchar();
    
    //step 3 - get the board input from the console
    for (int i = 0; i < rows; i++) {
        fgets(inputRune[i].arr, (int)column + 2, stdin);
    }
    ///--------------------------------------------
    
    ///--------------------------------------------------------
    ///       #Fill All Regions with ZoneID[index] array#
    ///--------------------------------------------------------
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < column; j++) {
            
            if (inputRune[i].arr[j] == '#') {
                continue;
            }
            
            if (inputRune[i].arr[j] == '.' && inputRune[i].regionMap[j] == 0) {
                
                point.xPos = i;
                point.yPos = j;
                
                //calls floodfill function for the . found
                floodFill(inputRune, RegionCount, dotPerRegion, point, que, rows, column);
                
                RegionCount++;
            }
        }
    }

    ///-----------------------------------------------------------
    ///       #Finds the Number of X's with their Cordinates#
    ///-----------------------------------------------------------
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < column; j++) {
            if (inputRune[i].arr[j] == 'X') {
                xcount++;
                
                bool * visitedInThisX = (bool*) calloc(RegionCount + 1, sizeof(bool));
                long long currentXTotal = 1;
                
                int dx[] = {0, 0, -1, 1};
                int dy[] = {1, -1, 0, 0};
                
                for (int k = 0; k < 4; k++) {
                    long long ni = i + dx[k];
                    long long nj = j + dy[k];
                    
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < column) {
                        int reg = inputRune[ni].regionMap[nj];
                        
                        if (reg > 0 && !visitedInThisX[reg]) {
                            currentXTotal += dotPerRegion[reg];
                            visitedInThisX[reg] = true;
                        }
                    }
                }
                
                XaroundMagic = magicpaircalculation(currentXTotal);
                
                if (XaroundMagic > XaroundMagicMax) {
                    XaroundMagicMax = XaroundMagic;
                    
                    for (int y = 1; y < RegionCount; y++) {
                        bestXVisited[y] = visitedInThisX[y];
                    }
                }
                
                free(visitedInThisX);
            }
        }
    }
    
    for (int i = 1; i < RegionCount; i++) {
        if (bestXVisited[i] == false) {
            finalResult += magicpaircalculation(dotPerRegion[i]);
        }
    }
    
    ///-----------------------------------------------------------
    ///       #Frees all allocations#
    ///-----------------------------------------------------------
    for (int i = 0; i < rows; i++) {
        free(inputRune[i].arr);
        free(inputRune[i].regionMap);
    }
    
    free(inputRune);
    free(dotPerRegion);
    free(bestXVisited);
    free(que->LL);
    free(que);
    ///-----------------------------------------------------------
    
    printf("%llu\n", finalResult + XaroundMagicMax);
    
    return 0;
}

//calculates the magic amount for pairs number of connections
long long magicpaircalculation(long long pairs){
    return pairs * (pairs + 1) / 2;
}

//function to allocate memmory and initialize the values of the board
board * InitBoard(board * inputRune, long long rows, long long column){
    //allocates a array with rows number of size.
    inputRune = (board*) calloc(rows, sizeof(board));
    
    for (int i = 0; i < rows; i++) {
        inputRune[i].arr = (char*) calloc(column + 2, sizeof(char));
        inputRune[i].regionMap = (int*) calloc(column + 2, sizeof(int));
    }
    
    //initializes all values to #
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < column; j++) {
            inputRune[i].arr[j] = '#';
        }
    }
    
    //returns the initialized rune
    return inputRune;
}

Node * createNode(point value){
    Node * newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    
    return newNode;
}

void addTail(linkedList * linkedList, point value){
    Node * newTail = createNode(value);
    if (linkedList ->head == NULL){
        linkedList->tail = NULL;
        linkedList->head = linkedList->tail = newTail;
        return;
    }
    
    linkedList->tail->next = newTail;
    linkedList->tail = newTail;
}

void removeHead(linkedList * linkedList){
    if (linkedList->head == NULL) {
        return;
    }
    
    if (linkedList->head->next == NULL) {
        free(linkedList->head);
        linkedList->head = linkedList->tail = NULL;
        return;
    }
    
    Node * newHead = linkedList->head->next;
    free(linkedList->head);
    linkedList->head = newHead;
}

point getfirst(queue * que){
    return que->LL->head->value;
}

void enqueue(queue * que, point value){
    addTail(que->LL, value);
}

void dequeue(queue * que){
    removeHead(que->LL);
}
