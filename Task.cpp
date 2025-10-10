#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cctype>  // For toupper/tolower if needed

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
void sortAndDisplayStudents(std::vector<Student> students);

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
        std::cin.ignore();  // Clear newline after cin >> choice

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
    std::ifstream file("students.txt");
    if (!file.is_open()) {
        std::cout << "No existing file found. Starting with empty records.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        Student student;
        std::string token;

        // Parse name (may contain commas, but assuming no commas in name for simplicity; use quotes if needed)
        std::getline(ss, student.name, ',');
        // Trim quotes if any
        if (!student.name.empty() && student.name.front() == '"') student.name.erase(0, 1);
        if (!student.name.empty() && student.name.back() == '"') student.name.pop_back();

        // Roll number
        ss >> student.rollNumber;
        ss.ignore();  // Ignore comma

        // Department
        std::getline(ss, student.department, ',');
        if (!student.department.empty() && student.department.front() == '"') student.department.erase(0, 1);
        if (!student.department.empty() && student.department.back() == '"') student.department.pop_back();

        // GPA
        ss >> student.gpa;
        ss.ignore();  // Ignore comma

        // Contact info
        std::getline(ss, student.contactInfo);
        if (!student.contactInfo.empty() && student.contactInfo.front() == '"') student.contactInfo.erase(0, 1);
        if (!student.contactInfo.empty() && student.contactInfo.back() == '"') student.contactInfo.pop_back();

        students.push_back(student);
    }
    file.close();
    std::cout << "Loaded " << students.size() << " students from file.\n";
}

// Function to save students to file
void saveStudentsToFile(const std::vector<Student>& students) {
    std::ofstream file("students.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file for writing.\n";
        return;
    }

    for (const auto& student : students) {
        file << "\"" << student.name << "\"," 
             << student.rollNumber << ","
             << "\"" << student.department << "\"," 
             << student.gpa << ","
             << "\"" << student.contactInfo << "\"\n";
    }
    file.close();
    std::cout << "Saved " << students.size() << " students to file.\n";
}

// Function to add new student
void addNewStudent(std::vector<Student>& students) {
    Student newStudent;
    std::cout << "Enter student name: ";
    std::getline(std::cin, newStudent.name);

    std::cout << "Enter roll number: ";
    std::cin >> newStudent.rollNumber;
    std::cin.ignore();  // Clear newline

    // Validate unique roll number
    for (const auto& student : students) {
        if (student.rollNumber == newStudent.rollNumber) {
            std::cout << "Roll number already exists. Please use a unique roll number.\n";
            return;
        }
    }

    std::cout << "Enter department: ";
    std::getline(std::cin, newStudent.department);

    std::cout << "Enter GPA (0.0 to 4.0): ";
    std::cin >> newStudent.gpa;
    std::cin.ignore();

    std::cout << "Enter contact info: ";
    std::getline(std::cin, newStudent.contactInfo);

    students.push_back(newStudent);
    std::cout << "Student record added successfully.\n";
}

// Function to view all students in tabular form
void viewAllStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No student records found.\n";
        return;
    }

    std::cout << std::left << std::setw(20) << "Name"
              << std::setw(12) << "Roll Number"
              << std::setw(15) << "Department"
              << std::setw(8) << "GPA"
              << std::setw(20) << "Contact Info" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    for (const auto& student : students) {
        std::cout << std::left << std::setw(20) << student.name
                  << std::setw(12) << student.rollNumber
                  << std::setw(15) << student.department
                  << std::setw(8) << std::fixed << std::setprecision(2) << student.gpa
                  << std::setw(20) << student.contactInfo << std::endl;
    }
}

// Function to view specific student by roll number
void viewStudentByRollNumber(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No student records found.\n";
        return;
    }

    int roll;
    std::cout << "Enter roll number: ";
    std::cin >> roll;
    std::cin.ignore();

    bool found = false;
    for (const auto& student : students) {
        if (student.rollNumber == roll) {
            std::cout << "\nStudent Details:\n";
            std::cout << "Name: " << student.name << std::endl;
            std::cout << "Roll Number: " << student.rollNumber << std::endl;
            std::cout << "Department: " << student.department << std::endl;
            std::cout << "GPA: " << std::fixed << std::setprecision(2) << student.gpa << std::endl;
            std::cout << "Contact Info: " << student.contactInfo << std::endl;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Student with roll number " << roll << " not found.\n";
    }
}

// Function to update student info
void updateStudentInfo(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No student records found.\n";
        return;
    }

    int roll;
    std::cout << "Enter roll number to update: ";
    std::cin >> roll;
    std::cin.ignore();

    auto it = students.begin();
    for (; it != students.end(); ++it) {
        if (it->rollNumber == roll) {
            break;
        }
    }
    if (it == students.end()) {
        std::cout << "Student with roll number " << roll << " not found.\n";
        return;
    }

    std::cout << "Current details:\n";
    std::cout << "Name: " << it->name << std::endl;
    std::cout << "Department: " << it->department << std::endl;
    std::cout << "GPA: " << it->gpa << std::endl;
    std::cout << "Contact: " << it->contactInfo << std::endl;

    std::cout << "\nEnter new GPA (or press Enter to keep current): ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) {
        it->gpa = std::stod(input);
    }

    std::cout << "Enter new contact info (or press Enter to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        it->contactInfo = input;
    }

    // Optionally allow updating name or department, but for simplicity, only GPA and contact
    std::cout << "Student updated successfully.\n";
}

// Function to delete student record
void deleteStudentRecord(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No student records found.\n";
        return;
    }

    int roll;
    std::cout << "Enter roll number to delete: ";
    std::cin >> roll;
    std::cin.ignore();

    auto it = students.begin();
    for (; it != students.end(); ++it) {
        if (it->rollNumber == roll) {
            std::cout << "Deleting student: " << it->name << " (Roll: " << roll << "). Confirm? (y/n): ";
            char confirm;
            std::cin >> confirm;
            std::cin.ignore();
            if (confirm == 'y' || confirm == 'Y') {
                students.erase(it);
                std::cout << "Student record deleted successfully.\n";
            } else {
                std::cout << "Deletion cancelled.\n";
            }
            return;
        }
    }
    std::cout << "Student with roll number " << roll << " not found.\n";
}

// Function to search students by name or department
void searchStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No student records found.\n";
        return;
    }

    int searchType;
    std::cout << "Search by: 1. Name  2. Department: ";
    std::cin >> searchType;
    std::cin.ignore();

    std::string query;
    std::cout << "Enter search query: ";
    std::getline(std::cin, query);

    std::vector<Student> results;
    for (const auto& student : students) {
        bool match = false;
        if (searchType == 1) {
            if (student.name.find(query) != std::string::npos) {
                match = true;
            }
        } else if (searchType == 2) {
            if (student.department.find(query) != std::string::npos) {
                match = true;
            }
        }
        if (match) {
            results.push_back(student);
        }
    }

    if (results.empty()) {
        std::cout << "No matching students found.\n";
        return;
    }

    std::cout << "\nSearch Results:\n";
    std::cout << std::left << std::setw(20) << "Name"
              << std::setw(12) << "Roll Number"
              << std::setw(15) << "Department"
              << std::setw(8) << "GPA"
              << std::setw(20) << "Contact Info" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    for (const auto& student : results) {
        std::cout << std::left << std::setw(20) << student.name
                  << std::setw(12) << student.rollNumber
                  << std::setw(15) << student.department
                  << std::setw(8) << std::fixed << std::setprecision(2) << student.gpa
                  << std::setw(20) << student.contactInfo << std::endl;
    }
}

// Function to sort and display students
void sortAndDisplayStudents(std::vector<Student> students) {
    if (students.empty()) {
        std::cout << "No student records found.\n";
        return;
    }

    int sortType;
    std::cout << "Sort by: 1. GPA (descending)  2. Roll Number (ascending): ";
    std::cin >> sortType;
    std::cin.ignore();

    if (sortType == 1) {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.gpa > b.gpa;  // Descending GPA
        });
    } else if (sortType == 2) {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.rollNumber < b.rollNumber;  // Ascending Roll Number
        });
    } else {
        std::cout << "Invalid sort type.\n";
        return;
    }

    std::cout << "\nSorted Student Records:\n";
    std::cout << std::left << std::setw(20) << "Name"
              << std::setw(12) << "Roll Number"
              << std::setw(15) << "Department"
              << std::setw(8) << "GPA"
              << std::setw(20) << "Contact Info" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    for (const auto& student : students) {
        std::cout << std::left << std::setw(20) << student.name
                  << std::setw(12) << student.rollNumber
                  << std::setw(15) << student.department
                  << std::setw(8) << std::fixed << std::setprecision(2) << student.gpa
                  << std::setw(20) << student.contactInfo << std::endl;
    }
}