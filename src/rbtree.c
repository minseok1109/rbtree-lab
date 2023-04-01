#include "rbtree.h"

#include <stdlib.h>
void leftRotate(rbtree *t, node_t *x);
void rightRotate(rbtree *t, node_t *y);
void rbtree_insert_fixUp(rbtree *t, node_t *z);

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *newNode = (node_t *)calloc(1, sizeof(node_t));
  newNode->color = RBTREE_BLACK;
  newNode->left = p->nil;
  newNode->right = p->nil;
  newNode->parent = p->nil;
  newNode->key = 0;
  p->root = newNode;
  p->nil = p->root;

  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  // 새로운 노드 생성
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  z->key = key;

  node_t *y = t->nil;
  node_t *x = t->root;

  while (x != t->nil)
  {
    y = x;
    if (z->key < x->key)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }

  z->parent = y;

  if (y == t->nil)
  {
    t->root = z;
  }
  //  새로운 노드의 좌우결정
  else if (z->key < y->key)
  {
    y->left = z;
  }
  else
  {
    y->right = z;
  }

  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;

  return t->root;
}

void rbtree_insert_fixUp(rbtree *t, node_t *z)
{
  while (z->parent->color == RBTREE_RED)
  {
    if (z->parent == z->parent->parent->left)
    {
      node_t *y = z->parent->parent->right;
      if (y->color == RBTREE_RED)
      {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else if (z == z->parent->right)
      {
        z = z->parent;
        leftRotate(t, z);
      }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      rightRotate(t, z->parent->parent);
    }
    else
    {
      node_t *y = z->parent->parent->left;
      if (y->color == RBTREE_RED)
      {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else if (z == z->parent->left)
      {
        z = z->parent;
        rightRotate(t, z);
      }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      leftRotate(t, z->parent->parent);
    }
  }
}

void leftRotate(rbtree *t, node_t *x)
{
  node_t *y = x->right; // y를 설정
  x->right = y->left;   // y의 왼쪽 서브트리를 x의 오른쪽으로 옮긴다.
  if (y->left != t->nil)
  {
    y->left->parent = x; // y의 왼쪽 서브트리의 부모도 x로 지정
  }
  y->parent = x->parent; // x의 부모와 y를 연결
  if (x->parent == t->nil)
  {
    t->root = y;
  }
  else if (x == x->parent->left) // x가 부모의 왼쪽 서브티리이면
  {
    x->parent->left = y; // 그 위치를 y와 연결
  }
  else
  {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void rightRotate(rbtree *t, node_t *y)
{
  node_t *x = y->left;    // x를 설정
  y->left = x->right;     // y의 왼쪽 서브트리를 x의 오른쪽 서브트리로 설정
  if (x->right != t->nil) // x의 오른쪽 서브트리가 nill이 아니면
  {
    x->right->parent = y; // x의 오른쪽과 y를 부모자식관계로 연결
  }
  x->parent = y->parent;   // y의 부모를 x의 부모로 변경
  if (y->parent == t->nil) // y의 부모가 없으면
  {
    t->root = x; // x를 트리의 루트로 설정
  }
  else if (y == y->parent->left) // y가 y의 부모의 왼쪽이였으면
  {
    y->parent->left = x; // 똑같이 x를 y의 부모의 왼쪽으로 설정
  }
  else
  {
    y->parent->right = x; // x를 y의 부모의 오른쪽으로 설정
  }
  x->right = y;  // x의 오른쪽을 y로 설정
  y->parent = x; // y의 부모를 x로 설정
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}
