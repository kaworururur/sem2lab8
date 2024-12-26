#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>

class Student {
private:
    std::string fullName;
    std::vector<int> examGrades;

public:
    // Конструктор
    Student(const std::string& name, const std::vector<int>& grades);

    // Функция определения среднего балла
    double calculateAverageGrade() const;

    // Функция печати параметров
    void printInfo() const;
};

#endif
