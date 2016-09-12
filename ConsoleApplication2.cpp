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
stack<T>::stack() : array_size_(0), count_(0), array_(nullptr) {};
template <typename T>
stack<T>::~stack() { delete[] array_; count_ = 0;array_size_ = 0; }
template <typename T>
size_t  stack<T>::count() const { return count_; };
template <typename T>
void stack<T>::push(T const &item)
{
	count_++;
	if (array_size_ == 0) array_size_ = 1;
	if (count_ > array_size_)  array_size_ = 2 * array_size_;
	T* new_array = new T[array_size_];
	new_array[0] = item;
	for (int i = 0; i<count_-1;i++)
		new_array[i+1] = array_[i];
	delete[] array_;
	array_ = new T[array_size_];
	for (int i = 0; i<count_;i++)
		array_[i] = new_array[i];
	delete[] new_array;
	cout << array_[0] << '\n';
}

template <typename T>
T stack<T>::pop()
{
	T* new_array;
	T item = array_[0];
	new_array = new T[array_size_];
	for (int i = 0; i<count_ - 1;i++)
		new_array[i] = array_[i + 1];
	delete[] array_;
	array_ = new T[array_size_];
	for (int i = 0; i<count_;i++)
		array_[i] = new_array[i];
	count_--;
	delete[] new_array;
	return item;
}



int main(void) {

	stack <int> a;
	a.push(1);
	a.push(2);
	a.push(3);
	cout << a.pop() << endl;
	cout << a.pop() << endl;
	system("pause");
}