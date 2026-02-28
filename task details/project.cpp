#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int MAX_TASKS = 100;

// Function to save tasks to file
void saveToFile(string tasks[], string descriptions[], bool completed[], int taskCount) {
    ofstream outFile("tasks_detail.txt");
    
    if (outFile.is_open()) {
        for (int i = 0; i < taskCount; i++) {
            outFile << "Task " << (i + 1) << ":" << endl;
            outFile << "Title: " << tasks[i] << endl;
            outFile << "Description: " << descriptions[i] << endl;
            outFile << "Status: " << (completed[i] ? "Completed" : "Pending") << endl;
            outFile << endl;
        }
        outFile.close();
        cout << "Tasks saved to file successfully!" << endl;
    } else {
        cout << "Error: Unable to open file for writing!" << endl;
    }
}

// Function to load tasks from file
void loadFromFile(string tasks[], string descriptions[], bool completed[], int &taskCount) {
    ifstream inFile("tasks_detail.txt");
    
    if (inFile.is_open()) {
        string line;
        taskCount = 0;
        
        while (getline(inFile, line) && taskCount < MAX_TASKS) {
            // Skip "Task X:" line
            if (line.find("Task ") != string::npos) {
                // Read Title
                if (getline(inFile, line)) {
                    tasks[taskCount] = line.substr(7); // Skip "Title: "
                }
                // Read Description
                if (getline(inFile, line)) {
                    descriptions[taskCount] = line.substr(13); // Skip "Description: "
                }
                // Read Status
                if (getline(inFile, line)) {
                    completed[taskCount] = (line.find("Completed") != string::npos);
                }
                taskCount++;
                getline(inFile, line); // Skip empty line
            }
        }
        inFile.close();
        cout << "Tasks loaded from file successfully! (" << taskCount << " tasks loaded)" << endl;
    } else {
        cout << "No previous tasks found. Starting fresh." << endl;
    }
}

// Function to display menu
void displayMenu() {
    cout << "\n*** To-Do List Menu ***" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Complete Task" << endl;
    cout << "4. Delete Task" << endl;
    cout << "5. Save Tasks to File" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to add a task
void addTask(string tasks[], string descriptions[], bool completed[], int &taskCount) {
    if (taskCount < MAX_TASKS) {
        cout << "Enter task title: ";
        getline(cin, tasks[taskCount]);
        cout << "Enter task description: ";
        getline(cin, descriptions[taskCount]);
        completed[taskCount] = false;
        taskCount++;
        cout << "Task added: " << tasks[taskCount - 1] << endl;
        
        // Auto-save after adding task
        saveToFile(tasks, descriptions, completed, taskCount);
    } else {
        cout << "Task limit reached!" << endl;
    }
}

// Function to view all tasks
void viewTasks(string tasks[], string descriptions[], bool completed[], int taskCount) {
    if (taskCount == 0) {
        cout << "No tasks available." << endl;
    } else {
        cout << "\n=== Your Tasks ===" << endl;
        for (int i = 0; i < taskCount; i++) {
            cout << "\nTask " << (i + 1) << ":" << endl;
            cout << "Title: " << tasks[i] << endl;
            cout << "Description: " << descriptions[i] << endl;
            cout << "Status: " << (completed[i] ? "Completed" : "Pending") << endl;
        }
    }
}

// Function to mark a task as completed
void completeTask(string tasks[], string descriptions[], bool completed[], int taskCount) {
    cout << "Enter task number to complete: ";
    int completeTaskNum;
    cin >> completeTaskNum;
    
    if (completeTaskNum < 1 || completeTaskNum > taskCount) {
        cout << "Invalid task number." << endl;
    } else {
        completed[completeTaskNum - 1] = true;
        cout << "Task marked as completed: " << tasks[completeTaskNum - 1] << endl;
        
        // Auto-save after completing task
        saveToFile(tasks, descriptions, completed, taskCount);
    }
}

// Function to delete a task
void deleteTask(string tasks[], string descriptions[], bool completed[], int &taskCount) {
    cout << "Enter task number to delete: ";
    int deleteTaskNum;
    cin >> deleteTaskNum;
    
    if (deleteTaskNum < 1 || deleteTaskNum > taskCount) {
        cout << "Invalid task number." << endl;
    } else {
        cout << "Task deleted: " << tasks[deleteTaskNum - 1] << endl;
        // Shift remaining tasks to fill the gap
        for (int i = deleteTaskNum - 1; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
            descriptions[i] = descriptions[i + 1];
            completed[i] = completed[i + 1];
        }
        taskCount--;
        
        // Auto-save after deleting task
        saveToFile(tasks, descriptions, completed, taskCount);
    }
}

int main() {
    string tasks[MAX_TASKS];
    string descriptions[MAX_TASKS];
    bool completed[MAX_TASKS] = {false};
    int taskCount = 0;
    int choice;

    // Load existing tasks from file on startup
    loadFromFile(tasks, descriptions, completed, taskCount);

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear the newline from the input buffer

        switch (choice) {
            case 1:
                addTask(tasks, descriptions, completed, taskCount);
                break;

            case 2:
                viewTasks(tasks, descriptions, completed, taskCount);
                break;

            case 3:
                completeTask(tasks, descriptions, completed, taskCount);
                break;

            case 4:
                deleteTask(tasks, descriptions, completed, taskCount);
                break;

            case 5:
                saveToFile(tasks, descriptions, completed, taskCount);
                break;

            case 6:
                cout << "Exiting the program." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}