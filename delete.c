#include "rbt.h"

/* The LEFT subtree of *node is one black node short.
   Fix it using the sibling (right child). Sets *db = 0 if fixed,
   leaves *db = 1 if the shortage moves up to the parent. */
static void fix_left_short(tree_t **node, int *db)
{
	tree_t *p = *node;
	tree_t *s = p->right;

	if (IS_RED(s))                              /* Case A: red sibling */
	{
		s->color = BLACK;
		p->color = RED;
		rotate_left(node);                      /* s is now on top, p is its left child */
		fix_left_short(&(*node)->left, db);     /* now p has a black sibling */
		return;
	}

	if (!IS_RED(s->left) && !IS_RED(s->right))  /* Case B: black sibling, black nephews */
	{
		s->color = RED;
		if (p->color == RED)
		{
			p->color = BLACK;
			*db = 0;
		}
		/* else: p was black, shortage moves up */
		return;
	}

	if (!IS_RED(s->right))                      /* Case C: far nephew black, near nephew red */
	{
		tree_t *r = s->left;
		r->color = BLACK;
		s->color = RED;
		rotate_right(&p->right);
		s = p->right;
	}

	/* Case D: far nephew is red */
	s->color = p->color;
	p->color = BLACK;
	s->right->color = BLACK;
	rotate_left(node);
	*db = 0;
}

/* Mirror image: the RIGHT subtree is one black node short. */
static void fix_right_short(tree_t **node, int *db)
{
	tree_t *p = *node;
	tree_t *s = p->left;

	if (IS_RED(s))
	{
		s->color = BLACK;
		p->color = RED;
		rotate_right(node);
		fix_right_short(&(*node)->right, db);
		return;
	}

	if (!IS_RED(s->left) && !IS_RED(s->right))
	{
		s->color = RED;
		if (p->color == RED)
		{
			p->color = BLACK;
			*db = 0;
		}
		return;
	}

	if (!IS_RED(s->left))
	{
		tree_t *r = s->right;
		r->color = BLACK;
		s->color = RED;
		rotate_left(&p->left);
		s = p->left;
	}

	s->color = p->color;
	p->color = BLACK;
	s->left->color = BLACK;
	rotate_right(node);
	*db = 0;
}

/* *db is set to 1 if the black height of this subtree dropped by one */
static int delete_rec(tree_t **node, data_t item, int *db)
{
	tree_t *n = *node;
	int status;

	*db = 0;
	if (n == NULL)
		return FAILURE;

	if (item < n->data)
	{
		status = delete_rec(&n->left, item, db);
		if (*db)
			fix_left_short(node, db);
		return status;
	}

	if (item > n->data)
	{
		status = delete_rec(&n->right, item, db);
		if (*db)
			fix_right_short(node, db);
		return status;
	}

	/* Found the node */
	if (n->left && n->right)
	{
		/* Two children: copy the smallest value of the right subtree here,
		   then delete that value from the right subtree */
		tree_t *m = n->right;
		while (m->left)
			m = m->left;
		n->data = m->data;
		status = delete_rec(&n->right, m->data, db);
		if (*db)
			fix_right_short(node, db);
		return status;
	}

	/* Zero or one child */
	tree_t *child = n->left ? n->left : n->right;

	if (n->color == RED)                /* red node has no children here */
	{
		*node = NULL;
		*db = 0;
	}
	else if (child)                     /* black node with one red child */
	{
		child->color = BLACK;
		*node = child;
		*db = 0;
	}
	else                                /* black leaf: black height drops */
	{
		*node = NULL;
		*db = 1;
	}
	free(n);
	return SUCCESS;
}

int delete(tree_t **root, data_t item)
{
	int db;
	int status = delete_rec(root, item, &db);

	if (*root)
		(*root)->color = BLACK;

	return status;
}
