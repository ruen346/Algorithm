#ifndef NODE_H
#define NODE_H

#define RED   0
#define BLACK 1

#include <cstddef> // NULL

template <class Type>
class RedBlackTree;

template <class Type>
class Node {
	friend class RedBlackTree<Type>;
public:
	Node() : left(NULL), right(NULL), parent(NULL), color(RED) {}
	Node(Type key, Node<Type>* l = NULL, Node<Type>* r = NULL) {
		this->key = key;
		this->left = l;
		this->right = r;
		this->color = RED;
	}
	Node(Node<Type>& node) {
		key = node.key;
		parent = node.parent;
		left = node.left;
		right = node.right;
		color = node.color;
	}
	~Node() {
		left = right = parent = NULL;
	}

	Type getKey() const { return this->key; }
	Node<Type>* getUncle() {
		Node<Type>* p = this->parent;
		if (!p) return new Node<Type>(-1, NULL, NULL);
		if (this->isLeftNode()) return p->right;
		else return p->left;
	}

	void setRedColor() { this->color = RED; }
	void setBlackColor() { this->color = BLACK; }
	void swapColor(Node<Type>* node) {
		int c = this->color;
		this->color = node->color;
		node->color = c;
	}

	bool isRed() const { return this->color == RED; }
	/* bool isBlack() const { return this->color == BLACK; } */
	bool isLeftNode() const {
		if (this->parent) return this->parent->left == this;
		return false;
	}
	bool isRightNode() const {
		if (this->parent) return this->parent->right == this;
		return false;
	}
	bool isLeaf() const {
		return !this->left || !this->right;
	}
private:
	Type key;
	Node<Type>* left;
	Node<Type>* right;
	Node<Type>* parent;
	int color;
};

#endif

#pragma once

#include "Node.h"

#include <cstdio>
#include <cstddef> // NULL
#include <iostream>

#define CASE_AUTO -2
#define CASE_FAIL -1
#define CASE_ROOT  0
#define CASE_1_1   1
#define CASE_2_1   2
#define CASE_2_4   3
#define CASE_X_2   4
#define CASE_X_3   5

#define INF 987654321

template <class Type>
class RedBlackTree {
public:
	RedBlackTree() {
		Node<Type> *_nil = new Node<Type>(-INF, NULL, NULL);
		nil = new Node<Type>(-INF, _nil, _nil);
		nil->setBlackColor();
		root = nil;
	}
	~RedBlackTree() { root = nil = NULL; }


	void Insert(Type);
	void Delete(Type);
	void Print() { Print(this->root); }
	void Print(Node<Type>* n, int d = 0, bool isLeft = true);

	Node<Type>* getRoot() const { return this->root; }

private:
	Node<Type>* _insert(Node<Type>*, Node<Type>*);
	Node<Type>* _delete(Node<Type>*, bool*);
	Node<Type>* _search(Node<Type>*, Type);
	Node<Type>* _findMaxNode(Node<Type>*);

	void _coloringAfterInsert(Node<Type>*);
	void _coloringAfterDelete(Node<Type>*, int caseNumber = CASE_AUTO);

	int whatCaseOf(Node<Type>*);

	Node<Type>* _rotateLeft(Node<Type>*);
	Node<Type>* _rotateRight(Node<Type>*);

	bool _isNull(Node<Type>*);
	bool _detectDanger(Node<Type>*); // �� ��带 ������� ���, ������ �߻��� �� �ִ°�?

private:
	Node<Type>* root;
	Node<Type>* nil;
};

template <class Type>
void RedBlackTree<Type>::Insert(Type data) {
	if (_isNull(_search(root, data)) == false) {
		std::cout << data << " : Already Exists\n";
		return;
	}

	Node<Type> *newNode = new Node<Type>(data, nil, nil);
	if (!root) {
		root = newNode;
		root->parent = nil;
	}
	else {
		root = _insert(root, newNode);
		_coloringAfterInsert(newNode);
	}
	root->setBlackColor();
	root->parent = nil;
}

template <class Type>
Node<Type>* RedBlackTree<Type>::_insert(Node<Type> *node, Node<Type> *newItem) {
	if (_isNull(node)) {
		node = newItem;
	}
	else if (newItem->getKey() > node->getKey()) {
		Node<Type>* child = _insert(node->right, newItem);
		node->right = child;
		child->parent = node;
	}
	else {
		Node<Type>* child = _insert(node->left, newItem);
		node->left = child;
		child->parent = node;
	}
	return node;
}

template <class Type>
void RedBlackTree<Type>::_coloringAfterInsert(Node<Type> *x) {
	if (_isNull(x) || _isNull(x->parent)) return;
	// ��Ʈ�̰ų� �� ���� ������ ����.
	if (x == root || !x->isRed()) return;
	Node<Type> *p = x->parent;
	// ���� ���� ������ �ڽ��� ���� �� ����. ������ �ʿ��ϴ�.
	if (p == root || !p->isRed()) return;

	// ���Ե� ���� ���� ����, �θ� ��嵵 ������ ��Ȳ

	Node<Type> *s = p->getUncle(), *pp = p->parent;
	// CASE 1 (Double Red)
	if (s->isRed()) {
		p->setBlackColor();
		s->setBlackColor();
		pp->setRedColor();
		_coloringAfterInsert(pp);
	}
	// CASE 2 (Unbalanced)
	else {
		bool xLeft = x->isLeftNode(),
			pLeft = p->isLeftNode();

		// CASE 2-1
		// ������ �������� ��Ȳ (XOR)
		if (xLeft ^ pLeft) {
			if (xLeft)
				_rotateRight(p);
			else
				_rotateLeft(p);
			_coloringAfterInsert(p);
		}
		// CASE 2-2
		else {
			if (pLeft)
				_rotateRight(pp);
			else
				_rotateLeft(pp);
			p->swapColor(pp);
			_coloringAfterInsert(x);
		}
	}
}

template <class Type>
void RedBlackTree<Type>::Delete(Type data) {
	Node<Type> *delNode = _search(root, data);
	if (_isNull(delNode)) {
		std::cerr << data << " : Not Exists\n";
		return;
	}
	bool hasProblem = _detectDanger(delNode);
	Node<Type> *newMid = _delete(delNode, &hasProblem);
	printf("���� �� ���ο� X : %d ", newMid->key);
	printf("(parent: %d)\n", newMid->parent ? newMid->parent->key : -1);
	puts("+--------------------------+");
	puts("���� ���� ��"); Print(root);
	if (hasProblem) {
		puts("���� ���� ��");
		_coloringAfterDelete(newMid);
		Print(root);
	}
	puts("+--------------------------+");
}

template <class Type>
Node<Type>* RedBlackTree<Type>::_delete(Node<Type> *node, bool *hasProblem) {
	if (_isNull(node)) return nil;

	bool hasLeft = !_isNull(node->left),
		hasRight = !_isNull(node->right);

	bool isBlack = node->isRed() == false;

	bool isLeft = node->isLeftNode(),
		isRight = node->isRightNode();

	if (hasLeft && hasRight) {
		Node<Type>* rightMax = _findMaxNode(node->left);

		Node<Type>* newMid = rightMax;
		// ���� ����Ʈ���� �ƿ� ���� ���
		if (_isNull(rightMax)) {
			rightMax = node->right;
		}
		// ���� ����Ʈ������ ���� ��常 �ִ� ���
		else if (rightMax == node->left) {
			if (isLeft) {
				rightMax->parent = node->parent;
				rightMax->parent->left = rightMax;
			}
			else {
				rightMax->parent = node->parent;
				rightMax->parent->right = rightMax;
			}
			rightMax->right = node->right;

			rightMax->left->parent = rightMax;
			newMid = rightMax->left;
			printf("[%d] is %s\n", rightMax->key, rightMax->isRed() ? "RED" : "BLACK");
			*hasProblem |= rightMax->isRed() == false;
		}
		else {
			// ���� ������ ����� ���� ����Ʈ���� �θ�� �������ش�. (������ ����)
			rightMax->parent->right = rightMax->left;
			rightMax->left->parent = rightMax->parent;

			// ������� ����� �ڸ��� ��ü
			rightMax->left = node->left;
			rightMax->right = node->right;
		}
		rightMax->parent = node->parent;
		rightMax->right->parent = rightMax->left->parent = rightMax;

		if (node == root) {
			root = rightMax;
		}
		else {
			if (isLeft)
				rightMax->parent->left = rightMax;
			else
				rightMax->parent->right = rightMax;
		}
		node->swapColor(rightMax);
		delete node;
		return newMid;
	}
	else if (hasLeft && hasRight == false) {
		Node<Type>* cur = node;
		cur = cur->left;
		cur->parent = node->parent;
		if (node == root) {
			root = cur;
			root->parent = nil;
		}
		else {
			if (isLeft) cur->parent->left = cur;
			else cur->parent->right = cur;
		}

		// ������ �ڽĳ�尡 ������ �������� �ʴ´�.
		*hasProblem &= cur->isRed() == false;
		node->swapColor(cur);
		delete node;

		cur->right->parent = cur;
		return cur->right;
	}
	else if (hasLeft == false && hasRight) {
		Node<Type>* cur = node;
		cur = cur->right;
		cur->parent = node->parent;
		if (node == root) {
			root = cur;
			root->parent = nil;
		}
		else {
			if (isLeft) cur->parent->left = cur;
			else cur->parent->right = cur;
		}

		// ������ �ڽĳ�尡 ������ �������� �ʴ´�.
		*hasProblem &= cur->isRed() == false;
		node->swapColor(cur);
		delete node;

		cur->left->parent = cur;
		return cur->left;
	}
	else {
		Node<Type>* p = node->parent, *ret = nil;
		if (node == root) root = nil;
		else if (isLeft) {
			p->left = ret;
			p->left->parent = p;
		}
		else {
			p->right = ret;
			p->right->parent = p;
		}
		delete node;

		return ret;
	}
}

template <class Type>
void RedBlackTree<Type>::_coloringAfterDelete(Node<Type> *x, int caseNumber) {
	if (caseNumber == CASE_AUTO)
		caseNumber = whatCaseOf(x);

	// �� ��尡 �ƴ� ���� ��尡 �Է¿� ���´ٸ�
	if (x->isRed()) {
		// �ڱ� �տ� ���� �����ŹǷ� �ڽ��� ����� �ٲ۴�.
		printf("�����θ� ������ �ٲٸ� �ذ�˴ϴ�. (������: %d (parent :%d))\n", x->key, x->parent->key);
		x->setBlackColor();
		return;
	}

	char str[8][5] = { "AUTO", "FAIL", "ROOT", "1-1", "2-1", "2-4", "*-2", "*-3" };
	printf("CASE %s�� ���� �˻��մϴ�. (������: %d (parent: %d))\n", str[caseNumber - CASE_AUTO], x->key, x->parent->key);

	bool isLeft = x->isLeftNode();

	Node<Type> *p = x->parent, *s = x->getUncle();
	Node<Type> *l = nil, *r = nil;
	if (_isNull(p)) s = nil;
	if (_isNull(s) == false) {
		if (isLeft) {
			l = s->left;
			r = s->right;
		}
		else {
			l = s->right;
			r = s->left;
		}
	}

	switch (caseNumber) {
	case CASE_1_1:
		p->swapColor(s);
		break;
	case CASE_X_2:
		isLeft ? _rotateLeft(p) : _rotateRight(p);
		p->swapColor(s);
		r->setBlackColor();
		break;
	case CASE_X_3:
		isLeft ? _rotateRight(s) : _rotateLeft(s);
		s->swapColor(l);
		x->parent = p;
		_coloringAfterDelete(x, CASE_X_2);
		break;
	case CASE_2_1:
		s->setRedColor();
		_coloringAfterDelete(p);
		break;
	case CASE_2_4:
		isLeft ? _rotateLeft(p) : _rotateRight(p);
		p->swapColor(s);
		// CASE 1-1, 1-2, 1-3 �� �ϳ���..
		_coloringAfterDelete(x);
		break;
	case CASE_ROOT:
		if (_isNull(x->left)) {
			x->left->parent = x;
			_coloringAfterDelete(x->left);
		}
		else {
			x->right->parent = x;
			_coloringAfterDelete(x->right);
		}
		break;
	case CASE_FAIL:
		break;
	}
}

template <class Type>
Node<Type>* RedBlackTree<Type>::_search(Node<Type> *node, Type data) {
	if (_isNull(node)) return nil;

	Type key = node->key;
	if (key == data) return node;
	else if (key < data) return _search(node->right, data);
	else return _search(node->left, data);
}

template <class Type>
Node<Type>* RedBlackTree<Type>::_findMaxNode(Node<Type> *node) {
	if (_isNull(node->right))
		return node;
	return _findMaxNode(node->right);
}

template <class Type>
int RedBlackTree<Type>::whatCaseOf(Node<Type> *nodeX) {
	bool isParentRed = false; // p
	bool isUncleRed = false; // s
	bool isCousinCloseRed = false; // x�� ������ �� ����, l
	bool isCousinFarRed = false; // x�� ������ �� ����, r

	Node<Type>* p = nodeX->parent;
	if (_isNull(p) == false) {
		isParentRed |= p->isRed();
		Node<Type>* s = nodeX->getUncle();
		if (_isNull(s) == false) {
			isUncleRed |= s->isRed();

			// �켱, x�� ������ �� �������� ���¸� ����
			isCousinCloseRed |= _isNull(s->left) == false && s->left->isRed();
			isCousinFarRed |= _isNull(s->right) == false && s->right->isRed();

			// �¿� ������ ��쿡 ���� ó��
			if (s->isLeftNode()) {
				std::swap(isCousinCloseRed, isCousinFarRed);
			}
		}
		else {
			isUncleRed = true; // leaf is black
		}
	}
	else {
		return CASE_ROOT;
	}

	if (isParentRed && !isUncleRed) {
		// CASE 1:
		// p�� ����(s�� �ݵ�� ��), <l�� ����, r�� ����>�� ����
		if (isCousinFarRed) return CASE_X_2;
		if (isCousinCloseRed) return CASE_X_3;
		return CASE_1_1;
	}
	else if (!isParentRed) {
		// CASE 2:
		// p�� �� <s�� ����, l�� ����, r�� ����>�� ����
		if (isUncleRed) {
			if (isCousinCloseRed || isCousinFarRed) return CASE_FAIL;
			// s�� �����̸� l�� r�� �ݵ�� ���̾�� �Ѵ�.
			return CASE_2_4;
		}
		if (isCousinFarRed) return CASE_X_2;
		if (isCousinCloseRed) return CASE_X_3;
		return CASE_2_1;
	}

	return CASE_FAIL;
}

template <class Type>
bool RedBlackTree<Type>::_detectDanger(Node<Type> *x) {
	if (_isNull(x)) return false;

	// ���� ��尡 �����̸� ���� ����.
	if (x->isRed()) return false;

	// ��� x�� ��Ʈ�̸� ������ ����
	Node<Type> *p = x->parent;
	if (x == root || _isNull(p)) return false;

	bool hasLeft = _isNull(x->left),
		hasRight = _isNull(x->right);

	// ���� ��尡 ���̴���, �ڽ��� ������ ��� ����.
	if (!hasLeft && !hasRight) return false;

	bool hasBlackChild = false;
	if (hasLeft) {
		hasBlackChild |= x->left->isRed() == false;
	}
	if (hasRight) {
		hasBlackChild |= x->right->isRed() == false;
	}

	// ���� �ڽ��� �ϳ��� �ִٸ� ������ �����.
	return hasBlackChild;
}

template <class Type>
Node<Type>* RedBlackTree<Type>::_rotateRight(Node<Type> *x) {
	if (_isNull(x)) return x;
	Node<Type> *l = x->left, *r = x->right, *p = x->parent;

	bool isLeft = x->isLeftNode();

	x->left = l->right;
	x->left->parent = x;
	l->right = x;
	l->right->parent = l;

	// (�θ�/�ڽ� ���踦 ����)
	// �������� �߽��� ��Ʈ���ٸ� ��Ʈ�� ����
	if (x == root) {
		root = l;
		root->parent = nil;
	}
	else {
		l->parent = p;
		if (isLeft) p->left = l;
		else p->right = l;
	}

	// ���ο� �߽��� ��ȯ�Ѵ�.
	return l;
}

template <class Type>
Node<Type>* RedBlackTree<Type>::_rotateLeft(Node<Type> *x) {
	if (_isNull(x)) return x;
	Node<Type> *l = x->left, *r = x->right, *p = x->parent;

	bool isLeft = x->isLeftNode();

	x->right = r->left;
	x->right->parent = x;
	r->left = x;
	r->left->parent = r;

	if (x == root) {
		root = r;
		root->parent = nil;
	}
	else {
		r->parent = p;
		if (isLeft) p->left = r;
		else p->right = r;
	}

	// ���ο� �߽��� ��ȯ�Ѵ�.
	return r;
}

template <class Type>
void RedBlackTree<Type>::Print(Node<Type> *n, int dep, bool isLeft) {
	if (_isNull(n)) return;
	for (int i = 0; i < dep; ++i) std::cout << "    ";
	std::cout << n->key << (n->isRed() ? "[R]" : "[B]") << '\n';
	Print(n->left, dep + 1);
	Print(n->right, dep + 1, false);
}

template <class Type>
bool RedBlackTree<Type>::_isNull(Node<Type> *x) {
	return x == NULL || x == nil;
}

#include <cstdio>
#include <iostream>
using namespace std;

int main() {
	char cmd;
	int number;
	RedBlackTree<int> rbtree;
	while (1) 
	{
		cout << "i���� d���� �Դϴ�. �Է��ϼ��� : " << endl;
		cin >> cmd;

		if (cmd == 'x') break;

		if (cmd == 'i') {
			cout << "������ ��ȣ�� �Է��ϼ��� : ";
			cin >> number;
			rbtree.Insert(number);
		}
		else if (cmd == 'd') {
			cout << "������ ��ȣ�� �Է��ϼ��� : ";
			cin >> number;
			rbtree.Delete(number);
		}

		// print for debug
		cout << "####################################################" << endl;
		rbtree.Print();
	}
	return 0;
}