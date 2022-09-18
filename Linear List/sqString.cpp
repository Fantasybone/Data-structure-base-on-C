#include"sqString.h"

//int* sqString::getNext(const sqString& s) const{
//	int* next = new int[s.size];
//	int i = 1, len = 0;
//	next[0] = 0;
//	while (i < s.size) {
//		if (s.ch[i] == s.ch[len]) {
//			len++;
//			next[i] = len;
//			i++;
//		} else {
//			if (len == 0) { next[i++] = 0; }
//			else { len = next[len - 1]; }
//		}
//	}
//	return next;
//}

int* sqString::getNext(const sqString& s) const{
	int* next = new int[s.size];
	int i = 0, j = -1;
	next[0] = -1;
	while (i < s.size - 1) {
		if (j == -1 || s.ch[i] == s.ch[j]) {
			i++; j++;
			if (s.ch[i] == s.ch[j]) next[i] = next[j];
			else next[i] = j;
		} else j = next[j];
	}
	return next;
}

sqString::sqString() {}

sqString::sqString(const char* c) {
	while (c[size] != '\0') size++;
	ch = new char[size];
	for (int i = 0; i < size; i++)
		ch[i] = c[i];
}

sqString::sqString(const sqString& s){
	delete[] this->ch;
	this->ch = new char[s.size];
	this->size = s.size;
	for (int i = 0; i < s.size; i++)
		this->ch[i] = s.ch[i];
}

sqString::~sqString(){
	delete[] ch;
}

sqString& sqString::operator=(const sqString& s){
	if (this->ch)delete[] ch;
	this->size = s.size;
	this->ch = new char[s.size];
	for (int i = 0; i < s.size; i++) {
		this->ch[i] = s.ch[i];
	}
	return *this;
}

size_t sqString::BF(const sqString& s, int pos) const{
	if (this->size < s.size || pos > this->size)return 0;
	size_t i = pos, j = 0;
	while (i < this->size && j < s.size) {
		if (this->ch[i] == s.ch[j]) {
			i++;
			j++;
		} else {
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == s.size)return i - j + 1;
	return 0;
}

//size_t sqString::KMP(const sqString& s, int pos) const{
//	if (this->size < s.size || pos > this->size)return -1;
//	int* next = getNext(s);
//	size_t i = pos, j = 0;
//	while (i < this->size && j < s.size) {
//		if (this->ch[i] == s.ch[j]) {
//			i++;
//			j++;
//			if (j == s.size) {
//				delete[] next;
//				return i - j + 1;
//			}
//		}else if(j == 0 && this->ch[i] != s.ch[i]){
//			i++;
//		} else {
//			j = next[j - 1];
//		}
//	}
//	delete[] next;
//	return 0;
//}

int sqString::KMP(const sqString& s, int pos) const{
	int* next = getNext(s);
	int i = pos, j = 0;
	while (i < this->size && j < s.size) {
		if (j == -1 || this->ch[i] == s.ch[j]) {
			i++, j++;
		} else j = next[j];
	}
	delete[] next;
	if (j == s.size)return i - j + 1;
	return 0;
}

int sqString::compare(const sqString& s) const{
	for (int i = 0; i < std::min(s.length(), this->length()); i++) {
		if (this->ch[i] > s.ch[i])return 1;
		else if (this->ch[i] < s.ch[i])return -1;
	}
	if (this->length() > s.length())return 1;
	else if (this->length() < s.length())return -1;
	return 0;
}

sqString& sqString::concat(const sqString& s){
	char* temp = new char[this->length() + s.length()];
	for (int i = 0; i < this->length(); i++)
		temp[i] = this->ch[i];
	for (int i = 0; i < s.length(); i++)
		temp[i + this->length()] = s.ch[i];
	this->size = this->size + s.size;
	delete[] this->ch;
	this->ch = temp;
	return *this;
}

bool sqString::empty() const{
	if (size)return false;
	return true;
}

size_t sqString::length() const{
	return size;
}


std::ostream& operator<<(std::ostream& cout, sqString& s){
	for (int i = 0; i < s.length(); i++)
		std::cout << s.ch[i];
	return cout;
}
