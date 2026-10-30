#include "rbt.h"

static void print_helper(tree_t *root, int level)
{
	if (root == NULL)
		return;

	print_helper(root->right, level + 1);

	for (int i = 0; i < level; i++)
		printf("    ");
	printf("%d(%c)\n", root->data, root->color == RED ? 'R' : 'B');

	print_helper(root->left, level + 1);
}

void print_tree(tree_t *root)
{
	if (root == NULL)
	{
		printf("Tree is empty\n");
		return;
	}
	print_helper(root, 0);
}
