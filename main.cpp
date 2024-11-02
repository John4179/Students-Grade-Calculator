#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

class Person {
private:
    std::string firstName;
    std::string surname;
    std::vector<double> homeworkResults;
    double examResult;
    double finalGrade;

public:
    // Constructor
    Person(const std::string& firstName, const std::string& surname)
        : firstName(firstName), surname(surname), examResult(0.0), finalGrade(0.0) {}

    // Copy Constructor
    Person(const Person& other)
        : firstName(other.firstName), surname(other.surname),
          homeworkResults(other.homeworkResults), examResult(other.examResult),
          finalGrade(other.finalGrade) {}

    // Assignment Operator
    Person& operator=(const Person& other) {
        if (this == &other) return *this; // Self-assignment check
        firstName = other.firstName;
        surname = other.surname;
        homeworkResults = other.homeworkResults;
        examResult = other.examResult;
        finalGrade = other.finalGrade;
        return *this;
    }

    // Destructor
    ~Person() {}

    // Data Input Method
    friend std::istream& operator>>(std::istream& is, Person& person) {
        int hwCount;
        std::cout << "Enter the number of homework assignments: ";
        is >> hwCount;
        person.homeworkResults.resize(hwCount);

        for (int i = 0; i < hwCount; ++i) {
            std::cout << "Homework " << (i + 1) << ": ";
            is >> person.homeworkResults[i];
        }

        std::cout << "Enter exam result: ";
        is >> person.examResult;
        return is;
    }

    // Data Output Method
    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << std::setw(10) << person.firstName
           << std::setw(15) << person.surname
           << std::setw(15) << std::fixed << std::setprecision(2) << person.finalGrade;
        return os;
    }

    // Calculation Method for Final Grade
    void calculateFinalGrade(bool useAverage) {
        double hwScore = 0.0;
        if (useAverage) {
            hwScore = std::accumulate(homeworkResults.begin(), homeworkResults.end(), 0.0) / homeworkResults.size();
        } else {
            std::sort(homeworkResults.begin(), homeworkResults.end());
            if (homeworkResults.size() % 2 == 0) {
                hwScore = (homeworkResults[homeworkResults.size() / 2 - 1] +
                           homeworkResults[homeworkResults.size() / 2]) / 2.0;
            } else {
                hwScore = homeworkResults[homeworkResults.size() / 2];
            }
        }
        finalGrade = 0.4 * hwScore + 0.6 * examResult;
    }
};

int main() {
    int personCount;
    std::cout << "Enter the number of persons: ";
    std::cin >> personCount;

    std::vector<Person> persons;
    for (int i = 0; i < personCount; ++i) {
        std::string firstName, surname;
        std::cout << "Enter first name and surname for person " << i + 1 << ": ";
        std::cin >> firstName >> surname;

        Person person(firstName, surname);
        std::cin >> person;

        persons.push_back(person);
    }

    char choice;
    std::cout << "Calculate final grade using (A)verage or (M)edian of homework scores? (A/M): ";
    std::cin >> choice;
    bool useAverage = (choice == 'A' || choice == 'a');

    // Calculate Final Grades for All Students
    for (auto& person : persons) {
        person.calculateFinalGrade(useAverage);
    }

    // Display Final Grades
    std::cout << std::setw(10) << "Name"
              << std::setw(15) << "Surname"
              << std::setw(15) << "Final_Point(Aver.)"
              << "\n-------------------------------------------\n";

    for (const auto& person : persons) {
        std::cout << person << std::endl;
    }

    return 0;
}