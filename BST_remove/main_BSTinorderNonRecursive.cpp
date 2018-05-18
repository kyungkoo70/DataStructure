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

struct node *pop()
{
	if (top == -1)
	{
		printf("stack empty\n");
		return 0;
	}
	top--;
	return stack[top+1];
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

void inorderNonRecursive(struct node *n)
{
	struct node *p = n;

	while (1)
	{
		if (p == 0)
		{
			p = pop();
			if (p == 0)
			{
				return;
			}
			else
			{
				printf("%d\n", p->data);
				p = p->right;
				continue;
			}
		}

		if (p->left != 0)
		{
			push(p);
			p = p->left;
		}
		else if (p->left == 0)
		{
			printf("%d\n", p->data);
			p = p->right;
		}
	}
}

int main(void)
{
	addToBST(10);
	addToBST(5);
	addToBST(15);
	addToBST(1);
	//addToBST(7);
	//addToBST(13);
	addToBST(17);

	printf("-------------------Recursive Inorder\n");
	inorderTraversal(root);
	
	printf("-------------------NonRecursive Inorder\n");
	inorderNonRecursive(root);

	return 0;
}