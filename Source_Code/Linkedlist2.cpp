#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Student Node
struct Student
{
    int rollNo;
    string name;
    string branch;
    float marks;
    Student* next;
    Student* prev;
};

// Circular List Node
struct CircularStudent
{
    int rollNo;
    string name;
    CircularStudent* next;
};

// List Heads
Student* singlyHead = NULL;
Student* doublyHead = NULL;
CircularStudent* circularHead = NULL;

// Find student in singly linked list
Student* findStudent(int roll)
{
    Student* temp = singlyHead;

    while (temp != NULL)
    {
        if (temp->rollNo == roll)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

// 1. Add Student (Singly Linked List)
void addStudent()
{
    int roll;
    cout << "Enter Roll Number: ";
    cin >> roll;

    if (findStudent(roll) != NULL)
    {
        cout << "Roll number already exists!\n";
        return;
    }

    Student* n = new Student;

    n->rollNo = roll;

    cout << "Enter Name: ";
    getline(cin >> ws, n->name);

    cout << "Enter Branch: ";
    getline(cin >> ws, n->branch);

    cout << "Enter Marks (out of 100): ";
    cin >> n->marks;

    if (n->marks < 0 || n->marks > 100)
    {
        cout << "Invalid marks!\n";
        delete n;
        return;
    }

    n->next = NULL;
    n->prev = NULL;

    if (singlyHead == NULL)
        singlyHead = n;
    else
    {
        Student* temp = singlyHead;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = n;
    }

    cout << "Student added successfully!\n";
}

// 2. Display Students
void displayStudents()
{
    if (singlyHead == NULL)
    {
        cout << "No student records found.\n";
        return;
    }

    Student* temp = singlyHead;

    cout << "\n--- STUDENT RECORDS ---\n";

    while (temp != NULL)
    {
        cout << "\nRoll Number: " << temp->rollNo;
        cout << "\nName: " << temp->name;
        cout << "\nBranch: " << temp->branch;
        cout << "\nMarks: " << temp->marks << "\n";

        temp = temp->next;
    }
}

// 3. Search Student
void searchStudent()
{
    int roll;

    cout << "Enter Roll Number to Search: ";
    cin >> roll;

    Student* temp = findStudent(roll);

    if (temp == NULL)
        cout << "Student not found.\n";
    else
    {
        cout << "Name: " << temp->name << "\n";
        cout << "Branch: " << temp->branch << "\n";
        cout << "Marks: " << temp->marks << "\n";
    }
}

// 4. Update Student
void updateStudent()
{
    int roll;

    cout << "Enter Roll Number to Update: ";
    cin >> roll;

    Student* temp = findStudent(roll);

    if (temp == NULL)
    {
        cout << "Student not found.\n";
        return;
    }

    cout << "Enter New Name: ";
    getline(cin >> ws, temp->name);

    cout << "Enter New Branch: ";
    getline(cin >> ws, temp->branch);

    cout << "Enter New Marks: ";
    cin >> temp->marks;

    if (temp->marks < 0 || temp->marks > 100)
    {
        cout << "Invalid marks! Please update again.\n";
        return;
    }

    cout << "Record updated successfully!\n";
}

// 5. Delete Student
void deleteStudent()
{
    int roll;

    cout << "Enter Roll Number to Delete: ";
    cin >> roll;

    Student* temp = singlyHead;
    Student* previous = NULL;

    while (temp != NULL && temp->rollNo != roll)
    {
        previous = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "Student not found.\n";
        return;
    }

    if (previous == NULL)
        singlyHead = temp->next;
    else
        previous->next = temp->next;

    delete temp;

    cout << "Student deleted successfully!\n";
}

// 6. Build Doubly Linked List
void buildDoublyList()
{
    Student* old = doublyHead;

    while (old != NULL)
    {
        Student* nextNode = old->next;
        delete old;
        old = nextNode;
    }

    doublyHead = NULL;

    Student* source = singlyHead;

    while (source != NULL)
    {
        Student* n = new Student;

        n->rollNo = source->rollNo;
        n->name = source->name;
        n->branch = source->branch;
        n->marks = source->marks;

        n->next = NULL;
        n->prev = NULL;

        if (doublyHead == NULL)
            doublyHead = n;
        else
        {
            Student* temp = doublyHead;

            while (temp->next != NULL)
                temp = temp->next;

            temp->next = n;
            n->prev = temp;
        }

        source = source->next;
    }
}

// 7. Navigate Forward and Backward
void navigateStudents()
{
    buildDoublyList();

    if (doublyHead == NULL)
    {
        cout << "No student records found.\n";
        return;
    }

    Student* current = doublyHead;
    char choice;

    do
    {
        cout << "\nRoll Number: " << current->rollNo;
        cout << "\nName: " << current->name;
        cout << "\nBranch: " << current->branch;
        cout << "\nMarks: " << current->marks;

        cout << "\n\nN = Next, P = Previous, Q = Quit: ";
        cin >> choice;

        if (choice == 'N' || choice == 'n')
        {
            if (current->next != NULL)
                current = current->next;
            else
                cout << "This is the last student.\n";
        }
        else if (choice == 'P' || choice == 'p')
        {
            if (current->prev != NULL)
                current = current->prev;
            else
                cout << "This is the first student.\n";
        }

    } while (choice != 'Q' && choice != 'q');
}

// 8. Build Circular Linked List
void buildCircularList()
{
    CircularStudent* old = circularHead;

    if (old != NULL)
    {
        CircularStudent* temp = old->next;

        while (temp != old)
        {
            CircularStudent* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        delete old;
    }

    circularHead = NULL;

    Student* source = singlyHead;

    while (source != NULL)
    {
        CircularStudent* n = new CircularStudent;

        n->rollNo = source->rollNo;
        n->name = source->name;
        n->next = NULL;

        if (circularHead == NULL)
        {
            circularHead = n;
            n->next = n;
        }
        else
        {
            CircularStudent* temp = circularHead;

            while (temp->next != circularHead)
                temp = temp->next;

            temp->next = n;
            n->next = circularHead;
        }

        source = source->next;
    }
}

// 9. Student Rotation Scheduler
void rotationScheduler()
{
    buildCircularList();

    if (circularHead == NULL)
    {
        cout << "No students available.\n";
        return;
    }

    CircularStudent* current = circularHead;
    int turns;

    cout << "Enter number of student turns: ";
    cin >> turns;

    if (turns <= 0)
    {
        cout << "Enter a positive number.\n";
        return;
    }

    cout << "\n--- STUDENT ROTATION SCHEDULER ---\n";

    for (int i = 1; i <= turns; i++)
    {
        cout << "Turn " << i << ": "
             << current->name
             << " (Roll No: " << current->rollNo << ")\n";

        current = current->next;
    }
}

// 10. Performance Analysis
void performanceAnalysis()
{
    if (singlyHead == NULL)
    {
        cout << "No student records found.\n";
        return;
    }

    Student* temp = singlyHead;
    float total = 0;
    int count = 0;

    Student* topper = singlyHead;

    cout << "\n--- PERFORMANCE ANALYSIS ---\n";

    while (temp != NULL)
    {
        float percentage = temp->marks;

        cout << "\n" << temp->name
             << " | Percentage: " << percentage << "%";

        if (percentage >= 90)
            cout << " | Grade: A+";
        else if (percentage >= 75)
            cout << " | Grade: A";
        else if (percentage >= 60)
            cout << " | Grade: B";
        else if (percentage >= 40)
            cout << " | Grade: C";
        else
            cout << " | Grade: F";

        total += temp->marks;
        count++;

        if (temp->marks > topper->marks)
            topper = temp;

        temp = temp->next;
    }

    cout << "\n\nClass Average: "
         << total / count << "%";

    cout << "\nTopper: " << topper->name;
    cout << "\nHighest Marks: " << topper->marks << "\n";
}

// Compare Linked Lists with Complexity
void compareLists()
{
    cout << "\n===== LINKED LIST COMPARISON =====\n";

    cout << "\n1. SINGLY LINKED LIST";
    cout << "\nTraversal: Forward only";
    cout << "\nInsert at Beginning: O(1)";
    cout << "\nSearch: O(n)";
    cout << "\nDelete by Value: O(n)";
    cout << "\nSpace Complexity: O(n)";

    cout << "\n\n2. DOUBLY LINKED LIST";
    cout << "\nTraversal: Forward and Backward";
    cout << "\nInsert at Beginning: O(1)";
    cout << "\nSearch: O(n)";
    cout << "\nDelete by Value: O(n)";
    cout << "\nSpace Complexity: O(n)";
    cout << "\nExtra Memory: Previous Pointer";

    cout << "\n\n3. CIRCULAR LINKED LIST";
    cout << "\nTraversal: Circular";
    cout << "\nInsert at Beginning: O(1)*";
    cout << "\nSearch: O(n)";
    cout << "\nDelete by Value: O(n)";
    cout << "\nSpace Complexity: O(n)";

    cout << "\n\n===== COMPLEXITY COMPARISON =====";

    cout << "\nOperation       Singly   Doubly   Circular";
    cout << "\nSearch          O(n)     O(n)     O(n)";
    cout << "\nInsert Begin    O(1)     O(1)     O(1)*";
    cout << "\nDelete by Value O(n)     O(n)     O(n)";

    cout << "\n\nNote:";
    cout << "\nO(1) = Constant Time";
    cout << "\nO(n) = Linear Time";
    cout << "\nO(n) Space = Memory for n nodes";
    cout << "\n*Circular insertion assumes a tail pointer.\n";
}


// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n===== SMART STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Previous/Next Navigation (Doubly)\n";
        cout << "7. Student Rotation Scheduler (Circular)\n";
        cout << "8. Performance Analysis\n";
        cout << "9. Compare Linked Lists\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";

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
                navigateStudents();
                break;

            case 7:
                rotationScheduler();
                break;

            case 8:
                performanceAnalysis();
                break;

            case 9:
                compareLists();
                break;

            case 10:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 10);

    return 0;
}