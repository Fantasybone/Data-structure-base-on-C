#include<iostream>
template<class T>
struct listNode {
	T data = NULL;
	listNode* next = nullptr;
};

template<class T>
struct listQueue {
protected:
	listNode<T>* front;
	listNode<T>* rear;
public:
	listQueue();
	listQueue(const listQueue&);
	~listQueue();

	listQueue<T>& operator=(const listQueue&);	//���� = ��
	bool push_back(const T&);	//��β����
	void pop_front();			//��ͷ��
	void clear();				//��ն��У���ɾ��ͷ
	bool destroy();				//�ݻٶ��У�ɾ��ͷ
	void display() const;		//�������
	int size() const;			//��ȡ����
	bool empty() const;			//�п�
};

template<class T>
listQueue<T>::listQueue() {
	front = rear = new listNode<T>;
	//if (!front)exit(1);
	//front->next = nullptr;			//�����ڳ�ʼ��null
}

template<class T>
inline listQueue<T>::listQueue(const listQueue& q){
	this->front = this->rear = new listNode<T>;
	//if (!this->front)exit(1);
	//this->front->next = nullptr;		//�����ڳ�ʼ��null
	if (!q.front->next)return;
	listNode<T>* p = q.front->next;
	while (p) {
		listNode<T>* node = new listNode<T>;
		node->data = p->data;
		this->rear->next = node;
		this->rear = node;
		p = p->next;
	}
	//this->rear->next = nullptr;
}

template<class T>
inline listQueue<T>::~listQueue(){
	if (!this->front)return;
	listNode<T>* p = this->front, *q = p;
	while (p) {
		q = q->next;
		delete p;
		p = q;
	}
}

template<class T>
inline listQueue<T>& listQueue<T>::operator=(const listQueue& Q){
	if (!this->front) {
		this->front = this->rear = new listNode<T>;
	}
	listNode<T>* p = this->front->next, * q = p;
	while (p) {							//����ͷ��㲻ɾ
		q = q->next;
		delete p;
		p = q;
	}
	this->rear = this->front;
	p = Q.front->next;
	while (p) {
		listNode<T>* node = new listNode<T>;
		node->data = p->data;
		this->rear->next = node;
		this->rear = node;
		p = p->next;
	}
	//this->rear->next = nullptr;		//�����ڳ�ʼ��
	return *this;
}

template<class T>
inline bool listQueue<T>::push_back(const T& data){
	listNode<T>* node = new listNode<T>;
	node->data = data;
	rear->next = node;
	rear = node;
	//rear->next = nullptr;				//�Ѿ����ڳ�ʼ����
	return true;
}

template<class T>
inline void listQueue<T>::pop_front(){
	if (!front)return;
	if (front == rear)return;
	listNode<T>* p = front->next;		//pָ���һ��Ԫ��
	front->next = p->next;
	if (p == rear)rear = front;			//������һ��Ԫ�ر�ɾ����βָ���ͷ
	delete p;
}

template<class T>
inline void listQueue<T>::clear(){
	if (!front)return;
	listNode<T>* p = front->next, * q = p;
	while (p) {
		q = q->next;
		delete p;
		p = q;
	}
	front->next = nullptr;
	rear = front;
}

template<class T>
inline bool listQueue<T>::destroy(){
	if (!front)return false;
	listNode<T>* p = front, * q = p;
	while (p) {
		q = q->next;
		delete p;
		p = q;
	}
	front = rear = nullptr;
	return true;
}

template<class T>
inline void listQueue<T>::display() const {
	if (!front) {
		std::cout << "It already been destroyed" << std::endl;
		return;
	}
	if (front == rear) {
		std::cout << "NULL" << std::endl;
		return;
	}
	listNode<T>* p = front->next;
	while (p) {
		std::cout << p->data << std::endl;
		p = p->next;
	}
}

template<class T>
inline int listQueue<T>::size() const {
	if (!front)return 0;
	listNode<T>* p = front;
	int size = 0;
	while (p->next) {
		p = p->next;
		size++;
	}
	return size;
}

template<class T>
inline bool listQueue<T>::empty() const {
	if (size())return false;
	return true;
}
