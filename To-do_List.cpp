#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Task {
    string description;
    bool completed;
    string dueDate;
    int priority; // 1 = Low, 2 = Medium, 3 = High
};

// File waar de tasks gesaved worden
const string FILE_NAME = "tasks.txt";

// Functie om de files te saven
void saveTasks(const vector<Task>& tasks) {
    ofstream file(FILE_NAME);
    for (const auto& task : tasks) {
        file << task.description << "|" << task.completed << "|" << task.dueDate << "|" << task.priority << endl;
    }
    file.close();
}

// Functie om de task te loaden naar de files
void loadTasks(vector<Task>& tasks) {
    ifstream file(FILE_NAME);
    if (!file) return;

    Task task;
    string completedStr;
    while (getline(file, task.description, '|')) {
        getline(file, completedStr, '|');
        getline(file, task.dueDate, '|');
        file >> task.priority;
        file.ignore(); // Ignore newline
        task.completed = (completedStr == "1");
        tasks.push_back(task);
    }
    file.close();
}

// functie om nieuwe task toetevoegen
void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, newTask.description);
    cout << "Enter due date (YYYY-MM-DD): ";
    cin >> newTask.dueDate;
    cout << "Set priority (1 = Low, 2 = Medium, 3 = High): ";
    cin >> newTask.priority;
    newTask.completed = false;
    tasks.push_back(newTask);
    saveTasks(tasks);
    cout << "Task added successfully!\n";
}

// Functie om task te deleten
void removeTask(vector<Task>& tasks) {
    int index;
    cout << "Enter task number to remove: ";
    cin >> index;
    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        saveTasks(tasks);
        cout << "Task removed successfully!\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

// Functie om task als completed te markeren 
void completeTask(vector<Task>& tasks) {
    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;
    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
        saveTasks(tasks);
        cout << "Task marked as completed!\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

// Functie om de tasks te tonen
void displayTasks(const vector<Task>& tasks) {
    cout << "\n====== PENDING TASKS ======\n";
    int count = 0;
    for (size_t i = 0; i < tasks.size(); ++i) {
        if (!tasks[i].completed) {
            cout << i + 1 << ". " << tasks[i].description
                 << " [Due: " << tasks[i].dueDate << "] "
                 << "[Priority: " << tasks[i].priority << "]\n";
            count++;
        }
    }
    if (count == 0) cout << "No pending tasks.\n";

    cout << "\n====== COMPLETED TASKS ======\n";
    count = 0;
    for (size_t i = 0; i < tasks.size(); ++i) {
        if (tasks[i].completed) {
            cout << i + 1 << ". " << tasks[i].description
                 << " [Due: " << tasks[i].dueDate << "]\n";
            count++;
        }
    }
    if (count == 0) cout << "No completed tasks.\n";
}

// Functie om task prioriteit te toonen
void sortTasks(vector<Task>& tasks) {
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.priority > b.priority; // Higher priority first
    });
    saveTasks(tasks);
    cout << "Tasks sorted by priority!\n";
}

// Main menu function
void menu(vector<Task>& tasks) {
    int choice;
    do {
        cout << "\n===== TO-DO LIST MENU =====\n";
        cout << "1. Add Task\n2. Remove Task\n3. Mark Task as Completed\n";
        cout << "4. View Tasks\n5. Sort by Priority\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(tasks); break;
            case 2: removeTask(tasks); break;
            case 3: completeTask(tasks); break;
            case 4: displayTasks(tasks); break;
            case 5: sortTasks(tasks); break;
            case 6: cout << "Exiting... Your tasks are saved.\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 6);
}

int main() {
    vector<Task> tasks;
    loadTasks(tasks); // Load tasks at startup
    menu(tasks);
    return 0;
}