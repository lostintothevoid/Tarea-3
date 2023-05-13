#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode {
  Pair *pair;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
};

struct TreeMap {
  TreeNode *root;
  TreeNode *current;
  int (*lower_than)(void *key1, void *key2);
};

int is_equal(TreeMap *tree, void *key1, void *key2) {
  if (tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0)
    return 1;
  else
    return 0;
}

TreeNode *createTreeNode(void *key, void *value) {
  TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
  if (new == NULL)
    return NULL;
  new->pair = (Pair *)malloc(sizeof(Pair));
  new->pair->key = key;
  new->pair->value = value;
  new->parent = new->left = new->right = NULL;
  return new;
}

TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2)) {
  TreeMap *temp = (TreeMap *)malloc(sizeof(TreeMap));
  temp->root = NULL;
  temp->current = temp->root;
  temp->lower_than = lower_than;
  return temp;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) {
  if (tree->root == NULL) {
    TreeNode *root = createTreeNode(key, value);
    tree->root = root;
    return;
  }
  if (searchTreeMap(tree, key) == NULL) {
    TreeNode *temp = createTreeNode(key, value);
    temp->parent = tree->current;
    if (tree->lower_than(key, tree->current->pair->key) == 1) {
      tree->current->left = temp;
      tree->current = temp;
    } else {
      tree->current->right = temp;
      tree->current = temp;
    }
  }
  return;
}

TreeNode *minimum(TreeNode *x) {
  if (x->left == NULL)
    return x;
  return minimum(x->left);
}

void removeNode(TreeMap *tree, TreeNode *node) {
  if (searchTreeMap(tree, node->pair->key) == NULL)
    return;
  else {
    tree->current = node->parent;
    if (node->left == NULL && node->right == NULL) {
      if (tree->lower_than(tree->current->pair->key, node->pair->key) == 1) {
        node->parent->right = NULL;
        free(node);

      } else {
        node->parent->left = NULL;
        free(node);
        return;
      }
    }
    if (node->left != NULL && node->right == NULL) {
      if (tree->lower_than(tree->current->pair->key, node->pair->key) == 1) {
        // left
        tree->current->right = node->left;
        node->left->parent = tree->current;
        node->parent = NULL;
        free(node);
        return;
      } else {
        // right
        tree->current->left = node->left;
        node->left->parent = tree->current;
        node->parent = NULL;
        free(node);
        return;
      }
    } else {
      if (node->left == NULL && node->right != NULL) {
        if (tree->lower_than(tree->current->pair->key, node->pair->key) == 1) {
          // left
          tree->current->right = node->right;
          node->right->parent = tree->current;
          node->parent = NULL;
          free(node);
          return;
        } else {
          // right
          tree->current->left = node->right;
          node->right->parent = tree->current;
          node->parent = NULL;
          free(node);
          return;
        }
      }
    }
    if (node->left != NULL && node->right != NULL) {
      TreeNode *min = minimum(node);
      node->pair->key = min->pair->key;
      node->pair->value = min->pair->value;
      removeNode(tree, min);
      return;
    }
  }
}

void eraseTreeMap(TreeMap *tree, void *key) {
  if (tree == NULL || tree->root == NULL)
    return;

  if (searchTreeMap(tree, key) == NULL)
    return;
  TreeNode *node = tree->current;
  removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key) {
  tree->current = tree->root;
  TreeNode *aux = tree->current;
  int resultado;
  while (aux != NULL) {
    if (is_equal(tree, key, aux->pair->key) == 1) {
      tree->current = aux;
      return aux->pair;
    }

    resultado = tree->lower_than(key, aux->pair->key);
    if (resultado == 1) {
      aux = aux->left;
    } else {
      aux = aux->right;
    }
    if (aux != NULL)
      tree->current = aux;
  }

  return NULL;
}

Pair *upperBound(TreeMap *tree, void *key) {
  
  return NULL; 
}

Pair *firstTreeMap(TreeMap *tree) {
  if(!tree) return NULL;
  tree->current = tree->root;
  tree->current = minimum(tree->current);
  return tree->current->pair;
}

Pair *nextTreeMap(TreeMap *tree) {
  TreeNode *aux=tree->current->right;
  if(tree->current==minimum(tree->current) && aux){
    tree->current=tree->current->right;
    return aux->pair;
  }
  if(tree->current==minimum(tree->current) && !aux){
    tree->current=tree->current->parent;
    return tree->current->pair;
  }
  if(tree->current!=minimum(tree->current)){
    if(tree->current->right!=NULL){
      tree->current=minimum(tree->current->right);
    }
    else{
      aux=tree->current->parent;
      while(aux!=NULL && tree->current== aux->right){
        tree->current=aux;
        aux=aux->parent;
      }
      tree->current=aux;
      if (tree->current != NULL && tree->current != minimum(tree->current)) {
        aux=tree->current->parent;
        while (aux != NULL && aux->right == tree->current) {
          tree->current = tree->current->parent;
        }
        tree->current = tree->current->parent;
      }
    }
    
  }
  
  if(tree->current!=NULL){
    return tree->current->pair;
  }
  else{
    return NULL;
  }
}