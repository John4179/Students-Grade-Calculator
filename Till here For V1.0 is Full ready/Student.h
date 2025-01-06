

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>

    // Forward declaration of the operator<< function
    class Student;
std::ostream &operator<<(std::ostream &os, const Student &student);

class Student
{
private:
    std::string firstName;
    std::string surname;
    std::vector<double> homeworkResults;
    double examResult;
    double finalGrade;

public:
    // Constructor
    Student(const std::string &firstName, const std::string &surname);

    // Set scores for homework and exam
    void setScores(const std::vector<double> &hwResults, double exam);

    // Calculate the final grade based on homework and exam
    void calculateFinalGrade(bool useAverage);

    // Get the final grade
    double getFinalGrade() const;

    // Get the full name of the student
    std::string getFullName() const;

    // Declare operator<< as a friend function to access private members
    friend std::ostream &operator<<(std::ostream &os, const Student &student);
};

#endif // STUDENT_H
