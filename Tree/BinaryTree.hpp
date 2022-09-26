//摆烂了，有问题找不到，只能放弃
#pragma once
#include<string>
#include<stack>
#include<iostream>

template<class T>
struct BinaryTree;

template<class T>
class Node {
public:
	T data;
	Node* left = nullptr;
	Node* right = nullptr;
public:
	Node(T ch) : data(ch) {}
	~Node() = default;
};

template<class T>
struct BinaryTree{
private:
	Node<T>* root;
public:
	BinaryTree();
	BinaryTree(const BinaryTree<T>& t);
	~BinaryTree();

	int depth(Node<T>* p) const;
	void copy(Node<T>* t, Node<T>* p);
	void input(Node<T>* node);
	void input(BinaryTree<T>& tree);
	void Predisplay(Node<T>* p) const;
	void display()const;
	void destroy(Node<T>* p);
	Node<T>* getRoot() const;
};

template<class T>
inline BinaryTree<T>::BinaryTree() {
	this->root = nullptr;
}

template<class T>
inline BinaryTree<T>::BinaryTree(const BinaryTree<T>& t){
	if (!t.root) return;
	std::stack<Node<T>*> s1, s2;
	Node<T>* q = nullptr, * p = t.root, * node = this->root;
	int count = 0;
	while (p || !s1.empty()) {
		if (p) {
			s1.push(p);
			node = new Node<T>(p->data);
			if (count == 0) this->root = node;
			s2.push(node);
			count++;
			p = p->left;
			node = node->left;
		} else {
			p = s1.top()->right;
			s1.pop();
			node = s2.top()->right;
			s2.pop();
		}
	}

}

template<class T>
inline BinaryTree<T>::~BinaryTree(){
	destroy(this->root);
}

template<class T>
inline int BinaryTree<T>::depth(Node<T>* p) const{
	if (p == nullptr) return 0;
	int m = depth(p->left);
	int n = depth(p->right);
	return  m > n ? m + 1 : n + 1;
}


template<class T>
inline void BinaryTree<T>::input(Node<T>* node){
	T ch = NULL;
	std::cin >> ch;
	if (ch != '#') {
		node = new Node<T>(ch);
		std::cout << "创建成功" << std::endl;
		input(node->left);
		input(node->right);
	}
}

template<class T>
inline void BinaryTree<T>::input(BinaryTree<T>& tree){
	input(this->root);
}

template<class T>
inline void BinaryTree<T>::Predisplay(Node<T>* p) const{
	if (p) {
		std::cout << p->data << ' ';
		Predisplay(p->left);
		Predisplay(p->right);
	}
}

template<class T>
inline void BinaryTree<T>::display() const{
	Predisplay(this->root);
}

template<class T>
inline void BinaryTree<T>::destroy(Node<T>* p){
	if (p) {
		destroy(p->left);
		destroy(p->right);
		delete p;
	}
}

template<class T>
inline Node<T>* BinaryTree<T>::getRoot() const{
	return this->root;
}
