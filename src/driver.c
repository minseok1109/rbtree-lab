#include "rbtree.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    rbtree *t = new_rbtree();
    rbtree_insert(t, 10);
    rbtree_insert(t, 20);
    rbtree_insert(t, 10);
    rbtree_insert(t, 30);

    return 0;
}