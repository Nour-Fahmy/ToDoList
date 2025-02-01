#include "CHash.h"
#include <fstream>
#include <iomanip>
#include <cstring>

HashMap::HashMap() {
    tableSize = CATEGORY_COUNT;
    table = new Node * [tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i] = nullptr;
    }
}

HashMap::~HashMap() {
   
    for (int i = 0; i < tableSize; i++) {
        Node* current = table[i]; 
        while (current) {
            Node* temp = current; 
            current = current->next; 
            delete temp; 
        }
    }
   
    delete[] table;
    table = nullptr;
}


void HashMap::insert(Category category, Task task) {
    int index = hashFunction(category);
    Node* newNode = new Node(task);
    newNode->next = table[index];
    table[index] = newNode;
}

Node*& HashMap::getTasks(Category category) {
    int index = hashFunction(category);
    return table[index];
}

void HashMap::printTasks(Category category) {
    int index = hashFunction(category);
    Node* current = table[index];
    std::cout << "Tasks for category: " << categoryNames[index] << "\n";
    while (current) {
        std::cout << "Title: " << current->task.title
            << ", Description: " << current->task.description
            << ", Priority: " << current->task.priority
            << ", Completed: " << (current->task.isCompleted ? "Yes" : "No")
            << ", Due Date: " << formatDate(current->task.dueDate) << "\n";
        current = current->next;
    }
    std::cout << std::endl;
}

void HashMap::printTasksSortedByDueDate() {
    struct CategorizedTask {
        std::string category;
        Task task;

        CategorizedTask() : category(""), task("", "", 0, false, 0) {}
        CategorizedTask(std::string cat, Task t) : category(cat), task(t) {}
    };

    int maxTasks = 0;
    for (int i = 0; i < tableSize; i++) {
        Node* current = table[i];
        while (current) {
            maxTasks++;
            current = current->next;
        }
    }

    CategorizedTask* taskList = new CategorizedTask[maxTasks];
    int taskCount = 0;

    for (int i = 0; i < tableSize; i++) {
        Node* current = table[i];
        while (current) {
            taskList[taskCount++] = CategorizedTask(categoryNames[i], current->task);
            current = current->next;
        }
    }

    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            if (taskList[j].task.dueDate > taskList[j + 1].task.dueDate) {
                CategorizedTask temp = taskList[j];
                taskList[j] = taskList[j + 1];
                taskList[j + 1] = temp;
            }
        }
    }

    std::cout << "Tasks Sorted by Due Date:\n";
    for (int i = 0; i < taskCount; i++) {
        std::cout << "Category: " << taskList[i].category << "\n"
            << "Title: " << taskList[i].task.title
            << ", Due Date: " << formatDate(taskList[i].task.dueDate) << "\n";
    }
    std::cout << std::endl;

    delete[] taskList;
}

void HashMap::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < tableSize; i++) {
        Node* current = table[i];
        if (current) {
            file << categoryNames[i] << ":\n";
            while (current) {
                file << current->task.title << ", "
                    << current->task.description << ", "
                    << current->task.priority << ", "
                    << current->task.isCompleted << ", "
                    << formatDate(current->task.dueDate) << "\n";
                current = current->next;
            }
            file << "\n";
        }
    }

    file.close();
}

void HashMap::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }

    std::string line;
    int currentCategory = -1;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line.find(":") != std::string::npos) {
            for (int i = 0; i < CATEGORY_COUNT; i++) {
                if (line.find(categoryNames[i]) != std::string::npos) {
                    currentCategory = i;
                    break;
                }
            }
        }
        else {
            size_t first = line.find(", ");
            size_t second = line.find(", ", first + 2);
            size_t third = line.find(", ", second + 2);
            size_t fourth = line.find(", ", third + 2);

            std::string title = line.substr(0, first);
            std::string description = line.substr(first + 2, second - first - 2);
            int priority = std::stoi(line.substr(second + 2, third - second - 2));
            bool isCompleted = std::stoi(line.substr(third + 2, fourth - third - 2));
        }
    }
}
