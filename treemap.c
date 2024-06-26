#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;

    //new->lower_than = lower_than;
    return NULL;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL || tree->root == NULL){
        tree->root = createTreeNode(key, value);
        tree->current = tree->root;
        
    }
    else{
        TreeNode* aux = tree->root;
        TreeNode* parent = NULL;
        while(aux != NULL)
        {
            parent = aux;
            if(is_equal(tree,aux->pair->key,key)){
                aux->pair->value = value;
                return;
            }
            else{
                if(tree->lower_than(aux->pair->key,key)){
                    aux = aux->right;
                    
                }
                else{
                    aux = aux->left;
                }
            }
            
        }
        TreeNode* new = createTreeNode(key, value);
        new->parent = parent;
        if(tree->lower_than(parent->pair->key,key)){
            parent->right = new;
            
        }
        else{
            parent->left = new;
        }
        tree->current = new;
        
    }
    
}
    

TreeNode * minimum(TreeNode * x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    return;
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode* aux = tree->root;
    while(aux != NULL){
        if(is_equal(tree,aux->pair->key,key)){
            tree->current = aux;
            return aux->pair;
            
        }
        else{
            if(tree->lower_than(aux->pair->key,key))
            {
                aux = aux->right;
            }
            else{
                aux = aux->left;
            }
        }
        
    }
    
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode* aux = minimum(tree->root);
    tree->current = aux;
    return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->current == NULL) return NULL;
    TreeNode* aux = tree->current;
    if(aux->right != NULL){
        tree->current = minimum(aux->right);
        return tree->current->pair;
    }
    else{
        TreeNode* parent = aux->parent;
        while(parent != NULL && aux == parent->right){
            aux = parent;
            parent = parent->parent;
            
        }
        tree->current = parent;
        if(parent != NULL){
            return parent->pair;
            
        }
        else{
            return NULL;
        }
        
    }
    
    return NULL;
}
