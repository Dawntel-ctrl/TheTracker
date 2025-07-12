#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

// Maximum number of workouts stored
const int MAX_WORKOUTS = 100;

// Structure to hold workout information
struct Workout {
    string date;          // Date of workout (e.g., "2024-04-23")
    string exercise;      // Name of the exercise
    int sets = 0;         // Initialize to 0 to avoid warnings
    int reps = 0;         // Initialize to 0 to avoid warnings
    string weightNotes;   // Weight used or notes
};

// Function declarations
void loadWorkouts(Workout workouts[], int& count);
void saveWorkouts(Workout workouts[], int count);
void addWorkout(Workout workouts[], int& count);
void viewTodayWorkouts(Workout workouts[], int count);
void viewWeekWorkouts(Workout workouts[], int count);
void suggestRandomWorkout();

int main() {
    Workout workouts[MAX_WORKOUTS]; // Array to store workouts
    int workoutCount = 0;           // Number of workouts stored

    // Load existing workouts from file
    loadWorkouts(workouts, workoutCount);

    int choice;

    do {
        // Display the menu
        cout << endl;
        cout << "==== Gym Workout Tracker ====" << endl;
        cout << "1. Add New Workout" << endl;
        cout << "2. View Today's Workouts" << endl;
        cout << "3. View This Week's Workouts" << endl;
        cout << "4. Suggest Random Workout Plan" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline

        switch (choice) {
        case 1:
            addWorkout(workouts, workoutCount);
            saveWorkouts(workouts, workoutCount);
            break;
        case 2:
            viewTodayWorkouts(workouts, workoutCount);
            break;
        case 3:
            viewWeekWorkouts(workouts, workoutCount);
            break;
        case 4:
            suggestRandomWorkout();
            break;
        case 5:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

// Function to load workouts from the file
void loadWorkouts(Workout workouts[], int& count) {
    ifstream inFile("workouts.txt");
    count = 0;

    if (inFile.is_open()) {
        while (count < MAX_WORKOUTS && getline(inFile, workouts[count].date)) {
            getline(inFile, workouts[count].exercise);
            inFile >> workouts[count].sets;
            inFile >> workouts[count].reps;
            inFile.ignore(); // Move past newline
            getline(inFile, workouts[count].weightNotes);
            inFile.ignore(); // Extra blank line between entries
            count++;
        }
        inFile.close();
    }
}

// Function to save workouts to the file
void saveWorkouts(Workout workouts[], int count) {
    ofstream outFile("workouts.txt");

    for (int i = 0; i < count; i++) {
        outFile << workouts[i].date << endl;
        outFile << workouts[i].exercise << endl;
        outFile << workouts[i].sets << endl;
        outFile << workouts[i].reps << endl;
        outFile << workouts[i].weightNotes << endl;
        outFile << endl; // Separate records with blank line
    }
}

// Function to add a new workout
void addWorkout(Workout workouts[], int& count) {
    if (count >= MAX_WORKOUTS) {
        cout << "Workout log is full!" << endl;
        return;
    }

    Workout w;
    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, w.date);
    cout << "Enter exercise name: ";
    getline(cin, w.exercise);
    cout << "Enter number of sets: ";
    cin >> w.sets;
    cout << "Enter number of reps: ";
    cin >> w.reps;
    cin.ignore();
    cout << "Enter weight or notes: ";
    getline(cin, w.weightNotes);

    workouts[count] = w;
    count++;

    cout << "Workout added successfully!" << endl;
}

// Function to view today's workouts
void viewTodayWorkouts(Workout workouts[], int count) {
    time_t now = time(0);
    tm localtmStruct;
    localtime_s(&localtmStruct, &now); // safer version of localtime
    tm* localtm = &localtmStruct;

    char today[11];
    strftime(today, 11, "%Y-%m-%d", localtm);

    cout << "=== Workouts for Today (" << today << ") ===" << endl;
    bool found = false;

    for (int i = 0; i < count; i++) {
        if (workouts[i].date == today) {
            cout << workouts[i].exercise << " - " << workouts[i].sets << " sets x " << workouts[i].reps << " reps (" << workouts[i].weightNotes << ")" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No workouts logged for today." << endl;
    }
}

// Function to view workouts from the past 7 days
void viewWeekWorkouts(Workout workouts[], int count) {
    cout << "=== Workouts This Week ===" << endl;
    bool found = false;

    for (int i = 0; i < count; i++) {
        cout << workouts[i].date << " - " << workouts[i].exercise << " - " << workouts[i].sets << " sets x " << workouts[i].reps << " reps (" << workouts[i].weightNotes << ")" << endl;
        found = true;
    }

    if (!found) {
        cout << "No workouts logged this week." << endl;
    }
}

// Function to suggest a random workout plan
void suggestRandomWorkout() {
    string exercises[] = { "Bench Press", "Squats", "Deadlift", "Overhead Press", "Pull-Ups", "Bicep Curls", "Tricep Extensions" };
    int numExercises = 3;

    srand(static_cast<unsigned int>(time(0))); // safer cast

    cout << "=== Suggested Workout Plan ===" << endl;
    for (int i = 0; i < numExercises; i++) {
        int idx = rand() % 7;
        int sets = rand() % 4 + 3; // 3-6 sets
        int reps = rand() % 6 + 5; // 5-10 reps

        cout << "- " << exercises[idx] << ": " << sets << " sets x " << reps << " reps" << endl;
    }
}
