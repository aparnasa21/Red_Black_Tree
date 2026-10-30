#include "rbt.h"

/* 'g_link' points to the link that points at the grandparent. Check g's
   children for a red node with a red child and fix it. */
static void fix_insert(tree_t **g_link)
{
	tree_t *g = *g_link;

	if (g->color == RED)
		return;

	if (IS_RED(g->left) && (IS_RED(g->left->left) || IS_RED(g->left->right)))
	{
		if (IS_RED(g->right))                    /* Case 1: uncle red */
		{
			g->left->color = BLACK;
			g->right->color = BLACK;
			g->color = RED;
		}
		else
		{
			if (IS_RED(g->left->right))          /* Case 2: triangle */
				rotate_left(&g->left);
			rotate_right(g_link);                /* Case 3: line */
			(*g_link)->color = BLACK;
			g->color = RED;
		}
	}
	else if (IS_RED(g->right) && (IS_RED(g->right->left) || IS_RED(g->right->right)))
	{
		if (IS_RED(g->left))                     /* Case 1 */
		{
			g->right->color = BLACK;
			g->left->color = BLACK;
			g->color = RED;
		}
		else
		{
			if (IS_RED(g->right->left))          /* Case 2 */
				rotate_right(&g->right);
			rotate_left(g_link);                 /* Case 3 */
			(*g_link)->color = BLACK;
			g->color = RED;
		}
	}
}

static int insert_rec(tree_t **node, data_t item)
{
	int status;

	if (*node == NULL)
	{
		tree_t *new = malloc(sizeof(tree_t));
		if (new == NULL)
			return FAILURE;
		new->data = item;
		new->left = new->right = NULL;
		new->color = RED;
		*node = new;
		return SUCCESS;
	}

	if (item == (*node)->data)
		return FAILURE;

	if (item < (*node)->data)
		status = insert_rec(&(*node)->left, item);
	else
		status = insert_rec(&(*node)->right, item);

	if (status == SUCCESS)
		fix_insert(node);

	return status;
}

int insert(tree_t **root, data_t item)
{
	int status = insert_rec(root, item);

	if (status == SUCCESS)
		(*root)->color = BLACK;

	return status;
}
