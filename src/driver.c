#include "rbtree.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    rbtree *t = new_rbtree();
    rbtree_insert(t, 1);
    rbtree_insert(t, 2);
    rbtree_insert(t, 3);
    rbtree_insert(t, 4);
    rbtree_insert(t, 5);
    node_t *find = rbtree_find(t, 1);
    rbtree_erase(t, find);

    return 0;
}