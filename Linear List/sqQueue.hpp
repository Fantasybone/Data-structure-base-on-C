#include<cstdlib>
#include<iostream>
template<class T>
struct sqQueue {
protected:
	size_t front = 0, rear = 0;		//front是对头下标，rear指向对尾的下一个位置的下标
	T* base = nullptr;
	size_t MAXSIZE;
public:
	sqQueue(size_t);
	sqQueue(const sqQueue&);
	~sqQueue();

	sqQueue<T>& operator=(const sqQueue&);
	T gettop();						//获取对头元素
	bool push_back(const T&);		//队尾添加元素
	T pop_front();					//删除对头
	void clear();					//清空队列
	bool destroy();					//摧毁队列，释放内存
	void display();					//遍历输出
	bool empty() const;				//判空
	size_t size() const;			//获取长度
};

template<class T>
sqQueue<T>::sqQueue(size_t size):MAXSIZE(size + 1) {//因为要留一个空位去判断队空和队满，size多加一
	this->base = new T[MAXSIZE];
	//if (!this->base)exit(1);
}

template<class T>
inline sqQueue<T>::sqQueue(const sqQueue& q) {
	this->base = new T[q.MAXSIZE];
	//if (!this->base)exit(1);
	this->front = q.front;
	this->rear = q.rear;
	this->MAXSIZE = q.MAXSIZE;
	//if (q.front == q.rear)return;		//可要可不要
	size_t head = q.front;
	while(head != q.rear) {
		this->base[head] = q.base[head];
		head = (head + 1) % q.MAXSIZE;
	}
}

template<class T>
inline sqQueue<T>::~sqQueue(){
	if (!this->base)return;
	delete[] this->base;
}

template<class T>
inline sqQueue<T>& sqQueue<T>::operator=(const sqQueue& q) {
	if (this->base) {
		delete[] this->base;
		this->front = this->rear = this->MAXSIZE = 0;
	}
	this->base = new T[q.MAXSIZE];
	//if (!this->base)exit(1);
	this->front = q.front;
	this->rear = q.rear;
	this->MAXSIZE = q.MAXSIZE;
	//if (q.front == q.rear)return *this;	//可要可不要
	size_t head = q.front;
	while (head != q.rear) {
		this->base[head] = q.base[head];
		head = (head + 1) % q.MAXSIZE;
	}
	return *this;
}

template<class T>
inline T sqQueue<T>::gettop(){
	if (!this->base)exit(-1);
	return this->base[front];
}

template<class T>
inline bool sqQueue<T>::push_back(const T& data){
	if (!MAXSIZE)return false;
	if ((this->rear + 1) % MAXSIZE == this->front)return false;
	this->base[this->rear] = data;
	this->rear = (this->rear + 1) % MAXSIZE;
	return true;
}

template<class T>
inline T sqQueue<T>::pop_front(){
	if (front == rear)exit(-1);
	size_t head = front;
	front = (front + 1) % MAXSIZE;
	return this->base[head];
}

template<class T>
inline void sqQueue<T>::clear(){
	this->front = this->rear = 0;
}

template<class T>
inline bool sqQueue<T>::destroy(){
	if (!this->base)return false;
	delete[] this->base;
	this->base = nullptr;
	this->front = this->rear = this->MAXSIZE = 0;
	return true;
}

template<class T>
inline void sqQueue<T>::display(){
	if (front == rear)return;
	size_t head = front;
	while (head != rear) {
		std::cout << base[head] << std::endl;
		head = (head + 1) % MAXSIZE;
	}
}

template<class T>
inline bool sqQueue<T>::empty() const {
	if (front == rear)return true;
	return false;
}

template<class T>
inline size_t sqQueue<T>::size() const {
	if (front == rear)return 0;
	return (rear - front + MAXSIZE) % MAXSIZE;
}
