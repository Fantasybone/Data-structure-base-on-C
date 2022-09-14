template<class T>
struct stack {
private:
	T* top = nullptr;
	T* base = nullptr;
	size_t stacksize = 0;
	size_t MAXSIZE = 0;
public:
	stack(size_t);
	stack(const stack&);
	~stack();

	stack& operator=(const stack&);
	size_t getsize();			//��ȡ��С
	size_t getMAXSIZE();		//��ȡ����
	T* getbase();				//����ջ��ָ��
	T gettop();					//����ջ��Ԫ��
	bool empty();				//�п�
	bool push(const T&);		//ѹջ
	T pop();					//��ջ������Ԫ��
	bool destroy();				//�ݻ�ջ
	void clear();				//���
};


template<typename T>
stack<T>::stack(size_t size) : MAXSIZE(size){
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
	if (this->base) {
		delete[] this->base;
	}
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
bool stack<T>::push(const T& data) {			//ѹջ
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
template<typename T>
bool stack<T>::destroy() {
	if (!this->base)return false;
	delete[] this->base;
	this->base = this->top = nullptr;
	this->stacksize = this->MAXSIZE = 0;
	return true;
}
template<typename T>
void stack<T>::clear() {
	this->stacksize = 0;
	this->top = this->base;
}