#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//�����˻�Ʈ�����
typedef struct treenode {
	int data;
	struct treenode* left;
	struct treenode* right;
}treenode;

treenode* insertnode(treenode* root, int data); //���� �˻� Ʈ�� ����߰�
void deletenode(treenode* root, int data); //�����˻�Ʈ�� ����

void preorder(treenode* node); //������ȸ
void inorder(treenode* node); //������ȸ
void postorder(treenode* node); //������ȸ

int maxValue(int a, int b); //ū �� ã��


//�����˻�Ʈ�� ����
void deletenode(treenode* root, int data)
{
	treenode* del = NULL; //���� ���
	treenode* p = NULL; //���� �����  �θ� ���

	treenode* max_left = NULL; //���� ����Ʈ�� �� ���� ū ���
	treenode* p_max_left = NULL; //max_left �θ� ���

	while (1)
	{
		if (root == NULL) //NULL�� ���-���� ��� �� ã�� ���
		{
			printf("���� ��带 ã�� ���߽��ϴ�.\n");
			return;
		}
		else if (root->left != NULL && root->left->data == data)
			//���� �ڽ��� ���� ����� ���
		{
			del = root->left;
			p = root;
			break;
		}
		else if (root->right != NULL && root->right->data == data)
			//������ �ڽ��� ���� ����� ���
		{
			del = root->right;
			p = root;
			break;
		}
		if (data < root->data) //root��庸�� ���� ���ΰ��
			root = root->left; //���� �ڽ����� �̵�
		else if (data > root->data) //root��庸�� ū ���ΰ��
			root = root->right; //������ �ڽ����� �̵�
	}

	//====================�ļ� ó�� ����===========================
	if (del->right == NULL && del->left == NULL) //���� ��尡 �ܳ���� ���
	{
		if (p->right != NULL && p->right == del) //������ �ڽĳ�尡 ���� ����� ���
			p->right = NULL; //���� ����� �θ� ��� ������ ���� ����
		else//���� �ڽ� ��尡 ���� ����� ���
			p->left = NULL; //���� ����� �θ� ��� ���� ���� ����
	}

	else if ((del->right == NULL && del->left != NULL) || (del->right != NULL && del->left == NULL))
		//�����ϰ��� �ϴ� ����� �ڽĳ�尡 �Ѱ��� ���
	{
		if (del->right != NULL) //������ �ڽ��� �����ϴ� ���
		{
			if (p->right == del) //������ �ڽĳ�尡 ���� ����� ���
				p->right = del->right; //���� ��� ��� ���� ����� �ڽ� ��� ����
			else //���� �ڽĳ�尡 ���� ����� ���
				p->left = del->right; //���� ��� ��� ���� ����� �ڽ� ��� ����
		}
		else //���� �ڽ��� �����ϴ� ���
		{
			if (p->right == del) //������ �ڽĳ�尡 ���� ����� ���
				p->right = del->left; //���� ��� ��� ���� ����� �ڽ� ��� ����
			else //���� �ڽĳ�尡 ���� ����� ���
				p->left = del->left; //���� ��� ��� ���� ����� �ڽ� ��� ����
		}
	}

	else 
	{
		max_left = del->left;
		p_max_left = del;

		while (max_left->right != NULL)	//max_left�� ������ �ڽ��� �����ϴ� ��� �ݺ�
										//���� ����Ʈ���� ���� ū ��� ã�� ����
		{
			p_max_left = max_left;
			max_left = max_left->right;
		}

		if (del->left == max_left)
			//���� ����� ���� �ڽ��� ���� ����Ʈ���� �ִ� ���� ���
		{
			max_left->right = del->right;
			//�ִ� ����� ������ �ڽĿ� ���� ����� ������ �ڽ� ����
		}

		else
			//���� ����� ���� �ڽ��� ���� ����Ʈ���� �ִ� ���� �ƴ� ���
		{
			p_max_left->right = NULL;
			//�ִ밪 ���� �θ� ��� ���� ���� 
			max_left->left = del->left;
			max_left->right = del->right;
			//�ִ밪 ��� ���� ��� ��ġ�� ����
		}

		if (p->right == del) //������ �ڽ��� ���� ����� ���
			p->right = max_left; //�θ��忡 ���� ������ ��� ����
		else //���� �ڽ��� ���� ����� ���
			p->left = max_left;//�θ��忡 ���� ������ ��� ����			
	}
	//============================================================

	free(del); //��� ����	
	printf("�����Ͽ����ϴ�.\n");
}

//����Ʈ�� ����߰�
treenode* insertnode(treenode* root, int data)
{
	treenode* n;
	if (root == NULL) { //Ʈ�� ó�� �����ϴ� ���
		n = (treenode*)malloc(sizeof(treenode));
		n->data = data;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	else if (data < root->data) //root��庸�� ���� ���ΰ��
		root->left = insertnode(root->left, data); //���� �ڽ����� �̵�
	else if (data > root->data) //root��庸�� ū ���ΰ��
		root->right = insertnode(root->right, data); //������ �ڽ����� �̵�
	else //data�� ���� ����� ���
		printf("�̹������ϴ³���Դϴ�.\n");

	return root;
}

//������ȸ
void preorder(treenode* node)
{
	printf("%d ", node->data);
	if (node->left)	preorder(node->left);
	if (node->right)	preorder(node->right);
}

//������ȸ
void inorder(treenode* node)
{
	if (node->left)	inorder(node->left);
	printf("%d ", node->data);
	if (node->right)	inorder(node->right);
}

//������ȸ
void postorder(treenode* node)
{
	if (node->left)	postorder(node->left);
	if (node->right)	postorder(node->right);
	printf("%d ", node->data);
}


//ū �� ã��
int maxValue(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

//���� �Լ�
int main()
{
	int data = 0;
	treenode* root = NULL;
	treenode* find = NULL;

	printf("==���� Ž�� Ʈ��==\n");
	printf("��Ʈ ������ �Է� : ");
	scanf("%d", &data);
	root = insertnode(root, 5);

	insertnode(root, 6);
	insertnode(root, 1);
	insertnode(root, 3);
	insertnode(root, 9);
	insertnode(root, 7);


	printf("1. Preorder : "); preorder(root); printf("\n");
	printf("2. Inorder : "); inorder(root); printf("\n");
	printf("3. Postorder : "); postorder(root); printf("\n");
	printf("\n");


	printf("\n");
	printf("���� �ϰ��� �ϴ� ��� ������ : ");
	scanf("%d", &data);
	deletenode(root, data);

	printf("1. Preorder : "); preorder(root); printf("\n");
	printf("2. Inorder : "); inorder(root); printf("\n");
	printf("3. Postorder : "); postorder(root); printf("\n");
	printf("\n");

	return 0;
}