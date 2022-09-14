template<class T>
struct stackNode {
	T data;
	stackNode* next = nullptr;
};

template<class T>
struct listStack {
private:
	size_t m_size = 0;
	stackNode<T>* head = nullptr;				//ͷ�ڵ㣬ָ��stackNode����ÿ��push�궼Ҫָ����˵Ľڵ�
public:
	listStack();
	listStack(const listStack&);
	~listStack();

	listStack<T>& operator=(const listStack<T>&);
	size_t size();			//��ȡ����
	bool push(const T&);	//ѹջ
	T pop();				//��ջ
	T gettop();				//��ȡջ��Ԫ��
	void clear();			//���
	bool destroy();			//�ݻ�ջ���ͷ��ڴ�
	void display();			//�������
	bool empty();			//�п�
};


template<typename T>
inline listStack<T>::listStack() {
	head = new stackNode<T>;
	if (!head)exit(1);
	//head->next = nullptr;			//�Ѿ����ڳ�ʼ����next
}
template<typename T>
listStack<T>::listStack(const listStack& s) {
	this->head = new stackNode<T>;	//�������첻���ù��캯���������������ڴ�
	if (!this->head)exit(1);
	//this->head->next = nullptr;
	if (!s.head->next)return;		//���sΪ�գ���ǰ����
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
	//ɾ��ԭ�ȵĿռ�
	stackNode<T>* p = this->head, * q = p;
	this->m_size = 0;
	while (p->next) {	//����ջ�ײ�ɾ
		q = q->next;
		delete p;
		p = q;
	}
	this->head = p;		//���½�headָ��ջͷ�����ʱ��ջ�׾���ջͷ
	//�����¿ռ�
	if (!s.head->next)return *this;		//���sֻ��ջ�ף�ֱ�ӷ���
	this->m_size = s.m_size;
	p = s.head;							//��¼s��ջͷ
	stackNode<T>* first = new stackNode<T>;//����ջͷ
	first->data = p->data;
	first->next = this->head;			//ջͷָ��ջ��
	p = p->next;
	stackNode<T>* rear = this->head = first;	//��¼ջͷ����β��head����ָ��ջͷ
	while (p->next) {
		stackNode<T>* node = new stackNode<T>;
		if (!node)exit(1);
		node->data = p->data;
		node->next = rear->next;		//��ջ��֮ǰ���ϲ���node
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
bool listStack<T>::push(const T& ele) {				//ѹջ
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
inline void listStack<T>::display() {					//�������
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