#include "stdafx.h"
#include<windows.h>
#include <iostream>

using namespace std;
template <typename T>
class stack
{
public:
	stack();
	size_t count() const;
	void push(T const &item);
	T pop();
	~stack();

private:

	T * array_;
	size_t array_size_;
	size_t count_;

};
template <typename T>
stack<T>::stack() : array_size_(1), count_(0) { array_ = new T[array_size_]; };
template <typename T>
stack<T>::~stack() { delete array_; count_=0;array_size_ = 0; }
template <typename T>
size_t  stack<T>::count() const { return count_; };
template <typename T>
void stack<T>::push(T const &item)
{
	count_++;
	if (count_ > array_size_)  array_size_ = 2 * array_size_;
	T* new_array;
	new_array = new T[array_size_];
	new_array[0] = item;
	for (int i = 1; i<count_;i++)
		new_array[i] = array_[i];
	delete array_;
	array_ = new T[array_size_];
	for (int i = 0; i<count_;i++)
		array_[i] = new_array[i];
	delete new_array;
	cout << array_[0] << '\n';
}

template <typename T>
T stack<T>::pop()
{
	T* new_array;
	T item = array_[0];
	new_array = new T[array_size_];
	for (int i = 0; i<count_ -1;i++)
		new_array[i] = array_[i+1];
	delete array_;
	array_ = new T[array_size_];
	for (int i = 0; i<count_;i++)
		array_[i] = new_array[i];
	count_--;
	delete new_array;
	return item;
}



int main(int argc, const char * argv[]) {

	stack <int> a;
	a.push(3);
	a.push(4);
	a.push(5);
	cout << a.pop() ;
	system("pause");
}