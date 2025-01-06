

#include "Student.h"
#include <algorithm>

    // Constructor to initialize a Student object with a first name and surname
    Student::Student(const std::string &firstName, const std::string &surname)
    : firstName(firstName),
surname(surname), examResult(0.0), finalGrade(0.0)
{
}

// Set scores for homework and exam
void Student::setScores(const std::vector<double> &hwResults, double exam)
{
    homeworkResults = hwResults;
    examResult = exam;
}

// Calculate the final grade based on homework and exam
void Student::calculateFinalGrade(bool useAverage)
{
    if (homeworkResults.empty())
    {
        finalGrade = examResult * 0.6; // If no homework, final grade is based on the exam only.
        return;
    }

    if (useAverage)
    {
        double sum = 0;
        for (double score : homeworkResults)
        {
            sum += score;
        }
        finalGrade = (sum / homeworkResults.size() * 0.4) + (examResult * 0.6);
    }
    else
    {
        // Median calculation
        std::vector<double> sortedResults = homeworkResults;
        std::sort(sortedResults.begin(), sortedResults.end());
        double median;
        size_t size = sortedResults.size();
        if (size % 2 == 0)
        {
            median = (sortedResults[size / 2 - 1] + sortedResults[size / 2]) / 2.0;
        }
        else
        {
            median = sortedResults[size / 2];
        }
        finalGrade = (median * 0.4) + (examResult * 0.6);
    }
}

// Get the final grade
double Student::getFinalGrade() const
{
    return finalGrade;
}

// Get the full name of the student
std::string Student::getFullName() const
{
    return firstName + " " + surname;
}

// Operator<< to output the Student's information
std::ostream &operator<<(std::ostream &os, const Student &student)
{
    os << student.getFullName() << " - Final Grade: " << student.getFinalGrade();
    return os;
}
