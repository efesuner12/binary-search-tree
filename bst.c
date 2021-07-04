#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"

// Your source code here

Node* newNode(int value)
{
    //creating a new node
    //not in insertNode() just to make things more clear

    Node *new;
    new = (Node*) malloc(sizeof(struct Node));

    new->data = value;
    new->left = NULL;
    new->right = NULL;

    return new;
}

Node* insertNode(Node *root, int value)
{ 
    //if root is null, then creating a new node with the value
    if(root == NULL)
        return newNode(value);
    //if value is greater, it should be inserted to rigth sub-tree
    else if(value > root->data)
            root->right = insertNode(root->right, value);
    //if value is smaller, it should be inserted to left sub-tree
    else if(value < root->data)
            root->left = insertNode(root->left, value);

    return root;
}

Node* findMinimum(Node *root)
{
    //finding the node with the min value
    //recursion until you reach the left-most node of the tree
    
    if(root == NULL)
        return NULL;
    else if(root->left != NULL)
            //left-most node will be the min
            return findMinimum(root->left); 

    return root;
}

Node* deleteNode(Node *root, int value)
{
    Node *temp;
    Node *min;
    
    if(root == NULL)
        return NULL;
    
    if(value > root->data)
            root->right = deleteNode(root->right, value);
    else if(value < root->data)
            root->left = deleteNode(root->left, value);
    else
    {
        //No children
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        //One child
        else if(root->left == NULL || root->right == NULL)
        {
                if(root->left == NULL)
                    temp = root->right;
                else if(root->right == NULL)
                    temp = root->left;

                free(root);
                return temp;
        }
        //Two children
        else if(root->left != NULL && root->right != NULL)
        {
                //finding the left-most node of the right sub-tree
                min = findMinimum(root->right);
                root->data = min->data;
                root->right = deleteNode(root->right, min->data);
        }
    }

    return root;
}

void printSubtree(Node *N)
{
    if(N != NULL) 
    {
        printSubtree(N->left); // visiting left child
        printf("%d\n", N->data); // printing data at root
        printSubtree(N->right);// visiting right child
    }
}

int countNodes(Node *N)
{
    int number = 1; //counts the root node

    if(N == NULL)
        return 0;
    else
    {
        number += countNodes(N->left);
        number += countNodes(N->right);

        return number;
    }
}

Node* freeSubtree(Node *N)
{   
    //if N is null, do nothing
    if(N == NULL)
        return 0;
    else if(N != NULL)
    {
            freeSubtree(N->left);
            free(N);
            freeSubtree(N->right);
    }
    
    return NULL;
}
                            
int sumSubtree(Node *N)
{
    int sum, sumLeft, sumRight;
    sum = sumLeft = sumRight = 0;

    if(N == NULL)
        return 0;
    else 
    {
        if(N->left != NULL)
            sumLeft = sumSubtree(N->left);
        if(N->right != NULL)
            sumRight = sumSubtree(N->right);
        
        sum = N->data + sumLeft + sumRight;

        return sum;
    }
}
