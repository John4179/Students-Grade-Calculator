

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <iostream>
#include "Student.h"

// Include the header for the Student class
#include "Student.h" // Assuming you have a separate Student.h file

    class FileManager
{
public:
    // Function declarations
    static void generateRandomStudentList(int numStudents, const std::string &filename);
    static void readStudentDataFromFile(const std::string &filename, std::vector<Student> &students);
    static void readStudentDataFromFile(const std::string &filename, std::list<Student> &students);
    static void readStudentDataFromFile(const std::string &filename, std::deque<Student> &students);
    static void writeStudentDataToFile(const std::vector<Student> &students, const std::string &filename);
    static void writeStudentDataToFile(const std::list<Student> &students, const std::string &filename);
    static void writeStudentDataToFile(const std::deque<Student> &students, const std::string &filename);

    template <typename T>
    static void splitStudentsIntoTwoContainers(const T &students, T &passed, T &failed, const std::string &passedFile, const std::string &failedFile);

    template <class T>
    static void moveStudentsToPassedOrFailed(T &students, T &passed, T &failed);

    // Function to write results to file
    template <class T>
    static void writeResultsToFile(const T &passed, const T &failed, const T &sorted);

private:
    // Additional private member functions if necessary
};

#endif // FILE_MANAGER_H
