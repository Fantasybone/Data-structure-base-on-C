#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define bool int
#define true 1
#define false 0
const int MAXSIZE = 100;

typedef struct{
    char no[20];
    char name[30];
    int price;
}Book;

typedef struct sqList{
    Book* ele;
    int length;
}sqList;

void create(sqList* List){ 
    List->ele=(Book*)malloc(sizeof(List->ele) * MAXSIZE);
    List->length=0;
}

//结构体指针指向结构体指针随机访问的时候
//1.List->ele[i].no
//2.(*List).ele[i].no
//3.(*(List->ele+i)).no
//4.(List->ele+i)->no
void display(sqList* List){
    for(int i = 0; i < List->length; i++){
        printf("Number: %-4s  Name: %-10s  Price: %d\n", (List->ele+i)->no, List->ele[i].name, List->ele[i].price);
    }
}
Book* getBook(sqList* List, int pos){
    if (pos > List->length) return NULL;
    return List->ele+pos-1;
}
Book* createBook(char no[], char name[], int price){
    Book* book = (Book*)malloc(sizeof(Book));
    strcpy(book->no,no);
    strcpy(book->name,name);
    book->price = price;
    return book;
}
//第二个形参是从1开始的位置，第三个形参是一个临时结构体，用完以后释放
bool insert(sqList* List, int pos, Book* ele){
    if(pos > List->length+1)return false;
    if(List->length == MAXSIZE)return false;
    for(int i = List->length-1; i>=pos-1; i--){
        strcpy((*List).ele[i+1].no, (*List).ele[i].no);
        strcpy((*List).ele[i+1].name, (*List).ele[i].name);
        (*List).ele[i+1].price = (*List).ele[i].price;
    }
    strcpy((*List).ele[pos-1].no, ele->no);
    strcpy((*List).ele[pos-1].name, ele->name);
    (*List).ele[pos-1].price = ele->price;
    List->length++;
    free(ele);      //把传进来的ele释放
    ele=NULL;
    return true;
}
bool delete(sqList* List, int pos){
    if(pos > List->length) return false;
    for(int i = pos; i < List->length; i++){
        strcpy((*List).ele[i-1].no, (*List).ele[i].no);
        strcpy((*List).ele[i-1].name, (*List).ele[i].name);
        (*List).ele[i-1].price = (*List).ele[i].price;
    }
    List->length--;
    return true;
}
void Modify(sqList* List, int pos, Book* ele){
    if(pos > List->length) return;
    strcpy((*List).ele[pos-1].no, ele->no);
    strcpy((*List).ele[pos-1].name, ele->name);
    (*List).ele[pos-1].price = ele->price;
}
bool find(sqList* List, char no[]){
    for(int i = 0; i < List->length; i++){
        if(strcmp(List->ele[i].no, no) == 0) return true;
    }
    return false;
}

//test
int main(){
    sqList List;
    create(&List);                          //创建空表
    insert(&List, 1, createBook("001", "science", 12));
    insert(&List, 1, createBook("002", "math", 11));
    insert(&List, 1, createBook("003", "chinese", 54));
    insert(&List, 1, createBook("004", "English", 45));
    insert(&List, 1, createBook("005", "technology", 38));
    delete(&List, 2);
    printf("%s\n",getBook(&List, 2)->name); //通过getBook直接获取ele
    Modify(&List, 2, createBook("test", "yuezige", 10));//修改函数测试
    display(&List);
    if(find(&List, "test")) printf("success found\n");else printf("cannot found\n");
}