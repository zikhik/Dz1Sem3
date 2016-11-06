#ifndef stack_cpp
#define stack_cpp
#pragma once
#include <cstdlib>
#include <string>
#include <iostream>
#include <new>
#include <stdexcept>
#include <vector>
#include <memory>

class bitset
{
public:
    explicit
    bitset(size_t size) /*strong*/;
    
    bitset(bitset const & other) = delete;
    auto operator =(bitset const & other)->bitset & = delete;
    bitset(bitset && other) = delete;
    auto operator =(bitset && other)->bitset & = delete;
    
    
    auto set(size_t index) /*strong*/ -> void;
    auto reset(size_t index) /*strong*/ -> void;
    auto test(size_t index) /*strong*/ -> bool;
    auto counter() /*noexcept*/ -> size_t;
    auto size() /*noexcept*/ -> size_t;
    
private:
    std::unique_ptr<bool[]>  ptr_;
    size_t size_;
    size_t counter_;
};

auto bitset::size()-> size_t {
    return size_;
}
auto bitset::counter()-> size_t {
    return counter_;
}

bitset::bitset(size_t size) :
ptr_(std::make_unique<bool[]>(size)),
size_(size),counter_(0) {
    
}



auto bitset::reset(size_t index)->void {
    
    if (index <= size()) {
        if (test(index) != false) {
            ptr_[index] = false;
            --counter_;
        }
    }
    else {
        throw std::out_of_range("Error");
    }
}



auto bitset::set(size_t index)->void {
    
    
    if (index <= size()) {
        if (test(index) != true) {
            
            ptr_[index] = true;
            ++counter_;
            std::cout << counter_ << " counter" << std::endl;
            }
            }
            else {
                throw std::out_of_range("Error");
            }
            
            
            }
            
            
            auto bitset::test(size_t index) ->bool{
                if (index <= size()) {
                    return ptr_[index];
                }
                else {
                    throw std::out_of_range("Error");
                }
            }

            
            template <typename T>
            class allocator
            {
            public:
                explicit
                allocator(std::size_t size = 0) /*strong*/;
                allocator(allocator const & other) /*strong*/;
                auto operator =(allocator const & other)->allocator & = delete;
                ~allocator();/*noexcept*/
                
                auto resize() /*strong*/ -> void;
                
                auto construct(T * ptr, T const & value) /*strong*/ -> void;
                auto destroy(T * ptr) /*noexcept*/ -> void;
                
                auto get() /*noexcept*/ -> T *;
                auto get() const /*noexcept*/ -> T const *;
                
                auto count() const /*noexcept*/ -> size_t;
                auto full() const /*noexcept*/ -> bool;
                auto empty() const /*noexcept*/ -> bool;
                auto swap(allocator & other) /*noexcept*/ -> void;
            private:
                auto destroy(T * first, T * last) /*noexcept*/ -> void;
                
                
                size_t size_;
                T * ptr_;
                std::unique_ptr<bitset> map_;
            };
            
            
template <typename T>
auto allocator<T>::construct(T * ptr, T const & value)->void
{
    
        if (ptr < ptr_ || ptr >= ptr_ + size_)
    {
        throw std::out_of_range("Error");
    }
    new(ptr) T(value);
    map_->set(ptr - ptr_);
}
template <typename T>
auto allocator<T>::destroy(T * ptr)->void
{
    ptr->~T();
    map_->reset(ptr - ptr_);
}
template <typename T>
void destroy(T first, T last) noexcept
{
    for (; first != last; ++first) {
        destroy(&*first);
    }
}
template <typename T>
allocator<T>::allocator(size_t size) : ptr_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))), size_(size), map_(std::unique_ptr<bitset>(size)) {
};
          
template <typename T>
allocator<T>::allocator(allocator const & tmp) :allocator<T>(tmp.size_)
            {
                for (size_t i = 0; i < size_; ++i)
                {
                    construct(ptr_ + i, tmp.ptr_[i]);
                }
            }
template <typename T>
allocator<T>::~allocator()
            {
                if (map_->counter() > 0)
                {
                    destroy(ptr_, ptr_ + map_->counter());
                }
                operator delete(ptr_);
            };
template <typename T>
auto allocator<T>::swap(allocator& other)->void {
    std::swap(ptr_, other.ptr_);
    std::swap(size_, other.size_);
    std::swap(map_, other.map_);
};
            
            template<typename T>//увеличиваем память
            auto allocator<T>::resize()-> void {
                size_t size = size_ * 2 + (size_ == 0);
                allocator<T> buff(size);
                for (size_t i = 0; i < size_; ++i) {
                    if (map_->test(i))
                    {		buff.construct(buff.ptr_ + i, ptr_[i]);}
                }
                this->swap(buff);
                size_ = size;
            }
            
            template<typename T>//проверка на пустоту
            auto allocator<T>::empty() const -> bool {
                return (map_->counter() == 0);
            }
            
            template<typename T>//проверка на заполненность
            auto allocator<T>::full() const -> bool {
                return (map_->counter() == size_);
            }
            
            template<typename T>//получить ptr_
            auto allocator<T>::get() -> T * {
                return ptr_;
            }
            
            template<typename T>//получить ptr_ const метод
            auto allocator<T>::get() const -> T const * {
                return ptr_;
            }
            
            template<typename T>//вернуть count_
            auto allocator<T>::count() const -> size_t {
                return map_->counter();
            };
            


template<typename T>
auto newcopy( const T * tmp, size_t size, size_t count) -> T* /*strong*/
{
    T * buff = new T[size];
    try {
        std::copy(tmp, tmp + count, buff);}
    catch(...){
        delete[] buff;
        throw; }
    
    return buff;
}

template <typename T>
class stack
{
public:
    explicit
    stack(size_t=0);
    stack(const stack &) = default;
    auto operator= (const stack &) -> stack &;;
    size_t count() const;
    void push(T const &item);
    void pop();
    void grow();
    auto top() const -> T&;
    auto top() const -> T const &;
    bool empty_() const;
    ~stack();
private: allocator<T> allocate;
    
    
    
};

template <typename T>
stack<T>::stack(size_t size):allocator<T>(size) {}; /*noexcept*/

template <typename T>
size_t  stack<T>::count() const { return allocator<T>::count_; }; /*noexcept*/

template <typename T>
void stack<T>::push(T const &item) /*noexcept*/
{
 if (allocate.full()) { allocate.resize(); }
    allocate.construct(allocate.get() + allocate.count(), item);
}

template<typename T>
void stack<T>::pop() { /*strong*/
    if (empty_()) throw std::logic_error("Stack is empty!");
    destroy(allocator<T>::ptr_+allocator<T>::count_);
    --allocator<T>::count_ ;
    
}
template <typename T>
auto stack<T>::top() const ->  T const & { /*strong*/
    if (allocate.count() == 0) throw std::range_error("Stack is empty!");
        return (*(allocate.get() + this->count() - 1 ));
    
}

 template <typename T>
 auto stack<T>::top() const->T &{
     if (allocate.count() == 0) throw std::logic_error("Empty!");
        return(*(allocate.get() + this->count() - 1));
                
}
template <typename T>
void stack<T>::grow() { /*strong*/
    size_t array_size = max(this->size_ * 2, 0);
    
    stack temp{array_size};
    while (temp.count() < this->count_) {
        temp.push(this->ptr_[temp.count()]);
    }
    
    this->swap(temp);
}


template <typename T>
bool stack<T>::empty_() const { /*noexcept*/
    return (allocate.count_ == 0);
}
template <typename T>
stack<T>& stack<T>::operator=(const stack<T> &tmp) { /*strong*/
    if (this != &tmp) { (stack(tmp)).allocate.swap(allocate); }
    return *this;


#endif
