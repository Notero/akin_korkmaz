/* COP 3502C Assignment 5
This program is written by: Akin Korkmaz */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//struct def
typedef struct Node Node;
//function declaration
Node *createNode(char *name, int fine);
Node *insertToTree(Node *root, Node *insertable, int depth);
Node *searchTree(Node *root, char *name);
int getHeight(Node *root);
void updateDepthAndHeight(Node *node);
Node *parent(Node *root, Node *child);
Node* deleteNode(Node* root, char* name);
Node* deduct(Node *root, char *name, int fine);
void freeTree(Node *root);
double add(Node *current_ptr);
int addlexi(Node *current_ptr, char *name);
double numnodes(Node *root);

//struct of Node
struct Node {
    //data
    char name[27];
    int fine;
    //childs
    Node *rChild;
    Node *lChild;
    //parent pointer
    Node *parent;
    //height and depth of a Node
    int height;
    int depth;
};

int main(int argc, const char * argv[]) {
   
    //Variables
    Node *root = NULL;
    Node *temp = NULL;
    int commandCount = 0;
    char nameinput[27];
    int currFineAmount = 0;
    char input[14];
    double sumAll;
    double nodeCount = 0;
    double average = 0.00;
    int lexisum = 0;
    
    
    //gets the amount of commands
    scanf("%d", &commandCount);
    
    //loop to get all commands
    for (int i = 0; i < commandCount; i++) {
        
        //gets the first command
        scanf("%s", input);
        
        //if statements to act as a string switch for commands
        if (strcmp(input, "add") == 0) {
            
            //gets the name and the fine amount of an entry from console
                scanf("%s %d", nameinput, &currFineAmount);
            
            //creates the said node and inserts it into the Binary Search Tree (BST)
                root = insertToTree(root, createNode(nameinput, currFineAmount), 0);
            
            //finds the node as inserted amount might not be the actual amount
                Node *printable = searchTree(root, nameinput);
            
            //prints according to the assignment guidelines
                printf("%s %d %d\n",printable->name,printable->fine,printable->depth);
            
        }else if (strcmp(input, "deduct") == 0) {
            //gets the name and amount to deduct from console
            scanf("%s %d", nameinput, &currFineAmount);
            //calls deduct function -> deduct function will call delete function if deducted amount is lower than 0
            root = deduct(root, nameinput, currFineAmount);
            
        }else if (strcmp(input, "search") == 0) {
            
            scanf("%s", nameinput);
            //search the node by name and save it to temp Node
            temp = searchTree(root, nameinput);
            //checks if temp found or not and prints appropriate lines
            if (temp != NULL) {
                printf("%s %d %d\n", temp->name, temp->fine, temp->depth);
            }else{
                printf("%s not found\n", nameinput);
            }
            
        }else if (strcmp(input, "average") == 0) {
            //gets the amount of node
            nodeCount = numnodes(root);
            //gets sum of all nodes
            sumAll = add(root);
            //calculates average from 2 doubles which will %100 give double
            average = sumAll/nodeCount;
            //prints out
            printf("%.2lf\n",average);
            
        }else if (strcmp(input, "height_balance") == 0) {
            //gets the height of the roots children
            int lHeight = getHeight(root->lChild);
            int rHeight = getHeight(root->rChild);
            //checks if they are equal and prints out balanced or not balanced
            if (lHeight == rHeight) {
                    printf("left height = %d right height = %d balanced\n", lHeight, rHeight);
                } else {
                    printf("left height = %d right height = %d not balanced\n", lHeight, rHeight);
                }
            
            
        }else if (strcmp(input, "calc_below") == 0) {
            //gets the name to calculate below
            scanf("%s", nameinput);
            //call addlexi function to add every value that has a lower lexicographical order
            lexisum = addlexi(root, nameinput);
            //print out
            printf("%d\n",lexisum);
        }
        
    }
    //frees the tree
    freeTree(root);
    
    return 0;
}

//creates a node with struct specifications
Node *createNode(char *name, int fine){
    //assign mem
    Node *temp = (Node*)malloc(sizeof(Node));

    //put the name and the fine into the node init all others
    strcpy(temp->name, name);
    temp->fine = fine;
    temp->rChild = NULL;
    temp->lChild = NULL;
    temp->parent = NULL;
    temp->height = 0;
    temp->depth = 0;
    
    return temp;
}

//search the tree lexicographically which is how insertion is handled
Node *searchTree(Node *node, char *name){
        
    //base case
    if (node == NULL) {
        return NULL;
    }
    //compares node->name to name to see if they are equal if so returns node
    if (strcmp(node->name, name) == 0) {
        return node;
    }
    //checks which string is higher lexicographically
    int c = strcmp(name, node->name);
    
    if(c > 0){
        //goes right if higher
        return searchTree(node->rChild, name);
    }else{
        //goes left if lower
        return searchTree(node->lChild, name);
    }
    
    return NULL;
}

//inserts a node into the BST and updates parent pointers
Node *insertToTree(Node *root, Node *insertable, int depth){

    // empty tree case
    if (root == NULL) {
        insertable->depth = depth;
        insertable->height = 0;
        insertable->parent = NULL;
        return insertable;
    }

    // node already exists; add fine
    if(strcmp(insertable->name, root->name) == 0){
        root->fine += insertable->fine;
        free(insertable);
        return root;
    }
    
    // update depth of current node
    root->depth = depth;
    
    // recur into left or right subtree
    if (strcmp(insertable->name, root->name) > 0) {
        root->rChild = insertToTree(root->rChild, insertable, depth + 1);
        root->rChild->parent = root;
    } else {
        root->lChild = insertToTree(root->lChild, insertable, depth + 1);
        root->lChild->parent = root;
    }
    
    // update height of current node
    int lHeight = getHeight(root->lChild);
    int rHeight = getHeight(root->rChild);
    root->height = 1 + (lHeight > rHeight ? lHeight : rHeight);

    return root;
}

int getHeight(Node* root){
    //NULL nodes in BST equals -1
    if (root == NULL) {
        return -1;
    }
    //returns the height value of the given Node
    return root->height;
}

//updates depth and height from the given node up to the root
void updateDepthAndHeight(Node* node) {
    while (node != NULL) {
        // update depth
        if (node->parent != NULL)
            node->depth = node->parent->depth + 1;
        else
            node->depth = 0; // Root node

        // update height
        int lHeight = getHeight(node->lChild);
        int rHeight = getHeight(node->rChild);
        node->height = 1 + (lHeight > rHeight ? lHeight : rHeight);

        node = node->parent;
    }
}

//modified deleteNode function with depth and height updates along the path
Node* deleteNode(Node* root, char* name) {
    Node *delnode, *new_del_node, *save_node;
    Node *par;
    char save_name[27];
    int save_fine;

    // get a pointer to the node to delete
    delnode = searchTree(root, name);

    // if the node to delete is not found, return the root as is
    if (delnode == NULL) {
        return root;
    }

    // Get the parent of this node
    par = delnode->parent;

    // case 1: The node to delete is a leaf node
    if (delnode->lChild == NULL && delnode->rChild == NULL) {
        // deleting the only node in the tree
        if (par == NULL) {
            free(root);
            return NULL;
        }

        // delete the node if it's a left or right child
        if (par->lChild == delnode) {
            par->lChild = NULL;
        } else {
            par->rChild = NULL;
        }
        free(delnode);

        // update depth and height along the path
        updateDepthAndHeight(par);

        return root;
    }

    // case 2: The node to be deleted only has a left child
    if (delnode->lChild != NULL && delnode->rChild == NULL) {
        if (par == NULL) {
            delnode->lChild->parent = NULL;
            save_node = delnode->lChild;
            free(delnode);

            
            return save_node;
        }

        if (par->lChild == delnode) {
            par->lChild = delnode->lChild;
        } else {
            par->rChild = delnode->lChild;
        }
        delnode->lChild->parent = par;
        free(delnode);

        // update depth and height along the path
        updateDepthAndHeight(par);

        return root;
    }

    // case 3: The node to be deleted only has a right child
    if (delnode->rChild != NULL && delnode->lChild == NULL) {
        if (par == NULL) {
            delnode->rChild->parent = NULL;
            save_node = delnode->rChild;
            free(delnode);

           
            return save_node;
        }

        if (par->lChild == delnode) {
            par->lChild = delnode->rChild;
        } else {
            par->rChild = delnode->rChild;
        }
        delnode->rChild->parent = par;
        free(delnode);

        // update depth and height along the path
        updateDepthAndHeight(par);

        return root;
    }

    // case 4: The node to delete has two children
    // left sub trees most right child (assignment req)
    new_del_node = delnode->lChild;
    while (new_del_node->rChild != NULL) {
        new_del_node = new_del_node->rChild;
    }

    // save the in-order predecessor's data
    strcpy(save_name, new_del_node->name);
    save_fine = new_del_node->fine;

    // recursively delete the in-order predecessor
    root = deleteNode(root, new_del_node->name);

    // replace the data
    strcpy(delnode->name, save_name);
    delnode->fine = save_fine;

    return root;
}

//deduct function that calls deleteNode if fine becomes zero or negative
Node *deduct(Node *root,char *name, int fine){
    //gets the node to be deducted from
    Node *deductable = searchTree(root, name);
    //base case if search cannot find a node with the given name
    if (deductable == NULL) {
        printf("%s not found\n", name);
        return root;
    }
    //deducts the fine from person's node
    deductable->fine -= fine;
    
    //checks if fine is lower or equal to 0 to start the deletion process
    if (deductable->fine <= 0) {
        //deletes the node
        root = deleteNode(root, name);
        //prints out required string
        printf("%s removed\n", name);
        
        return root;
    }
    //prints the deducted amount if no deletion has been done
    printf("%s %d %d\n", name, deductable->fine, deductable->depth);
    
    return root;
}

//frees the tree
void freeTree(Node * root){
    
    if (root == NULL) {
        return;
    }
    //recurse left
    freeTree(root->lChild);
    //recurse right
    freeTree(root->rChild);
    //free current
    free(root);
}
//adds all values of the nodes took it from class resources
double add(Node *current_ptr) {
    //if node isn't null recursively calls l and r child and adds them all up together
    if (current_ptr != NULL){
        return (double)current_ptr->fine + add(current_ptr->lChild) + add(current_ptr->rChild);
    }
    else
        return 0.00;
}

//modified from class resources
int addlexi(Node *current_ptr, char *name) {
    
    if (current_ptr == NULL) {
        return 0;
    }
    
    //if curr node is lexicographically lower than name add its fine to recurse l and recurse r
    if (strcmp(current_ptr->name, name) <= 0){
        return current_ptr->fine + addlexi(current_ptr->lChild, name) + addlexi(current_ptr->rChild, name);
    }
    
    //if node isn't low continues from left as left is lexicographically lower side and recurse l
    return addlexi(current_ptr->lChild, name);
}
//function returns double to ensure there is no int/int division for average function from class resources
double numnodes(Node *root) {
    
    if (root == NULL) return 0;
    //traverses through the BST and counts the nodes
    return 1 + numnodes(root->lChild) + numnodes(root->rChild);
}
