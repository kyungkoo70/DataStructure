#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *left;
	struct node *right;
};

struct node *root = 0;

#define STACK_SZ 10
struct node *stack[STACK_SZ];

int top = -1;

void push(struct node *n)
{
	if (top == STACK_SZ - 1)
	{
		printf("stack full, abort\n");
		return;
	}
	top++;
	stack[top] = n;
}

struct node *popClear()
{
	int temp;
	if (top == -1)
	{
		printf("stack empty\n");
		return 0;
	}
	temp = top;
	top = -1;
	return stack[temp];
}

struct node *createBSTNode(int v)
{
	struct node *n = (struct node *)malloc(sizeof(struct node));
	n->data = v;
	n->left = n->right = 0;
	return n;
}

void addToBST(int v)
{
	struct node *cur = createBSTNode(v);
	struct node *p = root;
	if (root == 0)
	{
		root = cur;
		return;
	}

	while (1)
	{
		if (p->data > v)
		{
			if (p->left == 0)
			{
				p->left = cur;
				return;
			}
			else
			{
				p = p->left;
			}
		}
		else
		{
			if (p->right == 0)
			{
				p->right= cur;
				return;
			}
			else
			{
				p = p->right;
			}
		}
	}
}

void inorderTraversal(struct node *n)
{
	if (n == 0)
	{
		return;
	}
	inorderTraversal(n->left);
	printf("%d\n", n->data);
	inorderTraversal(n->right);
}

// find node which has the data of v
// return 0 if no such node has the value of v
struct node *findNode(int v)
{
	struct node *p = root;

	while (1)
	{
		if (p == 0)
		{
			return 0;
		}
		if (p->data == v)
		{
			return p;
		}
		else if (p->data > v)
		{
			push(p);
			p = p->left;
		}
		else if (p->data < v)
		{
			push(p);
			p = p->right;
		}
	}
}

struct node *findLeast(struct node *n)
{
	struct node *p = n->right;
	push(n);
	while (p->left != 0)
	{
		push(p);
		p = p->left;
	}
	return p;
}

void reconnect(struct node *p, struct node *c, struct node *n)
{
	if (p->left == c)
	{
		p->left = n;
	}
	else
	{
		p->right = n;
	}
	free(c);
	return;
}

void removeNodeNonRecursive(int v)
{
	struct node *toBeRemoved = findNode(v);
	if (toBeRemoved == 0)
	{
		printf("Unable to find the node having %d\n", v);
		return;
	}
	struct node *pNode = popClear();
	if (pNode == 0)  // the node to be deleted is root
	{
		if (toBeRemoved->left == 0 && toBeRemoved->right == 0)
		{
			free(toBeRemoved);
			root = 0;
			return;
		}
		else if (toBeRemoved->left != 0 && toBeRemoved->right == 0)
		{
			root = toBeRemoved->left;
			free(toBeRemoved);
			return;
		}
		else if (toBeRemoved->left == 0 && toBeRemoved->right != 0)
		{
			root = toBeRemoved->right;
			free(toBeRemoved);
			return;
		}
		//else
		//{
		//	struct node *successor = findLeast(toBeRemoved);
		//	struct node *parent_succssor = popClear();
		//	// copy from successor to toBeRemoved
		//	toBeRemoved->data = successor->data;

		//	// now, lets remove the successor
		//	if (successor->left == 0 && sucessor->right == 0)
		//	{
		//		reconnect(parent_successor, successor, 0);
		//	}
		//	else if (successor->left != 0 && successor->right == 0)
		//	{
		//		reconnect(parent_successor, successor, successor->left);
		//	}
		//	else if (successor->left == 0 && successor->right != 0)
		//	{
		//		reconnect(parent_successor, successor, successor->right);
		//	}
		//}
	}
	//else
	{
		if (toBeRemoved->left == 0 && toBeRemoved->right == 0)
		{
			reconnect(pNode, toBeRemoved, 0);
		}
		else if (toBeRemoved->left != 0 && toBeRemoved->right == 0)
		{
			reconnect(pNode, toBeRemoved, toBeRemoved->left);
		}
		else if (toBeRemoved->left == 0 && toBeRemoved->right != 0)
		{
			reconnect(pNode, toBeRemoved, toBeRemoved->right);
		}
		else // both child is alive
		{
			struct node *successor = findLeast(toBeRemoved);
			struct node *parent_successor = popClear();
			// copy from successor to toBeRemoved
			toBeRemoved->data = successor->data;

			// now, lets remove the successor
			if (successor->left == 0 && successor->right == 0)
			{
				reconnect(parent_successor, successor, 0);
			}
			else if (successor->left != 0 && successor->right == 0)
			{
				reconnect(parent_successor, successor, successor->left);
			}
			else if (successor->left == 0 && successor->right != 0)
			{
				reconnect(parent_successor, successor, successor->right);
			}
		}
	}
}

int main(void)
{
	addToBST(10);
	addToBST(5);
	addToBST(15);
	addToBST(1);
	addToBST(7);
	//addToBST(13);
	addToBST(17);

	//inorderTraversal(root);

	removeNodeNonRecursive(15);
	inorderTraversal(root);

	return 0;
}