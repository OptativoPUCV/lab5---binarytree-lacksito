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
      else if (tree->lower_than(key, vigente->pair->key)) 
      {
        vigente = vigente->left;
      } 
      else 
      {
        vigente = vigente->right;
      }
    }
    TreeNode* nodo = createTreeNode(key, value);
    nodo->parent = son;
  if (son == NULL) 
  {
    tree->root = nodo;
  } 
  else if (tree->lower_than(key, son->pair->key)) 
  {
    son->left = nodo;
  } 
  else 
  {
    son->right = nodo;
  }
  
  tree->current = nodo;
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


void removeNode(TreeMap * tree, TreeNode* node) 
{
  if (node->left == NULL && node->right == NULL) 
  {
    if (node->parent != NULL) 
    {
      if (node == node->parent->left) 
      {
        node->parent->left = NULL;
      } 
      else 
      {
        node->parent->right = NULL;
      }
    } 
    else 
    {
      tree->root = NULL; 
    }
        free(node);
        return;
    }

    
    if (node->left == NULL || node->right == NULL) 
    {
      TreeNode* son = (node->left != NULL) ? node->left : node->right;

      if (node->parent != NULL) 
      {
        if (node == node->parent->left) 
        {
          node->parent->left = son;
        } 
        else 
        {
          node->parent->right = son;
        }
      } 
       else         
      {
      tree->root = son; 
      }

      son->parent = node->parent;
      free(node);
        return;
  }

    
  TreeNode* minDer = minimum(node->right);
  node->pair = minDer->pair;
  removeNode(tree, minDer);
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

Pair* firstTreeMap(TreeMap* tree) {
    TreeNode* current = tree->root;
    if (current == NULL) {
        return NULL; 
    }
    while (current->left != NULL) {
        current = current->left;
    }
    tree->current = current;
    return current->pair;
}

Pair* nextTreeMap(TreeMap* tree) {
    if (tree->current == NULL) {
        return NULL; 
    }

    TreeNode* current = tree->current;
    TreeNode* successor = NULL;

    if (current->right != NULL) {
        successor = current->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
    } else {
        TreeNode* parent = current->parent;
        while (parent != NULL && current == parent->right) {
            current = parent;
            parent = parent->parent;
        }
        successor = parent;
    }

    tree->current = successor;
    
    if (successor != NULL) {
        return successor->pair;
    } else {
        return NULL; 
    }
}
