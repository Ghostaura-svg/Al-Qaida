#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

struct Student {
    std::string name;
    int rollNumber;
    std::string department;
    double gpa;
    std::string contactInfo;
};

// Function prototypes
void loadStudentsFromFile(std::vector<Student>& students);
void saveStudentsToFile(const std::vector<Student>& students);
void addNewStudent(std::vector<Student>& students);
void viewAllStudents(const std::vector<Student>& students);
void viewStudentByRollNumber(const std::vector<Student>& students);
void updateStudentInfo(std::vector<Student>& students);
void deleteStudentRecord(std::vector<Student>& students);
void searchStudents(const std::vector<Student>& students);
void sortAndDisplayStudents(std::vector<Student> students);  // Pass by value to avoid modifying original

int main() {
    std::vector<Student> students;
    loadStudentsFromFile(students);

    int choice;
    do {
        std::cout << "\nStudent Record Management System\n";
        std::cout << "1. Add New Student Record\n";
        std::cout << "2. View All Student Records\n";
        std::cout << "3. View Specific Student Details\n";
        std::cout << "4. Update Student Information\n";
        std::cout << "5. Delete Student Record\n";
        std::cout << "6. Search Students\n";
        std::cout << "7. Sort and Display Students\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addNewStudent(students);
                break;
            case 2:
                viewAllStudents(students);
                break;
            case 3:
                viewStudentByRollNumber(students);
                break;
            case 4:
                updateStudentInfo(students);
                break;
            case 5:
                deleteStudentRecord(students);
                break;
            case 6:
                searchStudents(students);
                break;
            case 7:
                sortAndDisplayStudents(students);
                break;
            case 0:
                saveStudentsToFile(students);
                std::cout << "Exiting program. Data saved.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

// Function to load students from file
void loadStudentsFromFile(std::vector<Student>& students) {
    // TODO: Implement loading from "students.txt"
    // Open file, read lines, parse into Student structs, add to vector
    // Handle file not existing gracefully
    // Assigned to Team Member 1
}

// Function to save students to file
void saveStudentsToFile(const std::vector<Student>& students) {
    // TODO: Implement saving to "students.txt"
    // Open file, write each student's data in a formatted way (e.g., comma-separated)
    // Assigned to Team Member 1
}

// Function to add new student
void addNewStudent(std::vector<Student>& students) {
    // TODO: Implement adding a new student
    // Input name, roll number, department, GPA, contact
    // Validate unique roll number by checking existing students
    // Add to vector if valid
    // Assigned to Team Member 1
}

// Function to view all students in tabular form
void viewAllStudents(const std::vector<Student>& students) {
    // TODO: Implement displaying all records in a table
    // Use std::setw for alignment
    // Columns: Name, Roll Number, Department, GPA, Contact
    // Assigned to Team Member 2
}

// Function to view specific student by roll number
void viewStudentByRollNumber(const std::vector<Student>& students) {
    // TODO: Implement viewing a specific student
    // Ask for roll number, find and display details if found
    // Assigned to Team Member 2
}

// Function to update student info
void updateStudentInfo(std::vector<Student>& students) {
    // TODO: Implement updating a student's data
    // Ask for roll number, find student, then allow editing GPA, contact, etc.
    // Assigned to Team Member 1
}

// Function to delete student record
void deleteStudentRecord(std::vector<Student>& students) {
    // TODO: Implement deleting by roll number
    // Find and remove from vector
    // Assigned to Team Member 2
}

// Function to search students by name or department
void searchStudents(const std::vector<Student>& students) {
    // TODO: Implement search
    // Ask for search type (name or department), then query string
    // Display matching students in table
    // Assigned to Team Member 1
}

// Function to sort and display students
void sortAndDisplayStudents(std::vector<Student> students) {
    // TODO: Implement sorting
    // Ask for sort by (GPA or Roll Number)
    // Use std::sort with lambda comparator
    // Then display sorted list in table
    // Note: Passing by value to sort without modifying original
    // Assigned to Team Member 2
}