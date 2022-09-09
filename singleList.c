#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int num;
    struct node *next;
}Node,*Link;

void displayNode(Link head){
    Link p=head->next;
    while (p!=NULL){
        printf("%d ",p->num);
        p=p->next;
    }
}

Link findNode(Link head,int x){
    Link p=head->next;
    while(p!=NULL && p->num!=x){
        p=p->next;
    }
    return p;
}

int insertNode(Link head,int i,int x){
    Link p=head;
    int count=0;
    while(p!=NULL && count<i-1){    //查找第i-1个节点，当前p在第i-1个
        p=p->next;
        count++;
    }
    if(p==NULL)return 0;
    Link node=(Link)malloc(sizeof(Node));
    node->num=x;
    node->next=p->next;
    p->next=node;
    return 1;
}

Link newlisthead(int arr[],int n){      //create 头插法
    Link head=(Link)malloc(sizeof(Node));
    head->next=NULL;
    for (int i=0;i<n;i++){
        Link node=(Link)malloc(sizeof(Node));
        node->num=arr[i];
        node->next=head->next;
        head->next=node;
    }
    return head;
}

Link newlistrear(int arr[],int n){      //create 尾插法
    Link head=(Link)malloc(sizeof(Node));
    head->next=NULL;
    Link rear=head;
    for(int i=0;i<n;i++){
        Link node=(Link)malloc(sizeof(Node));
        node->num=arr[i];
        rear->next=node;
        rear=node;
    }
    rear->next=NULL;
    return head;
}

int erase(Link head,int x){             //删除value为x的节点
    if(head->next==NULL || head==NULL)return 0;
    Link q=head,p=head->next;
    while(p!=NULL){
        if(p->num==x){
            q->next=p->next;
            free(p);
            return 1;
        }
        q=q->next;
        p=p->next;
    }
    return 0;
}

void sort(Link head,int len){
    for (int i=0;i<len-1;i++){
        Link left=head,mid=head->next,right=mid->next;
        for(int j=0;j<len-i-1;j++){
            if(mid->num>right->num){
                Link leftnext=left->next;
                left->next=mid->next;
                mid->next=right->next;
                right->next=leftnext;
                Link temp=mid;
                mid=right;
                right=temp;
            }
            left=left->next;
            mid=mid->next;
            right=right->next;
        }
    }
}

//test
int main(){
    int arr[]={17,7,2,3,4,5};
    Link head=newlistrear(arr,6);
    erase(head,2);
    sort(head,5);
    displayNode(head);
    Link p=findNode(head,2);
    if(p!=NULL){
        printf("success find: %d ",p->num);
    }else{
        printf("Can't search");
    }
}