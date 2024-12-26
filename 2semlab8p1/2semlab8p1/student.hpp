#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>

class Student {
private:
    std::string fullName;
    std::vector<int> examGrades;

public:
    // �����������
    Student(const std::string& name, const std::vector<int>& grades);

    // ������� ����������� �������� �����
    double calculateAverageGrade() const;

    // ������� ������ ����������
    void printInfo() const;
};

#endif
