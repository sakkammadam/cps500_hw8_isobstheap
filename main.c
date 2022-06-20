#include <stdio.h>
#include <stdlib.h>
#include "treeFunctions.h"
#include <limits.h>

// struct to host heap!
typedef struct Heap{
    // actual Array
    int* array;
    // Array capacity
    int capacity;
    // Number of elements in the heap!
    int size;
} Heap;

// Function to swap heap values
void swapHeapValues(int* a, int* b);

// Function to insert records in a Min Heap
void insertMinHeap(Heap* heap, int inputData);

// Function to remove root of a Min Heap
void removeRootMinHeap(Heap* heap);

// Another function to remove root of a Min heap
void removeRootNodeFrmMinHeap(Heap* heap);

// Complimentary Function used by function to recreate heap
void heapifyDown(int arr[], int n, int i);

// Function to check if two trees are isomorphic or not!
int isomorphicRecur(Tree* tree1, Tree* tree2);

// Function to check if the tree is Binary Search tree or not!
int isBinarySearchTree(Tree* tree);

// Utility function used within isBinarySearchTree to evaluate node values
int isBinarySearchNode(TreeNode* node, int minValue, int maxValue);

int main() {

    // Initialize a root node for tree1
    TreeNode* rootR1 = initTreeNode(50);
    // Create a tree
    createBinaryTreeRecurs(rootR1, 30);
    createBinaryTreeRecurs(rootR1, 20);
    createBinaryTreeRecurs(rootR1, 40);
    createBinaryTreeRecurs(rootR1, 70);
    createBinaryTreeRecurs(rootR1, 60);
    createBinaryTreeRecurs(rootR1, 80);
    // Print using Breadth First Search
    printf("\nCreated a new tree....");
    bfsPrint((Tree*)&rootR1);

    // Initialize a root node
    TreeNode* rootR2 = initTreeNode(500);
    // Create a tree
    createBinaryTreeRecurs(rootR2, 300);
    createBinaryTreeRecurs(rootR2, 200);
    createBinaryTreeRecurs(rootR2, 400);
    createBinaryTreeRecurs(rootR2, 700);
    createBinaryTreeRecurs(rootR2, 600);
    createBinaryTreeRecurs(rootR2, 800);
    // Print using Breadth First Search
    printf("\nCreated a new tree....");
    bfsPrint((Tree*)&rootR2);

    printf("TreeR1 and R2 are isomorphic - %d",isomorphicRecur((Tree*)&rootR1, (Tree*)&rootR2));

    // Initialize a root node for tree1
    TreeNode* rootR3 = initTreeNode(50);
    // Create a tree
    createBinaryTreeRecurs(rootR3, 30);
    createBinaryTreeRecurs(rootR3, 20);
    createBinaryTreeRecurs(rootR3, 40);
    createBinaryTreeRecurs(rootR3, 70);
    createBinaryTreeRecurs(rootR3, 60);
    createBinaryTreeRecurs(rootR3, 80);
    // Print using Breadth First Search
    printf("\nCreated a new tree....");
    bfsPrint((Tree*)&rootR3);

    // Initialize a root node
    TreeNode* rootR4 = initTreeNode(500);
    // Create a tree
    createBinaryTreeRecurs(rootR4, 300);
    createBinaryTreeRecurs(rootR4, 200);
    createBinaryTreeRecurs(rootR4, 400);
    createBinaryTreeRecurs(rootR4, 700);
    createBinaryTreeRecurs(rootR4, 600);
    // Print using Breadth First Search
    printf("\nCreated a new tree....");
    bfsPrint((Tree*)&rootR4);
    // These will not be isomorphic as 800 node is not there
    printf("\nTreeR3 and R4 are isomorphic -  %d",isomorphicRecur((Tree*)&rootR3, (Tree*)&rootR4));

    // Evaluate BST!
    printf("\nTreeR1 is a binary search tree- %d",isBinarySearchTree((Tree*)&rootR1));

    // change the root value
    rootR1->data=100000;
    // display
    bfsPrint((Tree*)&rootR1);
    // now TreeR1 is not a binary search tree!
    printf("\nchecking if TreeR1 is a binary search tree- %d",isBinarySearchTree((Tree*)&rootR1));

    int N = 10;
    // initialize array in heap memory
    int* array4Heap = malloc(N*sizeof(int));
    // initialize struct of heap
    Heap h = {array4Heap, 10, 0};
    // let's populate the min heap
    for(int i=N-1; i>=0; i--){
        insertMinHeap(&h, i);
    }
    // let's print the heap
    printf("\nThe heap looks like this ->");
    for(int i=0; i<h.size; i++){
        printf("\nHeap element[%d] -> [%d]",i, h.array[i]);
    }
    // Used this visualization - https://www.cs.csubak.edu/~msarr/visualizations/Heap.html - to confirm behavior
    printf("\nHeap size is %d", h.size);
    // let's remove the min root of the heap
    removeRootMinHeap(&h);

    // let's print the heap
    printf("\nAfter removing the root the heap looks like this ->");
    for(int i=0; i<h.size; i++) {
        printf("\nHeap element[%d] -> [%d]", i, h.array[i]);
    }
    // Used this visualization - https://www.cs.csubak.edu/~msarr/visualizations/Heap.html - to confirm behavior
    // -- click on "Remove smallest"

    // let's add it back
    insertMinHeap(&h, 0);

    // let's print the heap
    printf("\nAfter adding the 0 back, the heap looks like this ->");
    for(int i=0; i<h.size; i++) {
        printf("\nHeap element[%d] -> [%d]", i, h.array[i]);
    }
    // Used this visualization - https://www.cs.csubak.edu/~msarr/visualizations/Heap.html - to confirm behavior
    // -- add 0 and click on Insert

    // let's remove the root again
    removeRootNodeFrmMinHeap(&h);

    // let's print the heap again
    printf("\nAfter removing the 0 again using heapifydown, the heap looks like this ->");
    for(int i=0; i<h.size; i++) {
        printf("\nHeap element[%d] -> [%d]", i, h.array[i]);
    }

    return 0;
}

int isomorphicRecur(Tree* tree1, Tree* tree2){
    // base cases - if both trees are empty - they are isomorphic!
    if(tree1==NULL && tree2==NULL){
        return 1;
    } else if (tree1==NULL || tree2==NULL){
        return 0;
    } else{
        // let's initialize Queues to host items
        Queue q1 = initQueue(); // used for tree1
        Queue q2 = initQueue(); // used for tree2
        // seed the Queue1 with Tree1's root node
        enQueue( &q1, tree1->root);
        // seed the Queue2 with Tree2's root node
        enQueue( &q2, tree2->root);
        while(q1.head!=NULL && q2.head!=NULL){
            TreeNode* popNodeFrmTree1 = deQueue(&q1);
            TreeNode* popNodeFrmTree2 = deQueue(&q2);
            if(popNodeFrmTree1->left && popNodeFrmTree2->left){
                enQueue( &q1, popNodeFrmTree1->left);
                enQueue( &q2, popNodeFrmTree2->left);
            } else if ((popNodeFrmTree1->left==NULL && popNodeFrmTree2->left!=NULL)
            || (popNodeFrmTree1->left!=NULL && popNodeFrmTree2->left==NULL)){
                return 0;
            } else {
                printf("\nleft continuing to right...");
            }
            if(popNodeFrmTree1->right && popNodeFrmTree2->right){
                enQueue( &q1, popNodeFrmTree1->right);
                enQueue( &q2, popNodeFrmTree2->right);
            } else if ((popNodeFrmTree1->right==NULL && popNodeFrmTree2->right!=NULL)
                       || (popNodeFrmTree1->right!=NULL && popNodeFrmTree2->right==NULL)){
                printf("\nbye right");
                return 0;
            } else {
                printf("\nright complete...");
            }
        }
        // after reading the entire tree
        return 1;
    }
}

int isBinarySearchTree(Tree* tree){
    // NULL trees are Binary Search trees!
    if(tree==NULL){
        return 1;
    } else{
        // recursive call starting with the tree's root
        return isBinarySearchNode(tree->root, INT_MIN, INT_MAX);
    }
}

int isBinarySearchNode(TreeNode* node, int minValue, int maxValue){
    // base cases!
    if(node==NULL){
        // Null node
        return 1;
    } else if (node->data < minValue || node->data > maxValue){
        // if node's data violates the min/max ranges
        return 0;
    } else {
        return isBinarySearchNode(node->left, minValue, node->data-1) &&
        isBinarySearchNode(node->right, node->data+1, maxValue);
    }
}

// Function used to swap Heap values
void swapHeapValues(int* a, int* b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

// Function used to insert data into a minHeap
void insertMinHeap(Heap* heap, int inputData){
    // insert new input by reflecting the size of the heap
    if(heap->size < heap->capacity){
        heap->array[heap->size++] = inputData;
    } else {
        printf("\nCannot insert as heap size exceeded!");
        // maybe double the array size ?
        return;
    }
    // set an index
    int index = (heap->size)-1;
    // perform array swaps that move heap items - child (index) and parent ([index-1]/2) in the array
    while(index>0 && (heap->array[index] < heap->array[(index-1)/2])){
        swapHeapValues(&(heap->array[index]), &(heap->array[(index-1)/2]));
        // swap the index for the next order comparison
        index = (index-1)/2;
    }
}

// Function to remove min (root) element of min heap data structure
void removeRootMinHeap(Heap* heap){
    // swap the 0th item in the array (root) with the last item in the array
    heap->array[0] = heap->array[--heap->size];
    // Starting with the new "highest" element
    int i=0;
    int left = 2*i+1;
    int right = 2*i+2;
    // Checking only 1 side of the tree
    while((i < (heap->size/2 + 1)) &&
        // ** Thank you Prof. Roueche for suggestion on checking if indices are valid!
        ((left < heap->size && heap->array[i] > heap->array[left])
        || (right < heap->size && heap->array[i] > heap->array[right]))){
        // check if the right child is smaller than left child
        if (right < heap-> size && heap->array[left] > heap->array[right]){
            swapHeapValues(&(heap->array[i]),&(heap->array[right]));
            // set index to right
            i=right;
        } else{
            // left value is smaller
            swapHeapValues(&(heap->array[i]),&(heap->array[left]));
            // set index to left
            i=left;
        }
        // recreate left and right indexes
        left = 2*i+1;
        right = 2*i+2;
    }
}

void removeRootNodeFrmMinHeap(Heap* heap){
    // swap the 0th item in the array (root) with the last item in the array
    heap->array[0] = heap->array[--heap->size];
    // heapify the root node
    heapifyDown(heap->array, heap->size, 0);
}

// Function to recreate the heapify after removing a minimum node
void heapifyDown(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
        printf("\nLeft - smallest -%d",smallest);
    }
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
        printf("\nRight - smallest -%d",smallest);
    }
    if (smallest != i) {
        swapHeapValues(&arr[i], &arr[smallest]);
        heapifyDown(arr, n, smallest);
    }
}