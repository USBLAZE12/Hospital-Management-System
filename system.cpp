#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX_ENTRIES = 100;
const double GST_RATE = 0.15;

// Structure to hold patient details
struct Patient {
    int id;
    string name;
    int age;
    string disease;
    bool isCritical;
};

Patient patients[MAX_ENTRIES];
int patientCount = 0;

string schedules[MAX_ENTRIES];
int scheduleCount = 0;

string doctorNames[] = {"Dr. Ali", "Dr. Waqar", "Dr. Hasnat"};
double doctorFees[] = {500.00, 400.00, 450.00};

int getValidIntInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Please enter a valid positive integer: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

void addPatient(int id, const string& name, int age, const string& disease, bool isCritical) {
    if (patientCount < MAX_ENTRIES) {
        patients[patientCount].id = id;
        patients[patientCount].name = name;
        patients[patientCount].age = age;
        patients[patientCount].disease = disease;
        patients[patientCount].isCritical = isCritical;
        patientCount++;
        cout << "\n>>> Patient added successfully.\n";
    } else {
        cout << "\n>>> Error: Maximum patient limit reached.\n";
    }
}

void displayPatients() {
    cout << "\n+---------------------------------------------------------------+\n";
    cout << "|                      --- Patients List ---                   |\n";
    cout << "+---------------------------------------------------------------+\n";
    if (patientCount == 0) {
        cout << "| No patients available.                                        |\n";
    } else {
        cout << "| ID   | Name                          | Age | Disease        | Status |\n";
        cout << "+---------------------------------------------------------------+\n";
        for (int i = 0; i < patientCount; ++i) {
            cout << "| " << setw(6) << patients[i].id << " | " << setw(30) << patients[i].name
                 << " | " << setw(3) << patients[i].age << " | " << setw(12) << patients[i].disease
                 << " | " << (patients[i].isCritical ? "Critical" : "Stable") << " |\n";
        }
    }
    cout << "+---------------------------------------------------------------+\n";
}

void displayDoctors() {
    cout << "\n+---------------------------------------------------------------+\n";
    cout << "|                         --- Doctors ---                      |\n";
    cout << "+---------------------------------------------------------------+\n";
    for (size_t i = 0; i < sizeof(doctorNames) / sizeof(doctorNames[0]); ++i) {
        cout << "| " << setw(2) << i + 1 << ". " << setw(20) << doctorNames[i] << " | Fee: Rs. "
             << setw(6) << fixed << setprecision(2) << doctorFees[i] << " |\n";
    }
    cout << "+---------------------------------------------------------------+\n";
}

string getCurrentDate() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
}

void scheduleAppointment(const string& patient, const string& doctor) {
    if (scheduleCount < MAX_ENTRIES) {
        schedules[scheduleCount++] = patient + " with " + doctor + " on " + getCurrentDate();
        cout << "\n>>> Appointment scheduled successfully.\n";
    } else {
        cout << "\n>>> Error: Appointment list is full.\n";
    }
}

void displaySchedules() {
    cout << "\n+---------------------------------------------------------------+\n";
    cout << "|                  --- Scheduled Appointments ---               |\n";
    cout << "+---------------------------------------------------------------+\n";
    if (scheduleCount == 0) {
        cout << "| No appointments scheduled.                                    |\n";
    } else {
        for (int i = 0; i < scheduleCount; ++i) {
            cout << "| " << setw(2) << i + 1 << ". " << setw(40) << schedules[i] << " |\n";
        }
    }
    cout << "+---------------------------------------------------------------+\n";
}

int main() {
    int choice;

    do {
        cout << "\n+---------------------------------------------------------------+\n";
        cout << "|                --- Hospital Management System ---             |\n";
        cout << "+---------------------------------------------------------------+\n";
        cout << "| 1. Add Patient                                              |\n";
        cout << "| 2. Display Doctors                                          |\n";
        cout << "| 3. Schedule Appointment                                     |\n";
        cout << "| 4. Display Appointments                                     |\n";
        cout << "| 5. Display Patients                                         |\n";
        cout << "| 6. Exit                                                      |\n";
        cout << "+---------------------------------------------------------------+\n";
        cout << "Enter your choice: ";
        choice = getValidIntInput();

        switch (choice) {
            case 1: {
                string name, disease;
                int age;
                bool isCritical;
                cout << "\nEnter patient name: ";
                getline(cin, name);
                cout << "Enter patient age: ";
                age = getValidIntInput();
                cout << "Enter patient's disease: ";
                getline(cin, disease);
                cout << "Is the patient critical? (1 for Yes, 0 for No): ";
                isCritical = getValidIntInput();
                addPatient(patientCount + 1, name, age, disease, isCritical);
                break;
            }
            case 2:
                displayDoctors();
                break;
            case 3: {
                int patientIndex, doctorIndex;
                displayPatients();
                cout << "Select patient index: ";
                patientIndex = getValidIntInput();
                displayDoctors();
                cout << "Select doctor index: ";
                doctorIndex = getValidIntInput();
                if (patientIndex > 0 && patientIndex <= patientCount && doctorIndex > 0 && doctorIndex <= sizeof(doctorNames) / sizeof(doctorNames[0])) {
                    scheduleAppointment(patients[patientIndex - 1].name, doctorNames[doctorIndex - 1]);
                } else {
                    cout << "Invalid patient or doctor selection.\n";
                }
                break;
            }
            case 4:
                displaySchedules();
                break;
            case 5:
                displayPatients();
                break;
            case 6:
                cout << "\n>>> Exiting system. Goodbye!\n";
                break;
            default:
                cout << "\n>>> Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
    return 0;
}
