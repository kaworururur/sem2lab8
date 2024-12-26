#include "Student.hpp"
#include <iostream>
#include <algorithm>

Student::Student(const std::string& name, const std::vector<int>& grades) : fullName(name), examGrades(grades) {
}

double Student::calculateAverageGrade() const {
    double sum = 0;
    for (int grade : examGrades) {
        sum += grade;
    }
    return sum / examGrades.size();
}

void Student::printInfo() const {
    std::cout << "Full Name: " << fullName << std::endl;
    std::cout << "Exam Grades: ";
    for (int grade : examGrades) {
        std::cout << grade << " ";
    }
    std::cout << std::endl;
}