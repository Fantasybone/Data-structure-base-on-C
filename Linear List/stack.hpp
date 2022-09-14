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
	size_t getsize();			//获取大小
	size_t getMAXSIZE();		//获取容量
	T* getbase();				//返回栈底指针
	T gettop();					//返回栈顶元素
	bool empty();				//判空
	bool push(const T&);		//压栈
	T pop();					//出栈并返回元素
	bool destroy();				//摧毁栈
	void clear();				//清空
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
size_t stack<T>::getsize() {			//获取栈的元素个数
	return stacksize;
}
template<typename T>
size_t stack<T>::getMAXSIZE() {			//获取栈的容量
	return MAXSIZE;
}
template<typename T>
T* stack<T>::getbase() {				//获取栈的base指针，用于自写输出函数
	return base;
}
template<typename T>
T stack<T>::gettop() {					//获取栈的最顶端的元素
	return *(top - 1);
}
template<typename T>
bool stack<T>::empty() {				//判断是否为空
	return top == base;
}
template<typename T>
bool stack<T>::push(const T& data) {			//压栈
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