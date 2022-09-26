#pragma once
#include<string>
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
	Node<T>* root = nullptr;
public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree<T>& t);
	~BinaryTree();

	int depth(Node<T>* p) const;
	int depth()const;
	void input(Node<T>*& node);
	void input();
	void Predisplay(Node<T>* p) const;
	void display()const;
	void destroy(Node<T>* p);
	Node<T>* copy(Node<T>* p);
};


template<class T>
inline BinaryTree<T>::BinaryTree(const BinaryTree<T>& t){
	this->root = copy(t.root);

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
inline int BinaryTree<T>::depth() const{
	return depth(this->root);
}


template<class T>
inline void BinaryTree<T>::input(Node<T>*& node){
	T ch = NULL;
	std::cin >> ch;
	if (ch != '#') {
		node = new Node<T>(ch);
		input(node->left);
		input(node->right);
	}
}

template<class T>
inline void BinaryTree<T>::input(){
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
inline Node<T>* BinaryTree<T>::copy(Node<T>* p) {
	if (!p) return nullptr;
	Node<T>* copyNode = new Node<T>(p->data);
	copyNode->left = copy(p->left);
	copyNode->right = copy(p->right);
	return copyNode;
}
