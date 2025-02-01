# ToDoList - C++ Task Manager

A simple **Task Manager** application built in C++ to help users organize their tasks by category, priority, and due date. This project uses a **hash map** to store and manage tasks efficiently.

---

## Features
- **Add Tasks**: Add tasks with a title, description, priority, due date, and category.
- **Remove Tasks**: Delete tasks by title and category.
- **Edit Tasks**: Update task details like description, priority, and due date.
- **View Tasks**:
  - Display tasks by category.
  - View all tasks sorted by due date.
- **Save and Load**: Save tasks to a file and load them when the program starts.

---

## Categories
Tasks can be organized into the following categories:
1. Studying
2. Kitchen
3. Work
4. Fitness
5. Hobbies

---

## How to Use
1. **Add a Task**:
   - Choose a category, enter the task details (title, description, priority, due date), and save it.
2. **Remove a Task**:
   - Select a category and enter the title of the task you want to remove.
3. **Edit a Task**:
   - Select a category and enter the title of the task you want to edit. Update the details as needed.
4. **View Tasks**:
   - View tasks by category or see all tasks sorted by due date.
5. **Save and Exit**:
   - Save all tasks to a file and exit the program.

---

## Code Structure
- **CHash.h**: Contains the `Task`, `Node`, and `HashMap` class definitions.
- **CHash.cpp**: Implements the `HashMap` class methods.
- **DSP.cpp**: Contains the main program logic and user interface.

---

## How to Run the Program
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/ToDoList-CPP.git
