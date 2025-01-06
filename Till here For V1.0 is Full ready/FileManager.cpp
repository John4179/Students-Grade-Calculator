

#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <random>
#include <iostream>
#include <stdexcept>
#include "Student.h"
#include <algorithm>
#include <typeinfo>

// Function to generate a list of random students and write to file
void FileManager::generateRandomStudentList(int numStudents, const std::string &filename)
{
    std::ofstream outFile(filename);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 10.0);

    outFile << "Name Surname HW1 HW2 HW3 HW4 HW5 HW6 HW7 Exam\n";

    for (int i = 0; i < numStudents; ++i)
    {
        outFile << "Name" << i + 1 << " Surname" << (i % 2 + 1); // Name pattern
        for (int j = 0; j < 7; ++j)
        {
            outFile << " " << dis(gen); // Random homework scores
        }
        outFile << " " << dis(gen) << "\n"; // Random exam score
    }
}

// Function to read student data from file and populate a vector
void FileManager::readStudentDataFromFile(const std::string &filename, std::vector<Student> &students)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string firstName, surname;
        double score;
        std::vector<double> homeworkScores;

        iss >> firstName >> surname;
        for (int i = 0; i < 7; ++i)
        {
            iss >> score;
            homeworkScores.push_back(score);
        }
        iss >> score; // Exam score

        Student student(firstName, surname);
        student.setScores(homeworkScores, score);
        students.push_back(student);
    }
}

// Function to read student data from file and populate a list
void FileManager::readStudentDataFromFile(const std::string &filename, std::list<Student> &students)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string firstName, surname;
        double score;
        std::vector<double> homeworkScores;

        iss >> firstName >> surname;
        for (int i = 0; i < 7; ++i)
        {
            iss >> score;
            homeworkScores.push_back(score);
        }
        iss >> score; // Exam score

        Student student(firstName, surname);
        student.setScores(homeworkScores, score);
        students.push_back(student);
    }
}

// Function to read student data from file and populate a deque
void FileManager::readStudentDataFromFile(const std::string &filename, std::deque<Student> &students)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string firstName, surname;
        double score;
        std::vector<double> homeworkScores;

        iss >> firstName >> surname;
        for (int i = 0; i < 7; ++i)
        {
            iss >> score;
            homeworkScores.push_back(score);
        }
        iss >> score; // Exam score

        Student student(firstName, surname);
        student.setScores(homeworkScores, score);
        students.push_back(student);
    }
}

// Function to write student data to file (for list)
void FileManager::writeStudentDataToFile(const std::list<Student> &students, const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    outFile << "Name Surname FinalGrade\n";
    for (const auto &student : students)
    {
        outFile << student.getFullName() << " " << student.getFinalGrade() << "\n";
    }
    outFile.close();
}

// Function to write student data to file (for vector)
void FileManager::writeStudentDataToFile(const std::vector<Student> &students, const std::string &filename)
{
    std::ofstream outFile(filename);

    if (!outFile) // Check if the file opened successfully
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Write the header to the file
    outFile << "Name Surname FinalGrade\n";

    // Write each student's data to the file in the same format as the list
    for (const auto &student : students)
    {
        outFile << student.getFullName() << " " << student.getFinalGrade() << "\n";
    }

    outFile.close(); // Explicitly close the file

    // Check if there was an error closing the file
    if (outFile.fail())
    {
        std::cerr << "Error closing file: " << filename << std::endl;
    }
    else
    {
        std::cout << "File written successfully!" << std::endl;
    }
}

// Function to write student data to file (for deque)
void FileManager::writeStudentDataToFile(const std::deque<Student> &students, const std::string &filename)
{
    std::ofstream outFile(filename);
    outFile << "Name Surname FinalGrade\n";
    for (const auto &student : students)
    {
        outFile << student.getFullName() << " " << student.getFinalGrade() << "\n"; // Ensure the output stream is formatted
    }
}
// Function to split students into passed and failed containers
template <typename T>
void FileManager::splitStudentsIntoTwoContainers(const T &students, T &passed, T &failed, const std::string &passedFile, const std::string &failedFile)
{
    for (const auto &student : students)
    {
        double finalGrade = student.getFinalGrade();

        if (finalGrade >= 5.0) // Assuming 5.0 as the passing grade threshold
            passed.push_back(student);
        else
            failed.push_back(student);
    }

    // Write to file for passed and failed students
    writeStudentDataToFile(passed, passedFile);
    writeStudentDataToFile(failed, failedFile);
}

bool hasPassed(const Student &student)
{
    return student.getFinalGrade() >= 5.0; // Pass if final grade >= 5.0
}

// Template function to move students to passed or failed containers
// Function to move students to passed or failed containers and sort the students
template <class T>
void FileManager::moveStudentsToPassedOrFailed(T &students, T &passed, T &failed)
{
    // Assume the passing grade is 5.0 (or any other threshold value)
    double passingGrade = 5.0;

    // Move students based on their final grade
    for (auto it = students.begin(); it != students.end();)
    {
        if (it->getFinalGrade() >= passingGrade)
        {
            passed.push_back(*it);   // Move passed student to 'passed' container
            it = students.erase(it); // Remove from original container
        }
        else
        {
            failed.push_back(*it);   // Move failed student to 'failed' container
            it = students.erase(it); // Remove from original container
        }
    }

    // Now we need to write the results into separate files
    writeResultsToFile(passed, failed, students); // Write the passed, failed, and sorted students
}

// Modified function to write student data to file for passed, failed, and sorted students

template <class T>
void FileManager::writeResultsToFile(const T &passed, const T &failed, const T &sorted)
{
    // Define the container type (list, vector, deque)
    std::string containerType;

    if (typeid(T) == typeid(std::list<Student>))
    {
        containerType = "list";
    }
    else if (typeid(T) == typeid(std::vector<Student>))
    {
        containerType = "vector";
    }
    else if (typeid(T) == typeid(std::deque<Student>))
    {
        containerType = "deque";
    }
    else
    {
        containerType = "unknown";
    }

    // Define file names based on the container type
    std::string passedFileName = "S2_Pass_Student_" + containerType + ".txt";
    std::string failedFileName = "S2_Fail_Student_" + containerType + ".txt";
    std::string sortedFileName = "S2_Sorted_Student_" + containerType + ".txt";

    // Write passed students to the corresponding file
    std::ofstream passedFile(passedFileName);
    if (passedFile.is_open())
    {
        for (const auto &student : passed)
        {
            passedFile << student << std::endl; // Write passed students to file
        }
        passedFile.close();
    }

    // Write failed students to the corresponding file
    std::ofstream failedFile(failedFileName);
    if (failedFile.is_open())
    {
        for (const auto &student : failed)
        {
            failedFile << student << std::endl; // Write failed students to file
        }
        failedFile.close();
    }

    // Combine passed and failed students into a single container for sorting
    std::vector<Student> allStudents;
    allStudents.insert(allStudents.end(), passed.begin(), passed.end());
    allStudents.insert(allStudents.end(), failed.begin(), failed.end());

    // Sort the students by final grade in descending order
    std::sort(allStudents.begin(), allStudents.end(), [](const Student &a, const Student &b)
              {
                  return a.getFinalGrade() > b.getFinalGrade(); // Sort by final grade (descending order)
              });

    // Write sorted students to the corresponding file
    std::ofstream sortedFile(sortedFileName);
    if (sortedFile.is_open())
    {
        for (const auto &student : allStudents)
        {
            sortedFile << student << std::endl; // Write all students to sorted file
        }
        sortedFile.close();
    }
}

// Explicit template instantiations for vector, list, deque
template void FileManager::writeResultsToFile<std::vector<Student>>(const std::vector<Student> &, const std::vector<Student> &, const std::vector<Student> &);
template void FileManager::writeResultsToFile<std::list<Student>>(const std::list<Student> &, const std::list<Student> &, const std::list<Student> &);
template void FileManager::writeResultsToFile<std::deque<Student>>(const std::deque<Student> &, const std::deque<Student> &, const std::deque<Student> &);

// Explicit instantiations for different containers
template void FileManager::moveStudentsToPassedOrFailed<std::vector<Student>>(std::vector<Student> &, std::vector<Student> &, std::vector<Student> &);
template void FileManager::moveStudentsToPassedOrFailed<std::list<Student>>(std::list<Student> &, std::list<Student> &, std::list<Student> &);
template void FileManager::moveStudentsToPassedOrFailed<std::deque<Student>>(std::deque<Student> &, std::deque<Student> &, std::deque<Student> &);

// Explicit template instantiation for different container types
template void FileManager::splitStudentsIntoTwoContainers<std::vector<Student>>(const std::vector<Student> &students, std::vector<Student> &passed, std::vector<Student> &failed, const std::string &passedFile, const std::string &failedFile);
template void FileManager::splitStudentsIntoTwoContainers<std::list<Student>>(const std::list<Student> &students, std::list<Student> &passed, std::list<Student> &failed, const std::string &passedFile, const std::string &failedFile);
template void FileManager::splitStudentsIntoTwoContainers<std::deque<Student>>(const std::deque<Student> &students, std::deque<Student> &passed, std::deque<Student> &failed, const std::string &passedFile, const std::string &failedFile);
