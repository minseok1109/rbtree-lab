#include "rbtree.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    rbtree *t = new_rbtree();
    rbtree_insert(t, 11);

    return 0;
}