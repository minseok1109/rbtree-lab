#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    rbtree *t = new_rbtree();
    rbtree_insert(t, 1);
    rbtree_insert(t, 2);
    rbtree_insert(t, 3);
    rbtree_insert(t, 4);
    rbtree_insert(t, 5);
    key_t *res = calloc(4, sizeof(key_t));
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", res[i]);
    }
    rbtree_to_array(t, res, 4);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", res[i]);
    }
    return 0;
}