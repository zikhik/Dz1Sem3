
#ifndef stack_cpp
#define stack_cpp
#pragma once 
#include <cstdlib>
#include <string>
#include <iostream>
#ifndef stack_cpp
#define stack_cpp
#pragma once 
#include <cstdlib>
#include <string>
#include <iostream>
class allocator
{
protected:
allocator(size_t size = 0);
~allocator();
auto swap(allocator& other)->void;
allocator(allocator const&) = delete;
auto operator=(allocator const&)->allocator& = delete;
T * ptr_;
size_t size_;
size_t count_;
};
template <typename T1, typename T2>
auto construct(T1 * ptr, T2 const & value)->void {
new(ptr) T1(value);
}
template <typename T>
void destroy(T * ptr) noexcept
{
ptr->~T();
}
template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept
{
for (; first != last; ++first) {
destroy(&*first);
}
}
template <typename T>
allocator<T>::allocator(size_t size) : ptr_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))), size_(0), count_(size) {
};
template <typename T>
allocator<T>::~allocator() {
operator delete(ptr_);
};
template <typename T>
auto allocator<T>::swap(allocator& other)->void {
std::swap(ptr_, other.ptr_);
std::swap(size_, other.size_);
std::swap(count_, other.count_);
};


using namespace std;
template<typename T>
auto newcopy( const T * tmp, size_t size, size_t count) -> T* /*strong*/
{
      T * buff = new T[size];
    try {
    copy(tmp, tmp + count, buff);}
    catch(...){
    delete[] buff;
    throw; }
    
    return buff;
}

template <typename T>
class stack: private allocator
{
public:
    stack();
    stack(const stack &);
    stack& operator= (const stack &);
    size_t count() const;
    void push(T const &item);
    void pop();
    auto top() const -> const T&;
    bool empty_() const;
    ~stack();
    
    
    
};
template<typename T>

template <typename T>
stack<T>::stack() {}; /*noexcept*/
template <typename T>
stack<T>::~stack() { destroy(allocator<T>::ptr_, allocator<T>::ptr_ + allocator<T>::count_)
 } /*noexcept*/
template <typename T>
size_t  stack<T>::count() const { return allocator<T>::count_; }; /*noexcept*/
template <typename T>
void stack<T>::push(T const &item) /*noexcept*/
{
    if (allocator<T>::size_ <= allocator<T>::count_) { grow(); }
    
construct(allocator<T>::ptr_+allocator<T>::count_,val);
++allocator<T>::count_;
}

template<typename T>
void stack<T>::pop() { /*strong*/
    if (empty_()) {
        throw std::logic_error("Stack is empty!");
    }
destroy(allocator<T>::ptr_+allocator<T>::count_);
    --allocator<T>::count_ ;
    
}
template <typename T>
auto stack<T>::top() const -> const T& { /*strong*/
    if (empty_())
        throw std::range_error("Stack is empty!");
    else return allocator<T>::ptr_[allocator<T>::count_-1]
;

}
template <typename T>
void stack<T>::grow() { /*strong*/
    size_t new_array_size_=0;
    if (allocator<T>::size_ == allocator<T>::count_) new_array_size_= allocator<T>::size*2 + (allocator<T>::size==0);
    T *new_array_ = newcopy(allocator<T>::ptr_,new_array_size_,allocator<T>::count_);
     if (!empty_()) {
        delete[] allocator<T>::ptr_;
	allocator<T>::ptr_ = new_array_;
    	allocator<T>::size_ = new_array_size_;
        }
      
    
}
template <typename T>
bool stack<T>::empty_() const { /*noexcept*/
    return (allocator<T>::count_ == 0);
}
template <typename T>
stack<T>& stack<T>::operator=(const stack<T> &tmp) { /*strong*/
      array_ = newcopy(tmp.array_,tmp.array_size_,tmp.count_);
      if (this != &tmp) {
        delete [] allocator<T>::ptr_;
      allocator<T>::ptr_=array_;
       allocator<T>:: count_ = tmp.count_;
        allocator<T>::size_ = tmp.array_size_;
        
    }
    return *this;
}
template <typename T>
stack<T>::stack(const stack &tmp) /*noexcept*/
: allocator<T>::count_(tmp.count_),
allocator<T>::size_(tmp.array_size_),allocator<T>::ptr_(newcopy(tmp.array_, tmp.array_size_,tmp.count_))
{};

#endif
