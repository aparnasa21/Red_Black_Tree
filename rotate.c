#include "rbt.h"

void rotate_left(tree_t **node)
{
	tree_t *x = *node;
	tree_t *y = x->right;

	x->right = y->left;
	y->left = x;
	*node = y;
}

void rotate_right(tree_t **node)
{
	tree_t *y = *node;
	tree_t *x = y->left;

	y->left = x->right;
	x->right = y;
	*node = x;
}
