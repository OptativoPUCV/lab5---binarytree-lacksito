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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
  TreeMap * new = (TreeMap *)malloc(sizeof(TreeNode));

  new->root = NULL;
  new->lower_than = lower_than;
  return new;
}


void insertTreeMap(TreeMap* tree, void* key, void* value) 
{

    TreeNode* vigente = tree->root;
    TreeNode* son = NULL;
    while (vigente != NULL) 
    {
      son = vigente;
      if (is_equal(tree, key, vigente->pair->key))
      {
        return;
      } 
      else if (tree->lower_than(key, vigente->pair->key) > 0) 
      {
        vigente = vigente->left;
      } 
      else 
      {
        vigente = vigente->right;
      }
    TreeNode* newNodo = createTreeNode(key, value);
      
    newNodo->parent = son;
    if (son == NULL) 
    {
      tree->root = newNodo;
    }
    else if (tree->lower_than(key, son->pair->key))
    {
      son->left = newNodo;
    }
    else
    {
      son->right = newNodo;
    }
  tree->current = newNodo;
}

TreeNode * minimum(TreeNode * x)
{
  if (x == NULL) return NULL;
  while( x->left != NULL)
    {
      x = x->left;
    }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
  TreeNode* vigente = tree->root;
  while (vigente != NULL) 
  {
    //tuve un error al asignar una variable a tree->lower_than(key, vigente->pair->key)
    if(tree->lower_than(key, vigente->pair->key) > 0 )
    {
      vigente = vigente->left;
    }
    else if (is_equal(tree, vigente->pair->key, key))
    {
      printf("\n pase aqui\n");
      tree->current = vigente;
      return vigente->pair;
    }
    else 
    {
      vigente = vigente->right;
    }
  }


    
    return NULL;
}



Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
