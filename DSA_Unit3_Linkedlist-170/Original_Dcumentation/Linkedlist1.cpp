#include <iostream>
#include <string>
using namespace std;

struct Student
{
    int rollNo;
    string name;
    string branch;
    float marks;
    Student* next;
};

Student* head = NULL;

// Add Student
void addStudent()
{
    Student* newStudent = new Student;

    cout << "\nEnter Roll No: ";
    cin >> newStudent->rollNo;

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, newStudent->name);

    cout << "Enter Branch: ";
    getline(cin, newStudent->branch);

    cout << "Enter Marks: ";
    cin >> newStudent->marks;

    newStudent->next = NULL;

    if (head == NULL)
    {
        head = newStudent;
    }
    else
    {
        Student* temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newStudent;
    }

    cout << "\nStudent added successfully!\n";
}


// Display Students
void displayStudents()
{
    if (head == NULL)
    {
        cout << "\nNo student records found.\n";
        return;
    }

    Student* temp = head;

    cout << "\n----- Student Records -----\n";

    while (temp != NULL)
    {
        cout << "\nRoll No : " << temp->rollNo;
        cout << "\nName    : " << temp->name;
        cout << "\nBranch  : " << temp->branch;
        cout << "\nMarks   : " << temp->marks;
        cout << "\n--------------------------";

        temp = temp->next;
    }
}


// Search Student
void searchStudent()
{
    int roll;
    cout << "\nEnter Roll No to search: ";
    cin >> roll;

    Student* temp = head;

    while (temp != NULL)
    {
        if (temp->rollNo == roll)
        {
            cout << "\nStudent Found!";
            cout << "\nName   : " << temp->name;
            cout << "\nBranch : " << temp->branch;
            cout << "\nMarks  : " << temp->marks << endl;

            return;
        }

        temp = temp->next;
    }

    cout << "\nStudent not found.\n";
}


// Update Student
void updateStudent()
{
    int roll;
    cout << "\nEnter Roll No to update: ";
    cin >> roll;

    Student* temp = head;

    while (temp != NULL)
    {
        if (temp->rollNo == roll)
        {
            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, temp->name);

            cout << "Enter New Branch: ";
            getline(cin, temp->branch);

            cout << "Enter New Marks: ";
            cin >> temp->marks;

            cout << "\nStudent record updated successfully!\n";
            return;
        }

        temp = temp->next;
    }

    cout << "\nStudent not found.\n";
}


// Delete Student
void deleteStudent()
{
    int roll;

    cout << "\nEnter Roll No to delete: ";
    cin >> roll;

    Student* temp = head;
    Student* previous = NULL;

    while (temp != NULL)
    {
        if (temp->rollNo == roll)
        {
            if (previous == NULL)
            {
                head = temp->next;
            }
            else
            {
                previous->next = temp->next;
            }

            delete temp;

            cout << "\nStudent deleted successfully!\n";
            return;
        }

        previous = temp;
        temp = temp->next;
    }

    cout << "\nStudent not found.\n";
}


// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n\n===== STUDENT RECORD MANAGEMENT =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nThank you!";
                break;

            default:
                cout << "\nInvalid choice!";
        }

    } while (choice != 6);

    return 0;
}