//
// Created by sakkammadam on 6/19/22.
//

#ifndef CPS500_HW8_ISOBSTHEAP_TREEFUNCTIONS_H
#define CPS500_HW8_ISOBSTHEAP_TREEFUNCTIONS_H
#include<stdlib.h>


// Node representing individual elements of tree
typedef struct TreeNode{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// "Root" node associated with Tree
typedef struct Tree{
    struct TreeNode* root;
} Tree;

struct TreeNode* initTreeNode(int inputData){
    // Initialize in heap
    struct TreeNode* initNode = malloc(sizeof(struct TreeNode));
    initNode->data = inputData;
    initNode->left = NULL;
    initNode->right = NULL;
    return initNode;
}

// Define a Queue node which reflects a TreeNode
typedef struct QueueNode{
    TreeNode* node;
    struct QueueNode* next;
} QueueNode;

// Define a Queue Structure here with the TreeNodes!
typedef struct Queue{
    struct QueueNode* head;
    struct QueueNode* tail;
} Queue;

QueueNode* initQNode(TreeNode* treeNode){
    QueueNode* temp = malloc(sizeof(QueueNode));
    temp->node=treeNode;
    temp->next=NULL;
    return temp;
}

// Initialize Queue
Queue initQueue(){
    Queue* temp = malloc(sizeof(struct Queue));
    temp->head = NULL;
    temp->tail = NULL;
    return *temp;
}

// Function to enqueue new(er) items to Queue
void enQueue(Queue* q, TreeNode* entryNode){
    // associate QueueNode!
    QueueNode* tempQNode = initQNode(entryNode);
    // let's check if the queue is null to begin with! check head and tail!
    if(q->head==NULL){
        q->head = tempQNode;
        q->tail = tempQNode;
        return;
    } else{
        q->tail->next=tempQNode;
        q->tail=tempQNode;
    }
}

// Function to dequeue
TreeNode* deQueue(Queue* q) {
    // based on header decide what to return !
    if (q->head == NULL) {
        TreeNode *node = NULL;
        return node;
    } else {
        TreeNode *node = q->head->node;
        // setting the header pointers ...
        if (q->head != NULL) {
            // assign a temp pointer for the header
            QueueNode *temp = q->head;
            // change the header point to the next
            q->head = q->head->next;
            free(temp);
            // if for some reason you were the last item in the queue, lets do some queue maintenance too
            if (q->head == NULL) {
                q->tail = NULL;
            }
        }
        // final return
        return node;
    }
}
// create binary tree using recursion!
void createBinaryTreeRecurs(TreeNode* node, int input){
    if(node==NULL || node->data==input){
        return;
    } else if (node->data > input){
        if(node->left==NULL){
            node->left = initTreeNode(input);
        }
        return createBinaryTreeRecurs(node->left,input);
    } else {
        if(node->right==NULL){
            node->right = initTreeNode(input);
        }
        return createBinaryTreeRecurs(node->right,input);
    }
}

// let's create an BFS based function to print!
void bfsPrint(Tree* tree){
    // create and initialize an empty Queue!
    Queue q = initQueue();
    // seed the queue with the root!
    enQueue( &q, tree->root);
    while(q.head != NULL){
        TreeNode* next = deQueue(&q);
        printf("\n[BFS]-NodeValue->%d",next->data);
        if(next->left != NULL){
            enQueue(&q, next->left);
        }
        if(next->right != NULL){
            enQueue(&q, next->right);
        }
    }
}

// binary Search!
void binarySearch(TreeNode* node, int value){
    if(node==NULL){
        printf("\nData - %d not found!", value);
    } else if(node->data==value){
        printf("\nFound data in the tree - %d", node->data);
    } else if(node->data < value){
        return binarySearch(node->right, value);
    } else{
        return binarySearch(node->left,value);
    }
}


// create a helper function to return the minimum node (along the left path) used for deleting nodes that have 2 child
TreeNode* minValNode(TreeNode* baseNode){
    TreeNode* currentNode = baseNode;
    while(currentNode!=NULL && currentNode->left!=NULL){
        currentNode=currentNode->left;
    }
    return currentNode;
}

// Function to delete a node containing inputData!
// The entry point has to be root of the tree! - iteration based!
void deleteNode(Tree* rootNode, int inputData){
    // set NULL to parent pointer for the rootNode
    TreeNode* parentNode=NULL;
    // start from the root!
    TreeNode* currentNode = rootNode->root;
    printf("\nRootNode?%d", currentNode->data);
    printf("\nMain delete - input data is %d", inputData);
    // search for inputData in the tree if found, parentNode address will be updated!
    while(currentNode!=NULL && currentNode->data!=inputData){
        parentNode=currentNode;
        if(inputData < currentNode->data){
            currentNode=currentNode->left;
        } else
            currentNode=currentNode->right;
    }

    // Now we will do some checks!
    // if the data point is never there, currentNode will be NULL
    if(currentNode==NULL){
        return;
    } else {
        // inputData == node->data --- case1 - the node that we are deleting is a leaf node!
        if(currentNode->left == NULL && currentNode->right == NULL){//  no children!
            printf("\nLeafNode delete! %d", currentNode->data);
            if(currentNode!=rootNode->root){
                // check if currentNode is left child of parent node
                if(parentNode->left==currentNode){
                    // set the parentNode's left child to NULL
                    parentNode->left=NULL;
                } else{
                    // set the parentNode's right child to NULL
                    parentNode->right=NULL;
                }
            } else {
                // handle the edge case where we have to delete the root of a 1 node tree
                rootNode=NULL;
            }
            // Free the memory too!
            free(currentNode);
        } else if (currentNode->left && currentNode->right){// currentNode has two children!
            // find the next highest (going right) but the lowest among those (by going left one level down)
            TreeNode* nextNode = minValNode(currentNode->right);
            // store nextNode's value
            int tempValue = nextNode->data;
            // delete the nextNode from the tree
            deleteNode(rootNode, nextNode->data);
            // associate the value back to currentNode
            currentNode->data = tempValue;
        } else {
            // final edge case - when there is only 1 child
            TreeNode* childNode = NULL;
            if (currentNode->left){
                childNode = currentNode->left;
            } else{
                childNode = currentNode->right;
            }
            // let's check if the currentNode is not root
            if(currentNode != rootNode->root){
                if(currentNode==parentNode->left){
                    parentNode->left = childNode;
                } else{
                    parentNode->right = childNode;
                }
            } else {
                rootNode->root = childNode;
            }
            // clear up the currentNode
            free(currentNode);
        }
    }
}


#endif //CPS500_HW8_ISOBSTHEAP_TREEFUNCTIONS_H
