template<class T>
struct stackNode {
	T data;
	stackNode* next = nullptr;
};

template<class T>
struct listStack {
private:
	size_t m_size = 0;
	stackNode<T>* head = nullptr;				//头节点，指向stackNode链，每次push完都要指向最顶端的节点
public:
	listStack();
	listStack(const listStack&);
	~listStack();

	listStack<T>& operator=(const listStack<T>&);
	size_t size();			//获取长度
	bool push(const T&);	//压栈
	T pop();				//出栈
	T gettop();				//获取栈顶元素
	void clear();			//清空
	bool destroy();			//摧毁栈，释放内存
	void display();			//遍历输出
	bool empty();			//判空
};


template<typename T>
inline listStack<T>::listStack() {
	head = new stackNode<T>;
	if (!head)exit(1);
	//head->next = nullptr;			//已经类内初始化了next
}
template<typename T>
listStack<T>::listStack(const listStack& s) {
	this->head = new stackNode<T>;	//拷贝构造不调用构造函数，别忘了申请内存
	if (!this->head)exit(1);
	//this->head->next = nullptr;
	if (!s.head->next)return;		//如果s为空，提前返回
	this->m_size = s.m_size;
	stackNode<T>* p = s.head;
	stackNode<T>* first = new stackNode<T>;
	first->data = p->data;
	first->next = this->head;
	p = p->next;
	stackNode<T>* rear = this->head = first;
	while (p->next) {
		stackNode<T>* node = new stackNode<T>;
		if (!node)exit(1);
		node->data = p->data;
		node->next = rear->next;
		rear->next = node;
		rear = node;
		p = p->next;
	}
}
template<typename T>
inline listStack<T>::~listStack() {
	if (!this->head)return;
	stackNode<T>* p = this->head, * q = p;
	while (p) {
		q = q->next;
		delete p;
		p = q;
	}
}

template<typename T>
listStack<T>& listStack<T>::operator=(const listStack<T>& s) {
	//删除原先的空间
	stackNode<T>* p = this->head, * q = p;
	this->m_size = 0;
	while (p->next) {	//留下栈底不删
		q = q->next;
		delete p;
		p = q;
	}
	this->head = p;		//重新将head指向栈头，这个时候栈底就是栈头
	//开辟新空间
	if (!s.head->next)return *this;		//如果s只有栈底，直接返回
	this->m_size = s.m_size;
	p = s.head;							//记录s的栈头
	stackNode<T>* first = new stackNode<T>;//创建栈头
	first->data = p->data;
	first->next = this->head;			//栈头指向栈底
	p = p->next;
	stackNode<T>* rear = this->head = first;	//记录栈头作链尾，head重新指向栈头
	while (p->next) {
		stackNode<T>* node = new stackNode<T>;
		if (!node)exit(1);
		node->data = p->data;
		node->next = rear->next;		//在栈底之前不断插入node
		rear->next = node;
		rear = node;
		p = p->next;
	}
	return *this;
}

template<typename T>
inline size_t listStack<T>::size() {
	return this->m_size;
}
template<typename T>
bool listStack<T>::push(const T& ele) {				//压栈
	if (!this->head)return false;
	stackNode<T>* node = new stackNode<T>;
	if (!node)return false;
	node->data = ele;
	node->next = this->head;
	this->head = node;
	this->m_size++;
	return true;
}
template<typename T>
inline T listStack<T>::pop(){
	if (!this->m_size)exit(1);
	m_size--;
	T data = head->data;
	head = head->next;
	return data;
}
template<typename T>
inline T listStack<T>::gettop(){
	return head->data;
}
template<typename T>
inline void listStack<T>::clear(){
	if (!this->head)return;
	stackNode<T>* p = this->head, * q = p;
	this->m_size = 0;
	while (p->next) {
		q = q->next;
		delete p;
		p = q;
	}
	this->head = p;
	p = q = nullptr;
}
template<typename T>
inline bool listStack<T>::destroy(){
	if (!this->head)return false;
	stackNode<T>* p = this->head, * q = p;
	this->m_size = 0;
	while (p) {
		q = q->next;
		delete p;
		p = q;
	}
	this->head = nullptr;
	return true;
}
template<typename T>
inline void listStack<T>::display() {					//遍历输出
	if (!this->head)return;
	stackNode<T>* p = this->head;
	while(p->next) {
		std::cout << p->data << std::endl;
		p = p->next;
	}
}
template<typename T>
inline bool listStack<T>::empty(){
	return !m_size;
}