template<class T>
struct stack {
private:
	T* top;
	T* base;
	size_t stacksize;
	size_t MAXSIZE;
public:
	stack(size_t);
	stack(const stack&);
	~stack();

	stack& operator=(const stack&);
	size_t getsize();
	size_t getMAXSIZE();
	T* getbase();
	T gettop();
	bool empty();
	bool push(T);
	T pop();
};


template<typename T>
stack<T>::stack(size_t size) : MAXSIZE(size), top(nullptr), base(nullptr), stacksize(0) {
	base = new T[MAXSIZE];
	top = base;
}
template<typename T>
stack<T>::stack(const stack& s) {
	this->base = new T[s.MAXSIZE];
	this->top = this->base + s.stacksize;
	this->stacksize = s.stacksize;
	this->MAXSIZE = s.MAXSIZE;
	for (int i = 0; i < s.stacksize; i++) {
		*(this->base + i) = *(s.base + i);
	}
}
template<typename T>
stack<T>::~stack() {
	delete[] base;
	base = nullptr;
}


template<typename T>
stack<T>& stack<T>::operator=(const stack& s) {
	if (this->base) {
		delete[] this->base;
		this->base = nullptr;
		this->top = nullptr;
		this->stacksize = 0;
		this->MAXSIZE = 0;
	}
	this->base = new T[s.MAXSIZE];
	this->top = this->base + s.stacksize;
	this->stacksize = s.stacksize;
	this->MAXSIZE = s.MAXSIZE;
	for (int i = 0; i < s.stacksize; i++) {
		*(this->base + i) = *(s.base + i);
	}
	return *this;
}


template<typename T>
size_t stack<T>::getsize() {			//��ȡջ��Ԫ�ظ���
	return stacksize;
}
template<typename T>
size_t stack<T>::getMAXSIZE() {			//��ȡջ������
	return MAXSIZE;
}
template<typename T>
T* stack<T>::getbase() {				//��ȡջ��baseָ�룬������д�������
	return base;
}
template<typename T>
T stack<T>::gettop() {					//��ȡջ����˵�Ԫ��
	return *(top - 1);
}
template<typename T>
bool stack<T>::empty() {				//�ж��Ƿ�Ϊ��
	return top == base;
}
template<typename T>
bool stack<T>::push(T data) {			//ѹջ
	if (stacksize == MAXSIZE)return false;
	*top++ = data;
	stacksize++;
	return true;
}
template<typename T>
T stack<T>::pop() {
	if (empty())exit(1);
	stacksize--;
	return *--top;
}