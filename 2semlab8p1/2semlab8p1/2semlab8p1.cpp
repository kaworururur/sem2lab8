#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Student.hpp"
#include "Student.cpp"

template<class T>
class Myunique {
private:
    T* p = nullptr;
public:
    //для управления одиночным динамическим объектом, обеспечивает уникальную собственность для избежания утечек памяти
    Myunique(T* ptr) : p(ptr) {}

    ~Myunique() {
        delete p;
    }

    T* get() const {
        return p;
    }

    T& operator*() {
        return *p;
    }

    T* operator->() {
        return p;
    }

    Myunique(const Myunique<T>&) = delete;
    Myunique<T>& operator=(const Myunique<T>& other) = delete;

    Myunique(Myunique<T>&& other) noexcept {
        p = other.p;
        other.p = nullptr;
    }

    Myunique<T>& operator=(Myunique<T>&& other) noexcept {
        if (this != &other) {
            delete p;
            p = other.p;
            other.p = nullptr;
        }
        return *this;
    }

}; template<class T, class... Args>
Myunique<T> Make_Myunique(Args... args) {
    return Myunique<T>(new T(std::forward<Args>(args)...));
}


template<class T>
//для управления динамическим объектом для подсчета ссылок, обеспечивает поддержку общего владения объектом с несколькими указателями
class Myshared {
private:
    T* p = nullptr;
    size_t* count = nullptr;
public:
    Myshared(T* ptr) : p(ptr), count(new size_t(1)) {}

    ~Myshared() {
        if (*count == 1) {
            delete p;
            delete count;
        }
        else {
            (*count)--;
        }
    }

    Myshared(const Myshared<T>& other) {
        p = other.p;
        count = other.count;
        (*count)++;
    }

    Myshared<T>& operator=(Myshared<T> other) {
        std::swap(p, other.p);
        std::swap(count, other.count);
        return *this;
    }
    //для подсчета ссылок в объекта
    size_t get_ptrCount() const{
        if (p) return *count;
        return 0;
        }

    T* get() const {
        return p;
    }

    T& operator*() {
        return *p;
    }

    T* operator->() {
        return p;
    }
};

template<class T, class... Args>
Myshared<T> Make_Myshared(Args&&... args) {
    return Myshared<T>(new T(std::forward<Args>(args)...));
}

int main(){
    std::vector<int> grades;
    for (int i = 0; i < 4; ++i) {
        grades.push_back(i);
    }
   //Unique
    auto ptr = Make_Myunique<Student>("Bobus.K.T", grades);

    //Shared
    auto ptr1 = Make_Myshared<Student>("aaa", grades);
    auto ptr2 = ptr1;
    auto ptr4 = Make_Myshared<Student>("sdn", grades);


    std::cout << "ptr1 " << ptr1.get_ptrCount() << "\n";
    std::cout << "ptr2 " << ptr2.get_ptrCount() << std::endl;
    //std::cout << ptr3.get_ptrCount() << std::endl;
    std::cout << "ptr4 " << ptr4.get_ptrCount() << "\n";

    {
        auto ptr3 = ptr2;
        auto ptr5 = ptr4;
        std::cout << "ptr1 " << ptr1.get_ptrCount() << std::endl;
        std::cout << "ptr2 " << ptr2.get_ptrCount() << std::endl;
        std::cout << "ptr3 " << ptr3.get_ptrCount() << std::endl;
        std::cout << "ptr4 " << ptr4.get_ptrCount() << "\n";
        std::cout << "ptr5 " << ptr5.get_ptrCount() << "\n";
    }
    std::cout << "ptr1 " << ptr1.get_ptrCount() << std::endl;
    std::cout << "ptr2 " << ptr2.get_ptrCount() << std::endl;
    std::cout << "ptr4 " << ptr4.get_ptrCount() << "\n";
    return 0;
}

