//
//  main.c
//  Tries
//
//  Created by Akin Korkmaz on 11/21/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//typdef
typedef struct Trie Trie;
//Function Declarations
Trie* createNode(void);
void insertWord(Trie* currNode, char *word, int weight, int index);
int searchWord(Trie* currNode, char *word, int index);
Trie* getNode(Trie* currNode, char *word, int index);
long getHighestChildrenWeight(Trie* root);
void freeTrie(Trie* root);

struct Trie {
    long weight;
    Trie* next[26];
};

int main(int argc, const char * argv[]) {
    
    //Variables
    Trie* root = createNode();
    Trie* tempTrie = NULL;
    long temp = 0;
    int tempIndex = 0;
    int commandCount = 0;
    int command = 0;
    char word[2000002];
    int weight = 0;
    //gets the amounf of inputs
    scanf("%d", &commandCount);
    //loop to get all command inputs
    for (int i = 0; i < commandCount; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                //gets word and frequency
                scanf("%s", word);
                scanf("%d", &weight);
                //inserts with frequency cummulatively
                insertWord(root, word, weight, 0);
                break;
            case 2:
                //gets word
                scanf("%s", word);
                
                temp = 0;
                
                //checks if the word exists if so get the last Node for the last letter
                if(searchWord(root, word, 0) == 1){
                    tempTrie = getNode(root, word, 0);
                    //finds the max weight among all children of the node
                    temp = getHighestChildrenWeight(tempTrie);
                }else {
                        printf("unrecognized prefix");
                }
                
                if (temp == 0 && searchWord(root, word, 0) == 1) {
                    printf("unrecognized prefix");

                }
                
                //loops trough children
                for (int i = 0; i < 26; i++) {
                    //checks if children exist and weight of that children is max
                    if (tempTrie->next[i] && temp == tempTrie->next[i]->weight) {
                        //reverse index to ascii value
                        tempIndex = i + 'a';
                        printf("%c",tempIndex);
                    }
                }
                //new line for next code
                printf("\n");
                break;
            default:
                break;
        }
    }
    //frees the trie from root
    freeTrie(root);
    
    return 0;
}
//creates and initalizes a Node
Trie* createNode(void){
    
    Trie* root = (Trie*) malloc(sizeof(Trie));
    
    root->weight = 0;
    
    for (int i = 0; i < 26; i++) {
        root->next[i] = NULL;
    }
    
    return root;
}
//Inserts word and accumulatively adds weight to all possible strings
void insertWord(Trie* currNode, char *word, int weight, int index){
    
    //exits when node for last char created
    if (index == strlen(word)) {
        currNode->weight += weight;
        return;
    }
    
    //add weight to all string possiblities other than root
    if (index > 0) {
        currNode->weight += weight;
    }
    
    //gets next index value of the next node;
    int tempIndex = word[index] - 'a';
    
    //creates a node if no node present
    if (currNode->next[tempIndex] == NULL) {
        currNode->next[tempIndex] = createNode();
    }
    
    //continues recursion
    insertWord(currNode->next[tempIndex], word, weight, index+1);
}
//search if a word exist or not
int searchWord(Trie* currNode, char* word, int index){
    if (index == strlen(word)) {
        if (currNode->weight >= 1) {
            return 1; //success
        }
    }
    //Get next to check if Null
    int tempIndex = word[index] - 'a';
    if (currNode->next[tempIndex] == NULL) {
        return 0; //fail
    }
    
    return searchWord(currNode->next[tempIndex], word, index+1);
}

Trie* getNode(Trie* currNode, char *word, int index){
    
    if (index == strlen(word)) {
        return currNode;
    }
    
    int tempIndex = word[index] - 'a';
    
    return getNode(currNode->next[tempIndex],word,index+1);
}

//gets the highest weight most possible letter(s)
long getHighestChildrenWeight(Trie* root){
    
    long currWeight = 0;
    
    for (int i = 0; i < 26; i++) {
        if (root->next[i]) {
            if (currWeight < root->next[i]->weight) {
                currWeight = root->next[i]->weight;
            }
        }
    }
    
    return currWeight;
}
//frees Trie
void freeTrie(Trie* tree) {
    
    for (int i = 0; i < 26; i++){
        if (tree->next[i] != NULL) {
            freeTrie(tree->next[i]);
        }
    }
    free(tree);
}
