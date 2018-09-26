#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//이진검색트리노드
typedef struct treenode {
	int data;
	struct treenode* left;
	struct treenode* right;
}treenode;

treenode* insertnode(treenode* root, int data); //이진 검색 트리 노드추가
void deletenode(treenode* root, int data); //이진검색트리 삭제

void preorder(treenode* node); //전위순회
void inorder(treenode* node); //중위순회
void postorder(treenode* node); //후위순회

int maxValue(int a, int b); //큰 값 찾기


//이진검색트리 삭제
void deletenode(treenode* root, int data)
{
	treenode* del = NULL; //삭제 노드
	treenode* p = NULL; //삭제 노드의  부모 노드

	treenode* max_left = NULL; //왼쪽 서브트리 중 가장 큰 노드
	treenode* p_max_left = NULL; //max_left 부모 노드

	while (1)
	{
		if (root == NULL) //NULL인 경우-삭제 노드 못 찾은 경우
		{
			printf("삭제 노드를 찾지 못했습니다.\n");
			return;
		}
		else if (root->left != NULL && root->left->data == data)
			//왼쪽 자식이 삭제 노드일 경우
		{
			del = root->left;
			p = root;
			break;
		}
		else if (root->right != NULL && root->right->data == data)
			//오른쪽 자식이 삭제 노드일 경우
		{
			del = root->right;
			p = root;
			break;
		}
		if (data < root->data) //root노드보다 작은 수인경우
			root = root->left; //왼쪽 자식으로 이동
		else if (data > root->data) //root노드보다 큰 수인경우
			root = root->right; //오른쪽 자식으로 이동
	}

	//====================후속 처리 시작===========================
	if (del->right == NULL && del->left == NULL) //삭제 노드가 단노드일 경우
	{
		if (p->right != NULL && p->right == del) //오른쪽 자식노드가 삭제 노드인 경우
			p->right = NULL; //삭제 노드의 부모 노드 오른쪽 연결 해제
		else//왼쪽 자식 노드가 삭제 노드일 경우
			p->left = NULL; //삭제 노드의 부모 노드 왼쪽 연결 해제
	}

	else if ((del->right == NULL && del->left != NULL) || (del->right != NULL && del->left == NULL))
		//삭제하고자 하는 노드의 자식노드가 한개인 경우
	{
		if (del->right != NULL) //오른쪽 자식이 존재하는 경우
		{
			if (p->right == del) //오른쪽 자식노드가 삭제 노드인 경우
				p->right = del->right; //삭제 노드 대신 삭제 노드의 자식 노드 연결
			else //왼쪽 자식노드가 삭제 노드인 경우
				p->left = del->right; //삭제 노드 대신 삭제 노드의 자식 노드 연결
		}
		else //왼쪽 자식이 존재하는 경우
		{
			if (p->right == del) //오른쪽 자식노드가 삭제 노드인 경우
				p->right = del->left; //삭제 노드 대신 삭제 노드의 자식 노드 연결
			else //왼쪽 자식노드가 삭제 노드인 경우
				p->left = del->left; //삭제 노드 대신 삭제 노드의 자식 노드 연결
		}
	}

	else 
	{
		max_left = del->left;
		p_max_left = del;

		while (max_left->right != NULL)	//max_left의 오른쪽 자식이 존재하는 경우 반복
										//왼쪽 서브트리의 가장 큰 노드 찾는 과정
		{
			p_max_left = max_left;
			max_left = max_left->right;
		}

		if (del->left == max_left)
			//삭제 노드의 왼쪽 자식이 왼쪽 서브트리의 최대 값일 경우
		{
			max_left->right = del->right;
			//최대 노드의 오른쪽 자식에 삭제 노드의 오른쪽 자식 연결
		}

		else
			//삭제 노드의 왼쪽 자식이 왼쪽 서브트리의 최대 값이 아닌 경우
		{
			p_max_left->right = NULL;
			//최대값 노드와 부모 노드 연결 해제 
			max_left->left = del->left;
			max_left->right = del->right;
			//최대값 노드 삭제 노드 위치에 삽입
		}

		if (p->right == del) //오른쪽 자식이 삭제 노드일 경우
			p->right = max_left; //부모노드에 새로 삽입한 노드 연결
		else //왼쪽 자식이 삭제 노드일 경우
			p->left = max_left;//부모노드에 새로 삽입한 노드 연결			
	}
	//============================================================

	free(del); //노드 삭제	
	printf("삭제하였습니다.\n");
}

//이진트리 노드추가
treenode* insertnode(treenode* root, int data)
{
	treenode* n;
	if (root == NULL) { //트리 처음 생성하는 경우
		n = (treenode*)malloc(sizeof(treenode));
		n->data = data;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	else if (data < root->data) //root노드보다 작은 수인경우
		root->left = insertnode(root->left, data); //왼쪽 자식으로 이동
	else if (data > root->data) //root노드보다 큰 수인경우
		root->right = insertnode(root->right, data); //오른쪽 자식으로 이동
	else //data와 같은 노드인 경우
		printf("이미존재하는노드입니다.\n");

	return root;
}

//전위순회
void preorder(treenode* node)
{
	printf("%d ", node->data);
	if (node->left)	preorder(node->left);
	if (node->right)	preorder(node->right);
}

//중위순회
void inorder(treenode* node)
{
	if (node->left)	inorder(node->left);
	printf("%d ", node->data);
	if (node->right)	inorder(node->right);
}

//후위순회
void postorder(treenode* node)
{
	if (node->left)	postorder(node->left);
	if (node->right)	postorder(node->right);
	printf("%d ", node->data);
}


//큰 값 찾기
int maxValue(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

//메인 함수
int main()
{
	int data = 0;
	treenode* root = NULL;
	treenode* find = NULL;

	printf("==이진 탐색 트리==\n");
	printf("루트 데이터 입력 : ");
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
	printf("삭제 하고자 하는 노드 데이터 : ");
	scanf("%d", &data);
	deletenode(root, data);

	printf("1. Preorder : "); preorder(root); printf("\n");
	printf("2. Inorder : "); inorder(root); printf("\n");
	printf("3. Postorder : "); postorder(root); printf("\n");
	printf("\n");

	return 0;
}