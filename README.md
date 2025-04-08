# Key_Management_System
This C++ program is designed to manage employee key assignments. It allows the user to perform various operations such as adding keys, returning keys, replacing keys, and viewing key statuses for employees. It reads and writes employee data from a file and updates the status accordingly.

Features:
View All Employees and Keys: Displays a list of all employees and the keys they possess.
View Keys for an Employee: Displays the keys held by a specific employee.
Search for Employees with a Specific Key: Lists the employees who possess a specific key.
Add a Key to an Employee: Allows adding a key to an employee, ensuring the employee doesn't exceed the maximum of 5 keys.
Return a Key: Allows employees to return keys they no longer need.
Replace a Key: Allows replacing an old key with a new one across all employees.
Save and Exit: Saves the current key statuses to a file and exits the program.

Requirements:
C++17 or later
A text file containing employee data (in the specified format)

File Format:
The input file should have the following format:
The first line contains the number of employees.
For each employee, the following format is used:
Name of the employee (including spaces)
The number of keys the employee possesses
A list of up to 5 keys (room identifiers)

Functions:
bool reader(string input_filename, Employee employees[], int& nEmployees): Reads the employee data from a file and stores it in the employees array.
void writer(string output_filename, Employee employees[], int nEmployees): Writes the updated employee key data to a file.
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey): Adds a new key to an employee's key list, ensuring no more than 5 keys are assigned.
bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey): Allows an employee to return a key.
int replaceAKey(Employee employees[], int nEmployees, string oldKey, string newKey): Replaces an old key with a new key for all employees who possess the old key.
