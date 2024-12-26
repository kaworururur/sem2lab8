#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

template<class T>
class MyUnique
{
    T* ptr = nullptr;

public:
    explicit MyUnique(T* p) : ptr(p) {}

    ~MyUnique()
    {
        if (ptr)
            delete ptr;
    }

    T* get() const
    {
        return ptr;
    }

    T& operator*()
    {
        return *ptr;
    }

    T* operator->()
    {
        return ptr;
    }

    MyUnique(const MyUnique&) = delete;
    MyUnique& operator=(const MyUnique&) = delete;

    MyUnique(MyUnique&& other) noexcept
    {
        ptr = other.ptr;
        other.ptr = nullptr;
    }
};

template <typename T, typename... Args>
MyUnique<T> Make_MyUnique(Args&&... args)
{
    return MyUnique<T>(new T(std::forward<Args>(args)...));
}

class Student
{
private:
    std::string fio;
    std::vector<int> exams;

public:
    Student(const std::string& fio, const std::vector<int>& exams) : fio(fio), exams(exams) {}

    float averageGrade() const
    {
        if (exams.size() == 0) return 0;

        float sum = 0;
        for (int grade : exams)
        {
            sum += grade;
        }
        return sum / exams.size();
    }

    void printInfo() const
    {
        std::cout << "Student: " << fio << ", Exams: ";
        for (int grade : exams)
        {
            std::cout << grade << " ";
        }
        std::cout << std::endl;
    }

    const std::string& getFIO() const { return fio; }
};

int main()
{
    MyUnique<Student> student1 = Make_MyUnique<Student>("John Doe", std::vector<int>{90, 85, 95, 88});
    MyUnique<Student> student2 = Make_MyUnique<Student>("Alice Smith", std::vector<int>{88, 92, 85, 90});
    MyUnique<Student> student3 = Make_MyUnique<Student>("Bob Johnson", std::vector<int>{91, 87, 93, 89});

    student1->printInfo();
    student2->printInfo();
    student3->printInfo();

    std::vector<MyUnique<Student>> students;
    students.push_back(std::move(student1));
    students.push_back(std::move(student2));
    students.push_back(std::move(student3));

    std::sort(students.begin(), students.end(),
        [](const MyUnique<Student>& s1, const MyUnique<Student>& s2)
        {
            return s1->get()->averageGrade() > s2->get()->averageGrade();
        });

    std::cout << "All students:" << std::endl;
    for (const auto& student : students)
    {
        student->get()->printInfo();
    }

    std::cout << "\nTop 3 students:" << std::endl;
    size_t numPrint = std::min(students.size(), size_t(3));
    for (size_t i = 0; i < numPrint; ++i)
    {
        std::cout << "Rank " << i + 1 << ": ";
        students[i]->get()->printInfo();
    }

    return 0;
}
