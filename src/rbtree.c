#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void print_tree(node_t *n);
void leftRotate(rbtree *t, node_t *x);
void rightRotate(rbtree *t, node_t *y);
void rbtree_insert_fixUp(rbtree *t, node_t *z);

void print_tree(node_t *n)
{
  if (n->key != 0)
  {
    if (n->color == RBTREE_RED)
    {
      printf("color Red: ");
    }
    else
    {
      printf("color Black: ");
    }
    printf(":%d\n", n->key);

    print_tree(n->left);
    print_tree(n->right);
  }
}

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  // 새로운 노드 생성 및 설정
  node_t *newNode = (node_t *)calloc(1, sizeof(node_t));
  newNode->color = RBTREE_BLACK;
  newNode->left = p->nil;
  newNode->right = p->nil;
  newNode->parent = p->nil;
  newNode->key = 0;

  // 생성한 노드를 루트로 설정
  p->root = newNode;
  p->nil = p->root;

  return p;
}

void delete_rbtree_post_order_traversal(node_t *node, node_t *nil)
{
  if (node == nil)
  {
    return;
  }

  delete_rbtree_post_order_traversal(node->left, nil);
  delete_rbtree_post_order_traversal(node->right, nil);
  free(node);
}

void delete_rbtree(rbtree *t)
{

  delete_rbtree_post_order_traversal(t->root, t->nil);
  free(t->nil);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{

  // 새로운 노드 생성
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  z->color = RBTREE_RED;
  z->key = key;

  node_t *y = t->nil;
  node_t *x = t->root;

  while (x != t->nil)
  {
    y = x;
    if (z->key < x->key) // x의 key보다 작으면 왼쪽
    {
      x = x->left;
    }
    else
    {
      x = x->right; // 아니면 오른쪽
    }
  }

  z->parent = y; // 새로운 노드의 부모를 y로 설정

  if (y == t->nil)
  {
    t->root = z;
    z->color = RBTREE_BLACK; // y가 빈 노드면 새로운 노드를 루트로 설정
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
  rbtree_insert_fixUp(t, z);
  return t->root;
}

void rbtree_insert_fixUp(rbtree *t, node_t *z)
{
  while (z->parent->color == RBTREE_RED) // 새로 삽입한 노드의 부모가 빨간색이면
  {
    if (z->parent == z->parent->parent->left) // 새로운 노드의 부모가 할아버지 노드의 왼쪽이면
    {
      node_t *y = z->parent->parent->right; // 삼촌 노드
      // case 1
      if (y->color == RBTREE_RED) // 삼촌노드가 빨간색이면
      {
        z->parent->color = RBTREE_BLACK; // 새로운 노드의 부모를 검은색으로 변경
        y->color = RBTREE_BLACK;
        if (z->parent->parent == t->root)
        {
          z->parent->parent->color = RBTREE_BLACK;
        }
        else
        {
          z->parent->parent->color = RBTREE_RED; // 할아버지 노드의 색깔을 빨강으로 변경
        }                                        // 삼촌노드의 색깔도 검은색으로 변경
        z = z->parent->parent;                   // z의 위치를 z의 할아버지로 변경
      }
      // case 2
      else if (z == z->parent->right)
      {
        z = z->parent;
        leftRotate(t, z);
      }
      else if (z == z->parent->left)
      {
        // case 3
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        rightRotate(t, z->parent->parent);
      }
    }
    else // 새로운 노드의 부모가 할아버지 노드의 오른쪽이면
    {
      node_t *y = z->parent->parent->left; // 삼촌 노드
      // case 1
      if (y->color == RBTREE_RED) // 삼촌노드가 빨간색이면
      {
        z->parent->color = RBTREE_BLACK; // 새로운 노드의 부모를 검은색으로 변경
        y->color = RBTREE_BLACK;
        if (z->parent->parent == t->root)
        {
          z->parent->parent->color = RBTREE_BLACK;
        }
        else
        {
          z->parent->parent->color = RBTREE_RED; // 할아버지 노드의 색깔을 빨강으로 변경
        }                                        // 삼촌노드의 색깔도 검은색으로 변경
        z = z->parent->parent;                   // z의 위치를 z의 할아버지로 변경
      }
      // case 2
      else if (z == z->parent->left)
      {
        z = z->parent;
        rightRotate(t, z);
      }
      else if (z == z->parent->right)
      {
        // case 3
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        leftRotate(t, z->parent->parent);
      }
    }
  }
}

void leftRotate(rbtree *t, node_t *x)
{
  node_t *y = x->right; // y를 설정
  x->right = y->left;   // y의 왼쪽 서브트리를 x의 오른쪽으로 옮긴다.

  // x,y color swap
  // color_t temp = x->color;
  // x->color = y->color;
  // y->color = temp;

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

  // 루트
  node_t *x = t->root;

  while (x != t->nil)
  {
    if (x->key == key)
    {
      return x;
    }
    else if (key > x->key)
    {
      x = x->right;
    }
    else
    {
      x = x->left;
    }
  }
  return NULL;
}
node_t *rbtree_min(const rbtree *t)
{
  node_t *n = t->root;
  while (n->left != t->nil)
  {
    n = n->left;
  }

  return n;
}

node_t *rbtree_max(const rbtree *t)
{
  node_t *n = t->root;
  while (n->right != t->nil)
  {
    n = n->right;
  }

  return n;
  return t->root;
}

void rbtree_transplant(rbtree *t, node_t *u, node_t *v)
{
  if (u->parent == t->nil)
  {
    t->root = v;
  }
  else if (u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

node_t *tree_minimum(rbtree *t, node_t *n)
{

  while (n->left != t->nil)
  {
    n = n->left;
  }
  return n;
}

void rbtree_delete_fixup(rbtree *t, node_t *x)
// x는 doubly black
{
  while (x != t->root && x->color == RBTREE_BLACK)
  {
    if (x == x->parent->left)
    {
      node_t *w = x->parent->right; // w는 doubly black의 형제노드
      if (w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        leftRotate(t, x->parent);
        w = x->parent->right; // 경우 1
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        x = x->parent; // 경우 2
      }
      else
      {
        if (w->right->color == RBTREE_BLACK)
        {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          rightRotate(t, w); // 경우 3
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        leftRotate(t, x->parent);
        x = t->root; // 경우 4
      }
    }
    else
    {
      node_t *w = x->parent->left;
      if (w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        rightRotate(t, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else
      {
        if (w->left->color == RBTREE_BLACK)
        {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          leftRotate(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        rightRotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z)
{

  node_t *y = z; // 삭제할 노드 z를 y로 담음 // y가 successor를 찾아가는 얘
  node_t *x;
  color_t y_color = y->color; // y의 색을 담음
  if (z->left == t->nil)      // z의 왼쪽 자식이 nil이면
  {
    x = z->right;
    rbtree_transplant(t, z, z->right);
  }
  else if (z->right == t->nil)
  {
    x = z->left;
    rbtree_transplant(t, z, z->left);
  }
  else
  {
    y = tree_minimum(t, z->right);
    y_color = y->color;
    x = y->right;
    if (y->parent == z)
    {
      x->parent = y;
    }
    else
    {
      rbtree_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rbtree_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if (y_color == RBTREE_BLACK)
  {
    rbtree_delete_fixup(t, x);
  }
  free(z);
  return 0;
}

void tree_to_array(node_t *node, key_t *arr, node_t *nil, int *index, size_t n)
{
  if (node == nil || *index > n)
  {
    return;
  }
  tree_to_array(node->left, arr, nil, index, n);
  if (*index < n)
  {
    arr[(*index)++] = node->key;
  }
  tree_to_array(node->right, arr, nil, index, n);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  int index = 0;
  tree_to_array(t->root, arr, t->nil, &index, n);
  return 1;
}