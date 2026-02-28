#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAX 50

// ---------------- STRUCT ----------------
struct Car {
    int slot;
    string ownerName;
    char vehicleNo[20];
};

// ------------- GLOBAL DATA --------------
Car parking[MAX];
int carCount = 0;

// -------- FUNCTION DECLARATIONS ---------
void parkCar();
void removeCar();
void displayCars();
void saveToFile();
void loadFromFile();

// ----------------- MAIN -----------------
int main() {
    int choice;
    loadFromFile();

    cout << "=================================\n";
    cout << "     CAR PARKING MANAGEMENT       \n";
    cout << "=================================\n";

    do {
        cout << "\n1. Park Car";
        cout << "\n2. Remove Car";
        cout << "\n3. Display Parked Cars";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: parkCar(); break;
            case 2: removeCar(); break;
            case 3: displayCars(); break;
            case 4:
                saveToFile();
                cout << "\nData saved successfully. Exiting...\n";
                break;
            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

// ================= FUNCTIONS =================

void parkCar() {
    if (carCount >= MAX) {
        cout << "\nParking is full!\n";
        return;
    }

    Car &c = parking[carCount];
    c.slot = carCount + 1;

    cin.ignore(1000, '\n');

    cout << "Enter Owner Name: ";
    getline(cin, c.ownerName);

    cout << "Enter Vehicle Number: ";
    cin.getline(c.vehicleNo, 20);

    carCount++;
    cout << "\nCar parked at slot " << c.slot << endl;
}

void removeCar() {
    int slot;
    cout << "\nEnter slot number to remove car: ";
    cin >> slot;

    if (slot < 1 || slot > carCount) {
        cout << "\nInvalid slot number!\n";
        return;
    }

    for (int i = slot - 1; i < carCount - 1; i++) {
        parking[i] = parking[i + 1];
        parking[i].slot = i + 1;
    }

    carCount--;
    cout << "\nCar removed successfully!\n";
}

void displayCars() {
    if (carCount == 0) {
        cout << "\nNo cars parked.\n";
        return;
    }

    cout << "\n------ PARKED CARS ------\n";
    for (int i = 0; i < carCount; i++) {
        cout << "Slot: " << parking[i].slot << endl;
        cout << "Owner: " << parking[i].ownerName << endl;
        cout << "Vehicle No: " << parking[i].vehicleNo << endl;
        cout << "-------------------------\n";
    }
}

// -------- FILE SAVE (ABSOLUTE PATH) --------
void saveToFile() {
    ofstream file("/Users/user/Desktop/itp_project/parking.txt");

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file << carCount << endl;
    for (int i = 0; i < carCount; i++) {
        file << parking[i].slot << endl;
        file << parking[i].ownerName << endl;
        file << parking[i].vehicleNo << endl;
    }

    file.close();
}

// -------- FILE LOAD (ABSOLUTE PATH) --------
void loadFromFile() {
    ifstream file("/Users/user/Desktop/itp_project/carparking.txt");
    if (!file) return;

    file >> carCount;
    file.ignore(1000, '\n');

    for (int i = 0; i < carCount; i++) {
        file >> parking[i].slot;
        file.ignore(1000, '\n');
        getline(file, parking[i].ownerName);
        file.getline(parking[i].vehicleNo, 20);
    }

    file.close();
}
