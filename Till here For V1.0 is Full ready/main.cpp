

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include "Student.h"
#include "FileManager.h"
#include "Sorting.h"
#include "Timer.h"

void handleStudentContainerOperations(std::string filename, int containerChoice)
{
    Timer timer;
    double readTime = 0.0, sortTime = 0.0, splitTime = 0.0, writeTime = 0.0;

    // Containers for passed and failed students
    std::vector<Student> passedVector, failedVector;
    std::list<Student> passedList, failedList;
    std::deque<Student> passedDeque, failedDeque;

    if (containerChoice == 1)
    {
        std::list<Student> students;
        timer.startTimer();
        FileManager::readStudentDataFromFile(filename, students);
        readTime = timer.stopTimer();
        std::cout << "Data reading took " << readTime << " seconds.\n";

        char gradeChoice;
        std::cout << "Calculate final grade using (A)verage or (M)edian? ";
        std::cin >> gradeChoice;
        bool useAverage = (gradeChoice == 'A' || gradeChoice == 'a');
        for (auto &student : students)
        {
            student.calculateFinalGrade(useAverage);
        }

        timer.startTimer();
        Sorting::sortStudents(students);
        sortTime = timer.stopTimer();
        std::cout << "Data sorting took " << sortTime << " seconds.\n";

        int strategyChoice;
        std::cout << "Select strategy:\n";
        std::cout << "1. Split into two new containers (passed and failed)\n";
        std::cout << "2. Move students to 'failed' or 'passed' containers\n";
        std::cout << "Enter your choice: ";
        std::cin >> strategyChoice;

        if (strategyChoice == 1)
        {
            timer.startTimer();
            FileManager::splitStudentsIntoTwoContainers(students, passedList, failedList, "S1_Pass_Students_List.txt", "S1_Fail_Students_List.txt");
            splitTime = timer.stopTimer();
            std::cout << "Data splitting into two containers took " << splitTime << " seconds.\n";
        }
        else if (strategyChoice == 2)
        {
            timer.startTimer();
            FileManager::moveStudentsToPassedOrFailed(students, passedList, failedList);
            splitTime = timer.stopTimer();
            std::cout << "Data moved to passed/failed containers took " << splitTime << " seconds.\n";
        }

        timer.startTimer();
        FileManager::writeStudentDataToFile(students, "S1_Sorted_Students_List.txt");
        writeTime = timer.stopTimer();
        std::cout << "Writing data took " << writeTime << " seconds.\n";
    }
    else if (containerChoice == 2)
    {
        std::deque<Student> students;
        timer.startTimer();
        FileManager::readStudentDataFromFile(filename, students);
        readTime = timer.stopTimer();
        std::cout << "Data reading took " << readTime << " seconds.\n";

        char gradeChoice;
        std::cout << "Calculate final grade using (A)verage or (M)edian? ";
        std::cin >> gradeChoice;
        bool useAverage = (gradeChoice == 'A' || gradeChoice == 'a');
        for (auto &student : students)
        {
            student.calculateFinalGrade(useAverage);
        }

        timer.startTimer();
        Sorting::sortStudents(students);
        sortTime = timer.stopTimer();
        std::cout << "Data sorting took " << sortTime << " seconds.\n";

        int strategyChoice;
        std::cout << "Select strategy:\n";
        std::cout << "1. Split into two new containers (passed and failed)\n";
        std::cout << "2. Move students to 'failed' or 'passed' containers\n";
        std::cout << "Enter your choice: ";
        std::cin >> strategyChoice;

        if (strategyChoice == 1)
        {
            timer.startTimer();
            FileManager::splitStudentsIntoTwoContainers(students, passedDeque, failedDeque, "S1_Pass_Students_deque.txt", "S1_Fail_Students_deque.txt");
            splitTime = timer.stopTimer();
            std::cout << "Data splitting into two containers took " << splitTime << " seconds.\n";
        }
        else if (strategyChoice == 2)
        {
            timer.startTimer();
            FileManager::moveStudentsToPassedOrFailed(students, passedDeque, failedDeque);
            splitTime = timer.stopTimer();
            std::cout << "Data moved to passed/failed containers took " << splitTime << " seconds.\n";
        }

        timer.startTimer();
        FileManager::writeStudentDataToFile(students, "S1_Sorted_Student_deque.txt");
        writeTime = timer.stopTimer();
        std::cout << "Writing data took " << writeTime << " seconds.\n";
    }
    else if (containerChoice == 3)
    {
        std::vector<Student> students;
        timer.startTimer();
        FileManager::readStudentDataFromFile(filename, students);
        readTime = timer.stopTimer();
        std::cout << "Data reading took " << readTime << " seconds.\n";

        char gradeChoice;
        std::cout << "Calculate final grade using (A)verage or (M)edian? ";
        std::cin >> gradeChoice;
        bool useAverage = (gradeChoice == 'A' || gradeChoice == 'a');
        for (auto &student : students)
        {
            student.calculateFinalGrade(useAverage);
        }

        timer.startTimer();
        Sorting::sortStudents(students);
        sortTime = timer.stopTimer();
        std::cout << "Data sorting took " << sortTime << " seconds.\n";

        int strategyChoice;
        std::cout << "Select strategy:\n";
        std::cout << "1. Split into two new containers (passed and failed)\n";
        std::cout << "2. Move students to 'failed' or 'passed' containers\n";
        std::cout << "Enter your choice: ";
        std::cin >> strategyChoice;

        if (strategyChoice == 1)
        {
            timer.startTimer();
            FileManager::splitStudentsIntoTwoContainers(students, passedVector, failedVector, "S1_Pass_Students_vector.txt", "S1_Fail_Students_vector.txt");
            splitTime = timer.stopTimer();
            std::cout << "Data splitting into two containers took " << splitTime << " seconds.\n";
        }
        else if (strategyChoice == 2)
        {
            timer.startTimer();
            FileManager::moveStudentsToPassedOrFailed(students, passedVector, failedVector);
            splitTime = timer.stopTimer();
            std::cout << "Data moved to passed/failed containers took " << splitTime << " seconds.\n";
        }

        timer.startTimer();
        FileManager::writeStudentDataToFile(students, "S1_Sorted_Students_vector.txt");
        writeTime = timer.stopTimer();
        std::cout << "Writing data took " << writeTime << " seconds.\n";
    }

    double totalTime = readTime + sortTime + splitTime + writeTime;
    std::cout << "\nTotal time for all operations: " << totalTime << " seconds.\n";
}

int main()
{
    int choice;
    bool exitProgram = false;

    while (!exitProgram)
    {
        std::cout << "\nWhat would you like to do?\n";
        std::cout << "1. Generate a random student list\n";
        std::cout << "2. Sort students\n";
        std::cout << "3. Calculate final grade (Average/Median)\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        try
        {
            switch (choice)
            {
            case 1:
            {
                int numStudents;
                std::string filename;
                std::cout << "How many students to generate? ";
                std::cin >> numStudents;
                std::cout << "Enter the filename to save: ";
                std::cin >> filename;
                FileManager::generateRandomStudentList(numStudents, filename);
                break;
            }
            case 2:
            {
                std::string filename;
                std::cout << "Enter the filename to read from: ";
                std::cin >> filename;

                int containerChoice;
                std::cout << "Select container:\n1. List\n2. Deque\n3. Vector\nEnter your choice: ";
                std::cin >> containerChoice;

                handleStudentContainerOperations(filename, containerChoice);
                break;
            }
            case 3:
            {
                std::string inputFilename, outputFilename;
                std::cout << "Enter the filename to read from: ";
                std::cin >> inputFilename;

                // Read the student data from the file
                std::vector<Student> students;
                FileManager::readStudentDataFromFile(inputFilename, students);

                // Ask the user whether to calculate average or median
                char gradeChoice;
                std::cout << "Calculate final grade using (A)verage or (M)edian? ";
                std::cin >> gradeChoice;
                bool useAverage = (gradeChoice == 'A' || gradeChoice == 'a');

                // Calculate final grades for each student
                for (auto &student : students)
                {
                    student.calculateFinalGrade(useAverage);
                }

                std::cout << "Enter the filename to save the results: ";
                std::cin >> outputFilename;

                // Save the updated student data with final grades to the output file
                FileManager::writeStudentDataToFile(students, outputFilename);

                std::cout << "Final grades have been calculated and saved to " << outputFilename << ".\n";
                break;
            }

            case 4:
                exitProgram = true;
                std::cout << "Exiting program.\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
