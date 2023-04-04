#include "rbtree.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    rbtree *t = new_rbtree();
    rbtree_insert(t, 10);
    rbtree_insert(t, 20);
    rbtree_insert(t, 5);
    rbtree_insert(t, 30);
    rbtree_insert(t, 40);
    node_t *x = rbtree_min(t);
    node_t *y = rbtree_max(t);

    return 0;
}