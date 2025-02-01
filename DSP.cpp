#include "CHash.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Helper function to display the menu
void displayMenu() {
    cout << "\nTask Manager Menu:\n";
    cout << "1. Add a Task\n";
    cout << "2. Remove a Task\n";
    cout << "3. Edit a Task\n";
    cout << "4. Display Tasks by Category\n";
    cout << "5. Display All Tasks Sorted by Due Date\n";
    cout << "6. Save and Exit\n";
    cout << "Enter your choice: ";
}

// Helper function to choose a category
Category chooseCategory() {
    cout << "\nChoose a Category:\n";
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        cout << i + 1 << ". " << categoryNames[i] << "\n";
    }
    int choice;
    cin >> choice;
    return static_cast<Category>(choice - 1);
}

// Helper function to parse a date string in "YYYY-MM-DD" format
bool parseDate(const string& dateStr, struct tm& date) {
    if (dateStr.length() != 10 || dateStr[4] != '-' || dateStr[7] != '-') {
        return false;
    }

    date.tm_year = stoi(dateStr.substr(0, 4)) - 1900;
    date.tm_mon = stoi(dateStr.substr(5, 2)) - 1;
    date.tm_mday = stoi(dateStr.substr(8, 2));
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;

    return true;
}

// Add a new task
void addTask(HashMap& taskMap) {
    cin.ignore(); // Clear input buffer
    cout << "\nAdding a New Task\n";

    cout << "Enter Task Title: ";
    string title;
    getline(cin, title);

    cout << "Enter Task Description: ";
    string description;
    getline(cin, description);

    cout << "Enter Task Priority (1 = Low, 10 = High): ";
    int priority;
    cin >> priority;

    cout << "Enter Task Due Date (YYYY-MM-DD): ";
    string dateInput;
    cin >> dateInput;

    struct tm dueDateStruct = {};
    if (!parseDate(dateInput, dueDateStruct)) {
        cout << "Invalid date format. Please use YYYY-MM-DD.\n";
        return;
    }

    time_t dueDate = mktime(&dueDateStruct);
    Task task(title, description, priority, false, dueDate);
    Category category = chooseCategory();

    taskMap.insert(category, task);
    cout << "Task added successfully!\n";
}

// Remove a task
void removeTask(HashMap& taskMap) {
    cin.ignore(); // Clear input buffer
    cout << "\nRemoving a Task\n";

    Category category = chooseCategory();
    cout << "Enter Task Title to Remove: ";
    string title;
    getline(cin, title);

    Node*& head = taskMap.getTasks(category);
    Node* current = head;
    Node* prev = nullptr;

    while (current) {
        if (current->task.title == title) {
            if (prev) {
                prev->next = current->next; // Bypass the current node
            }
            else {
                head = current->next; // Update head if removing the first node
            }
            delete current; // Free the memory
            cout << "Task \"" << title << "\" removed successfully!\n";
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Task not found in the selected category.\n";
}

// Edit an existing task
void editTask(HashMap& taskMap) {
    cin.ignore();
    cout << "\nEditing a Task\n";

    Category category = chooseCategory();
    cout << "Enter Task Title to Edit: ";
    string title;
    getline(cin, title);

    Node* current = taskMap.getTasks(category);
    while (current) {
        if (current->task.title == title) {
            cout << "Editing Task: " << current->task.title << "\n";

            cout << "Enter New Description: ";
            string newDescription;
            getline(cin, newDescription);

            cout << "Enter New Priority (1 = Low, 10 = High): ";
            int newPriority;
            cin >> newPriority;

            cout << "Enter New Due Date (YYYY-MM-DD): ";
            string dateInput;
            cin >> dateInput;

            struct tm dueDateStruct = {};
            if (!parseDate(dateInput, dueDateStruct)) {
                cout << "Invalid date format. Please use YYYY-MM-DD.\n";
                return;
            }

            time_t newDueDate = mktime(&dueDateStruct);

            // Update task
            current->task.description = newDescription;
            current->task.priority = newPriority;
            current->task.dueDate = newDueDate;

            cout << "Task updated successfully!\n";
            return;
        }
        current = current->next;
    }

    cout << "Task not found in the selected category.\n";
}

// Display tasks by category
void displayByCategory(HashMap& taskMap) {
    Category category = chooseCategory();
    taskMap.printTasks(category);
}

// Main program
int main() {
    HashMap taskMap;
    const string filename = "tasks.txt";

    // Load tasks from file
    taskMap.loadFromFile(filename);

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addTask(taskMap);
            break;
        case 2:
            removeTask(taskMap);
            break;
        case 3:
            editTask(taskMap);
            break;
        case 4:
            displayByCategory(taskMap);
            break;
        case 5:
            taskMap.printTasksSortedByDueDate();
            break;
        case 6:
            cout << "Saving tasks and exiting. Goodbye!\n";
            taskMap.saveToFile(filename);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
