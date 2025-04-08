#include <iostream>
#include <fstream>

using namespace std;

struct Employee {
    string name; // a string that holds the name of an employee (that may contain whitespaces)
    int nKeysPossessed; //an integer that stores the number of keys an employee owns
    string keys[5]; //a string array with 5 elements. Each element stores the room that the key can opens, e.g., "AHC201"
};

bool reader(string input_filename, Employee employees[], int& nEmployees); //Reads the employee data from a file and stores it in the employees array.
void writer(string output_filename, Employee employees[], int nEmployees); //Writes the updated employee key data to a file.
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey); //Adds a new key to an employee's key list, ensuring no more than 5 keys are assigned.
bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey); //Allows an employee to return a key.
int replaceAKey(Employee employees[], int nEmployees, string oldKey, string newKey); //Replaces an old key with a new key for all employees who possess the old key.

int main() {
    string filename;
    cout << "Please enter key file name to start: ";
    cin >> filename;
    cin.ignore();

    Employee employees[100];
    int nEmployees;
    if (!reader(filename, employees, nEmployees)) {
        cout << "File not found, exiting the program..." << endl;
        return 1;
    }

    int choice;
    do { // Ask for the user to input a number for one of the following options.
        cout << "Please select from the following options: " << endl;
        cout << "  1. show all employees and their keys" << endl;
        cout << "  2. show the keys an employee possesses" << endl;
        cout << "  3. show which employees possess a specific key" << endl;
        cout << "  4. add a key to an employee" << endl;
        cout << "  5. return a key by an employee" << endl;
        cout << "  6. replace a key" << endl;
        cout << "  7. save the current key status" << endl;
        cout << "  8. exit the program" << endl;
        cin >> choice;
        cin.ignore();

        switch (choice) { //It check the option the user choose and output the case that match whith that option. In case the user input a non-valid option it will ask to input an option once again.
        case 1:
            for (int i = 0; i < nEmployees; i++) {
                cout << "Name: " << employees[i].name << endl;
                cout << "Keys possessed: ";
                for (int j = 0; j < employees[i].nKeysPossessed; j++) {
                    cout << employees[i].keys[j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            break;

        case 2: {
            string name;
            cout << "Please enter employee's name: ";
            getline(cin, name);
            bool found = false;
            for (int i = 0; i < nEmployees; i++) {
                if (employees[i].name == name) {
                    found = true;
                    cout << name << " possess the following keys: ";
                    for (int j = 0; j < employees[i].nKeysPossessed; j++) {
                        cout << employees[i].keys[j] << " ";
                    }
                    cout << endl;
                }
            }
            if (!found) {
                cout << "Cannot find the specified employee!" << endl;
            }
            cout << endl;
            break;
        }

        case 3: {
            string key;
            cout << "Please enter a key: ";
            cin >> key;
            bool found = false;
            for (int i = 0; i < nEmployees; i++) {
                for (int j = 0; j < employees[i].nKeysPossessed; j++) {
                    if (employees[i].keys[j] == key) {
                        if (found) cout << ", ";
                        cout << employees[i].name;
                        found = true;
                    }
                }
            }
            if (found) {
                cout << ", possess this key." << endl;
            }
            if (!found) {
                cout << "No one possesses this key." << endl;
            }
            cout << endl;
            break;
        }

        case 4: {
            string name, key;
            cout << "Please enter employee's name: ";
            getline(cin, name);
            cout << "Please enter a new key: ";
            cin >> key;
            if (addKeyForEmployee(employees, nEmployees, name, key)) {
                cout << "Key added successfully." << endl;
            }
            cout << endl;
            break;
        }
        case 5: {
            string name, key;
            cout << "Please enter employee's name: ";
            getline(cin, name);
            cout << "Please enter the returned key: ";
            cin >> key;
            if (returnAKey(employees, nEmployees, name, key)) {
                cout << "Key returned successfully." << endl;
            }
            cout << endl;
            break;
        }
        case 6: {
            string oldKey, newKey;
            cout << "Please enter the old key: ";
            cin >> oldKey;
            cout << "Please enter the new key: ";
            cin >> newKey;
            int count = replaceAKey(employees, nEmployees, oldKey, newKey);
            cout << "Reissued " << count << " keys." << endl;
            break;
        }
        case 7: {
            writer("keys_updated.txt", employees, nEmployees);
            cout << "Key status saved successfully." << endl;
            break;
        }
        case 8: {
            writer("keys_updated.txt", employees, nEmployees);
            cout << "Thank you for using the system! Goodbye!" << endl;
            break;
        }
        default:
            cout << "Not a valid option. Please try again." << endl;
            cout << endl;
        }

    } while (choice != 8);

    return 0;
}

//Reads the employee data from a file and stores it in the employees array.
bool reader(string input_filename, Employee employees[], int& nEmployees) {
    ifstream fin(input_filename);
    if (!fin.is_open()) {
        return false;
    }
    fin >> nEmployees;
    fin.ignore();
    for (int i = 0; i < nEmployees; i++) {
        getline(fin, employees[i].name);
        fin >> employees[i].nKeysPossessed;
        for (int j = 0; j < employees[i].nKeysPossessed; j++) {
            fin >> employees[i].keys[j];
        }
        fin.ignore();
    }
    fin.close();
    return true;
}

//Writes the updated employee key data to a file.
void writer(string output_filename, Employee employees[], int nEmployees) {
    ofstream fout(output_filename);
    fout << nEmployees << endl;
    for (int i = 0; i < nEmployees; i++) {
        fout << employees[i].name << endl;
        fout << employees[i].nKeysPossessed;
        for (int j = 0; j < employees[i].nKeysPossessed; j++) {
            fout << " " << employees[i].keys[j];
        }
        fout << endl;
    }
    fout.close();

}

//Adds a new key to an employee's key list, ensuring no more than 5 keys are assigned.
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey) {
    for (int i = 0; i < nEmployees; i++) {
        if (employees[i].name == emp_name) {
            if (employees[i].nKeysPossessed >= 5) {
                cout << "This employee already has 5 keys!" << endl;
                return false;
            }
            for (int j = 0; j < employees[i].nKeysPossessed; j++) {
                if (employees[i].keys[j] == newKey) {
                    cout << "This employee already has this key!" << endl;
                    return false;
                }
            }
            employees[i].keys[employees[i].nKeysPossessed] = newKey;
            employees[i].nKeysPossessed++;
            return true;
        }
    }
    cout << "Cannot find the specified employee!" << endl;
    return false;
}

//Allows an employee to return a key.
bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey) {
    for (int i = 0; i < nEmployees; i++) {
        if (employees[i].name == emp_name) {
            for (int j = 0; j < employees[i].nKeysPossessed; j++) {
                if (employees[i].keys[j] == returnKey) {
                    for (int k = j; k < employees[i].nKeysPossessed - 1; k++) {
                        employees[i].keys[k] = employees[i].keys[k + 1];
                    }
                    employees[i].nKeysPossessed--;
                    return true;
                }
            }
            cout << "This employee does not have the specified key!" << endl;
            return false;
        }
    }
    cout << "Cannot find the specified employee!" << endl;
    return false;
}

//Replaces an old key with a new key for all employees who possess the old key.
int replaceAKey(Employee employees[], int nEmployees, string oldKey, string newKey) {
    int count = 0;
    for (int i = 0; i < nEmployees; i++) {
        for (int j = 0; j < employees[i].nKeysPossessed; j++) {
            if (employees[i].keys[j] == oldKey) {
                employees[i].keys[j] = newKey;
                count++;
            }
        }
    }
    return count;
}