#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath> 

using namespace std;

// Represents a single task entry in the application
struct Task {
    string name;
    string description;
};

/**
 * Renders the task list in a formatted table.
 * Supports text wrapping for long task names and descriptions.
 */
void ShowTasks(const vector<Task>& tasks) {
    if (tasks.empty()) return;

    // Table Header
    cout << left << setw(5) << "ID" << " | " << left << setw(10) << "Name" << " | " << left << setw(30) << "Description" << endl;
    cout << "------------------------------------------------------------" << endl;

    const int nameWidth = 10;
    const int descWidth = 30;

    for (int i = 0; i < (int)tasks.size(); i++) {
        string name = tasks[i].name;
        string desc = tasks[i].description;

        // Calculate how many rows are needed based on the longest text string
        int lines = max((int)ceil((double)name.length() / nameWidth),
            (int)ceil((double)desc.length() / descWidth));

        for (int j = 0; j < lines; j++) {
            // Display task ID only on the first line of the wrap
            if (j == 0)
                cout << left << setw(5) << (to_string(i + 1) + "-");
            else
                cout << left << setw(5) << " ";

            // Substring logic to handle multi-line text wrapping
            cout << " | " << left << setw(nameWidth) << (j * nameWidth < (int)name.length() ? name.substr(j * nameWidth, nameWidth) : "")
                << " | " << left << setw(descWidth) << (j * descWidth < (int)desc.length() ? desc.substr(j * descWidth, descWidth) : "")
                << endl;
        }
    }
}

int main() {
    // Application state and constraints
    string taskname, taskDescription;
    int choice, numDelete;
    vector<Task> tasks;
    Task t;

    const int maxNameLength = 20;
    const int maxDescLength = 50;
    bool running = true;

    cout << "Hello, welcome to the To-Do application!\n";

    while (running) {
        cout << "\nEnter A Choice: \n"
            << "0-Exit\n1-ADD Task\n2-DELETE Task\n3-Show Task List\n4-Clear ALL Tasks\n5-Edit Task\n" << endl;

        cout << "Choice: ";
        cin >> choice;

        // Validation for non-integer inputs to prevent infinite loops
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a numeric choice.\n";
            continue;
        }

        cin.ignore(); // Clear newline buffer before using getline

        if (choice == 1) { // ADD TASK
            cout << "Enter The Task: ";
            getline(cin, taskname);

            if (taskname.length() > maxNameLength) {
                cout << "Validation Error: Task name exceeds " << maxNameLength << " characters.\n";
                continue;
            }

            cout << "Enter The Task Description: ";
            getline(cin, taskDescription);

            if (taskDescription.length() > maxDescLength) {
                cout << "Validation Error: Description exceeds " << maxDescLength << " characters.\n";
                continue;
            }

            t.name = taskname;
            t.description = taskDescription;
            tasks.push_back(t);
            ShowTasks(tasks);
        }
        else if (choice == 2) { // DELETE TASK
            if (tasks.empty()) {
                cout << "No tasks available to delete.\n";
                continue;
            }
            cout << "Enter Task ID to DELETE: ";
            cin >> numDelete;
            cin.ignore();

            // Validate if the ID exists within the vector range
            if (numDelete >= 1 && numDelete <= (int)tasks.size()) {
                string deletedName = tasks[numDelete - 1].name;
                tasks.erase(tasks.begin() + (numDelete - 1));
                cout << "Success: [" << deletedName << "] has been removed.\n";
            }
            else {
                cout << "Error: Task ID not found.\n";
            }
        }
        else if (choice == 3) { // VIEW TASKS
            if (tasks.empty()) {
                cout << "The task list is currently empty.\n";
            }
            ShowTasks(tasks);
        }
        else if (choice == 4) { // CLEAR ALL
            tasks.clear();
            cout << "Success: All tasks cleared.\n";
        }
        else if (choice == 5) { // EDIT TASK
            int numEdit;
            if (tasks.empty()) {
                cout << "No tasks available to edit.\n";
                continue;
            }

            cout << "Enter Task ID to EDIT: ";
            cin >> numEdit;
            cin.ignore();

            if (numEdit >= 1 && numEdit <= (int)tasks.size()) {
                string nameNew, descriptionNew;

                cout << "Enter New Name: ";
                getline(cin, nameNew);
                if (nameNew.length() > maxNameLength) {
                    cout << "Error: New name is too long.\n";
                    continue;
                }

                cout << "Enter New Description: ";
                getline(cin, descriptionNew);
                if (descriptionNew.length() > maxDescLength) {
                    cout << "Error: New description is too long.\n";
                    continue;
                }

                // Update the existing object in the vector
                tasks[numEdit - 1].name = nameNew;
                tasks[numEdit - 1].description = descriptionNew;

                cout << "Success: Task " << numEdit << " updated.\n";
                ShowTasks(tasks);
            }
            else {
                cout << "Error: Invalid Task ID.\n";
            }
        }
        else if (choice == 0) { // EXIT
            cout << "Exiting application...\n";
            running = false;
        }
        else {
            cout << "Invalid choice! Please select a valid option from the menu.\n";
        }
    }

    return 0;
}