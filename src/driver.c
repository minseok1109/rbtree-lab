#include "rbtree.h"

int main(int argc, char *argv[])
{
    rbtree *t = new_rbtree();
    node_t *n = rbtree_insert(t, 1);
    return 0;
}