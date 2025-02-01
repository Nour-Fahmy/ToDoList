#pragma once

#include <string>
#include <ctime>
#include <iostream>

struct Task {
    std::string title;
    std::string description;
    int priority;       
    bool isCompleted;   
    time_t dueDate;     

    Task(std::string t, std::string desc, int prio, bool completed, time_t due)
        : title(t), description(desc), priority(prio), isCompleted(completed), dueDate(due) {}
};

struct Node {
    Task task;
    Node* next;

    Node(Task t) : task(t), next(nullptr) {}
};

enum Category {
    STUDYING,
    KITCHEN,
    WORK,
    FITNESS,
    HOBBIES,
    CATEGORY_COUNT 
};

const std::string categoryNames[] = {
    "Studying",
    "Kitchen",
    "Work",
    "Fitness",
    "Hobbies"
};

class HashMap {
private:
    Node** table;
    int tableSize;

    int hashFunction(Category category) {
        return static_cast<int>(category) % tableSize; 
    }

    std::string formatDate(time_t time) {
        char buffer[11]; 
        struct tm timeInfo;
        localtime_s(&timeInfo, &time); 
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeInfo); 
        return std::string(buffer);
    }


public:
    HashMap();
    void insert(Category category, Task task);
    Node*& getTasks(Category category);
    void printTasks(Category category);
    void printTasksSortedByDueDate();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    ~HashMap();
};


