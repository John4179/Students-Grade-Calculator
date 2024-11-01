#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>

class Person {
private:
    std::string firstName;
    std::string surname;
    std::vector<double> homeworkResults;
    double examResult;
    double finalGrade;

public:
    // Constructor to initialize first name, surname, and default scores
    Person(const std::string& firstName, const std::string& surname)
        : firstName(firstName), surname(surname), examResult(0.0), finalGrade(0.0) {}

    // Copy constructor for duplicating a Person object
    Person(const Person& other)
        : firstName(other.firstName), surname(other.surname),
          homeworkResults(other.homeworkResults), examResult(other.examResult),
          finalGrade(other.finalGrade) {}

    // Overload of assignment operator to handle object copying
    Person& operator=(const Person& other) {
        if (this == &other) return *this; // Check for self-assignment
        firstName = other.firstName;
        surname = other.surname;
        homeworkResults = other.homeworkResults;
        examResult = other.examResult;
        finalGrade = other.finalGrade;
        return *this;
    }

    // Destructor
    ~Person() {}

    // Sets homework scores and exam result for the student
    void setScores(const std::vector<double>& hwResults, double exam) {
        homeworkResults = hwResults;
        examResult = exam;
    }

    // Overloaded output stream operator for displaying Person details
    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << std::setw(10) << person.firstName
           << std::setw(15) << person.surname
           << std::setw(15) << std::fixed << std::setprecision(2) << person.finalGrade;
        return os;
    }

    // Calculates the final grade based on either the average or median of homework scores
    void calculateFinalGrade(bool useAverage) {
        double hwScore = 0.0;

        // Calculate average or median of homework scores
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

        // Calculate final grade as 40% homework and 60% exam score
        finalGrade = 0.4 * hwScore + 0.6 * examResult;
    }
};

int main() {
    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return 1; // Exit if file opening fails
    }

    std::vector<Person> persons;
    std::string line;

    // Skip header line in input file
    std::getline(infile, line);

    // Read each line of the file
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string firstName, surname;
        double score;
        std::vector<double> homeworkScores;

        // Read first name and surname
        iss >> firstName >> surname;

        // Read and store homework scores
        for (int i = 0; i < 5; ++i) { // Modify this number based on the input file
            iss >> score;
            homeworkScores.push_back(score);
        }

        // Read exam score
        double examScore;
        iss >> examScore;

        // Create Person object, set scores, and add to list
        Person person(firstName, surname);
        person.setScores(homeworkScores, examScore);
        persons.push_back(person);
    }

    infile.close(); // Close input file

    // Prompt user to choose grading method
    char choice;
    std::cout << "Calculate final grade using (A)verage or (M)edian of homework scores? (A/M): ";
    std::cin >> choice;
    bool useAverage = (choice == 'A' || choice == 'a');

    // Calculate final grades for each student
    for (auto& person : persons) {
        person.calculateFinalGrade(useAverage);
    }

    // Display final grades
    std::cout << std::setw(10) << "Name"
              << std::setw(15) << "Surname"
              << std::setw(15) << "Final Grade"
              << "\n-------------------------------------------\n";

    for (const auto& person : persons) {
        std::cout << person << std::endl;
    }

    return 0;
}
