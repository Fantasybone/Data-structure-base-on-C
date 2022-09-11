#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define bool int
#define true 1
#define false 0


typedef struct{
    char no[20];
    char name[30];
    int price;
}Book;
Book* createBook(const char no[], const char name[], const int price){
    Book* book = (Book*)malloc(sizeof(Book));
    strcpy(book->no, no);
    strcpy(book->name, name);
    book->price = price;
    return book;
}
 //一定一定要给Book指针分配内存，给List分配空间的时候，只给Book指针留了指针的空间，需要手动再给Book分配内存
typedef struct List{
    struct List* prior;
    Book* ele;
    struct List* next;
}List;


List* create(){     //无参初始化
    List* head = (List*)malloc(sizeof(List));
    head->ele = (Book*)malloc(sizeof(Book));    //给Book指针分配内存，勿忘！！
    strcpy(head->ele->no, "");
    strcpy(head->ele->name, "");
    head->ele->price = 0;
    //指针初始化
    head->prior = head->next = head;
    return head;
}

List* newList(Book* ele[], int len){        //有参初始化
    List* head = create();
    for(int i = 0; i < len; i++){
        List* node = (List*)malloc(sizeof(List)); 
        node->ele = ele[i];
        //节点尾插
        head->prior->next = node;
        node->prior = head->prior;
        head->prior = node;
        node->next = head;
        }
    return head;
}
void display(const List* head){             //显示链表元素
    List* p = head->next;
    if(p == head){
        printf("NULL\n");
        return;
    }
    while(p != head){
        printf("Number: %-4s, Name: %-10s, Price: %-2d\n", p->ele->no, p->ele->name, p->ele->price);
        p = p->next;
    }
}
void displayReverse(const List* head){             //显示链表元素
    List* p = head->prior;
    if(p == head){
        printf("NULL\n");
        return;
    }
    while(p != head){
        printf("Number: %-4s, Name: %-10s, Price: %-2d\n", p->ele->no, p->ele->name, p->ele->price);
        p = p->prior;
    }
}
int length(const List* head){               //计算链表长度
    List* p = head->next;
    int len = 0;
    while(p != head){
        len++;
        p = p->next;
    }
    return len;
}
bool empty(const List* head){               //判断是否为空
    if(!length(head))return true;
    return false;
}

void push_back(List* head, Book* ele){      //尾插
    List* node = (List*)malloc(sizeof(List));
    node->ele = ele;
    //节点尾插
    head->prior->next = node;
    node->prior = head->prior;
    head->prior = node;
    node->next = head;
}
void push_front(List* head, Book* ele){     //头插
    List* node = (List*)malloc(sizeof(List));
    node->ele = ele;
    //节点头插
    node->prior = head;
    head->next->prior = node;
    node->next = head->next;
    head->next = node;
}
bool pop_back(List* head){                  //尾删
    if(empty(head))return false;
    List* tail = head->prior;
    tail->prior->next = head;
    head->prior = tail->prior;
    free(tail);
    tail = NULL;
    return true;
}
bool pop_front(List* head){
    if(empty(head))return false;
    List* first = head->next;
    head->next = first->next;
    first->next->prior = head;
    free(first);
    first = NULL;
    return true;
}
bool insert(List* head, int pos, Book* ele){
    if(pos > length(head) + 1)return false;   //也可以用这个，然后while里面不需要第一个条件
    List* p = head;
    int count = 0;
    while(count < pos - 1){
        p = p->next;
        count++;
    }
    List* node = (List*)malloc(sizeof(List));
    node->ele = ele;

    node->next = p->next;
    p->next = node;
    node->prior = p;
    node->next->prior = node;
    return true;
}
bool erase(List* head, const int pos){      //删除指定下标的节点
    if(pos > length(head) + 1)return false;
    List* p = head, *q = head->next;
    int count = 0;
    while(count < pos - 1){
        p = p->next;
        q = q->next;
        count++;
    }
    p->next = q->next;
    p->next->prior = p;
    free(q);
    q = NULL;
    return true;
}
bool Modify(List* head, const int pos, Book* book){//修改指定下标的节点
    if(pos > length(head) + 1)return false;
    List* p = head->next;
    int count = 1;
    while(count < pos){
        p = p->next;
        count++;
    }
    strcpy(p->ele->no, book->no);
    strcpy(p->ele->name, book->name);
    p->ele->price = book->price;
    return true;
}
List* find(List* head, const int pos){      //获取指定下标的节点
    if(pos > length(head) + 1)return NULL;
    List* p = head;
    int count = 0;
    while(count < pos){
        p = p->next;
        count++;
    }
    return p;
}
void reverse(List* head){       //头插法反转链表
    List* first = head->next;   //第一个节点
    head->next = head->prior = head;
    while(first != head){
        List* p = first;        //提前储存第一个节点
        first = first->next;    //第一个节点提前往后，不然下面跑完，next节点就丢失了
        p->prior = head;
        head->next->prior = p;
        p->next = head->next;
        head->next = p;
    }
}

int main(){
    //结构体指针数组，作为有参构造函数的参数
    // Book* ele[] = {createBook("001", "math", 22), createBook("002","English",43), createBook("003", "Chinese", 66)};
    // List* head = newList(ele, 3);
    List* head = create();
    push_back(head, createBook("001", "math", 22));
    push_back(head, createBook("002", "English", 33));
    push_back(head, createBook("003", "science", 24));
    push_front(head, createBook("004", "test", 99));
    // if(pop_front(head))printf("success delete\n");else printf("it is NULL List\n");
    insert(head, 5, createBook("113", "yuezige", 45));
    erase(head, 1);
    display(head);
    printf("\n");
    // Modify(head, 4, createBook("2", "test", 56));
    reverse(head);
    display(head);
    // printf("%s\n", find(head, 1)->ele->name);
}