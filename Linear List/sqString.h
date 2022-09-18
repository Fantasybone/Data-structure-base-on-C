#pragma once
#include<iostream>
#include<algorithm>
struct sqString {
	friend std::ostream& operator<<(std::ostream& cout, sqString& s);
private:
	char* ch = nullptr;
	//size_t size = 0;			size_t类型计算会有问题
	int size = 0;
	int* getNext(const sqString& s)const;
public:
	sqString();
	sqString(const char* c);
	sqString(const sqString& s);
	~sqString();

	sqString& operator=(const sqString& s);				//重载 = 号
	size_t BF(const sqString& s, int pos = 0)const;		//找子串
	int KMP(const sqString& s, int pos = 0)const;
	int compare(const sqString& s)const;				//比较，大于s返回1，小于s返回-1，相等返回0
	sqString& concat(const sqString& s);				//拼接s到后面
	bool empty()const;									//判空
	size_t length()const;								//返回长度
};
std::ostream& operator<<(std::ostream& cout, sqString& s);//重载 << 用作输出字符串