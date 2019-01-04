#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

// write definition for bst_insert here
void bst_insert(btNode*& bst_root, int anInt){
    
    if(bst_root == 0){
        btNode* new_root = new btNode;
        new_root->data = anInt;
        new_root->left = new_root->right = 0;
        bst_root = new_root;
        return;
    }

    btNode* cursor = bst_root;

    while(cursor != 0){
        if(anInt < cursor->data){
            if(cursor->left == 0){
                cursor->left = new btNode;
                cursor->left->data = anInt;
                cursor->left->left = cursor->left->right = 0;
                return;
            }
            else
                cursor = cursor->left;
        }
        else if(anInt > cursor->data){
            if(cursor->right == 0){
                cursor->right = new btNode;
                cursor->right->data = anInt;
                cursor->right->left = cursor->right->right = 0;
                return;
            }
            else
                cursor = cursor->right;
        }
        else
            return;
    }
/*
    while(current != 0){
        leafPtr = current;

        if(current->data < value)
            current = current->right;
        else if(current->data == value){
            current = nodePtr;
            return;
        }
        else
            current = current->left;
    }

    if(leafPtr->data < value)
        leafPtr->right = nodePtr;
    else
        leafPtr->left = nodePtr;*/
}
// write definition for bst_remove here
bool bst_remove(btNode*& bst_root, int remInt){

    if(bst_root == 0)
        return false;
    //If remInt < root call function, send it the left child
    if(remInt < bst_root->data)
        bst_remove(bst_root->left, remInt);
    //If remInt > root, call function, send it the right child
    else if(remInt > bst_root->data)
        bst_remove(bst_root->right, remInt);
    else{
        //case if remInt = bst_root with 2 children
        if(bst_root->right != 0 && bst_root->left != 0)
            bst_remove_max(bst_root->left, bst_root->data);
        else{
            //cases if remInt = bst_root with one child
            //or no children
            btNode* old_bst_root = bst_root;

            if(bst_root->right != 0 && bst_root->left == 0)
                bst_root = bst_root->right;
            else if(bst_root->left != 0 && bst_root->right == 0)
                bst_root = bst_root->left;
            else
                bst_root = 0;

            delete old_bst_root;

        }
            return true;
    }
}
// write definition for bst_remove_max here

void bst_remove_max(btNode*& bst_root, int& remInt){

    if(bst_root == 0) return;

    if(bst_root->right == 0){
        btNode* tempNode = bst_root;
        remInt = bst_root->data;
        bst_root = bst_root->left;
        delete tempNode;
    }
    else 
        bst_remove_max(bst_root->right, remInt);
}





















