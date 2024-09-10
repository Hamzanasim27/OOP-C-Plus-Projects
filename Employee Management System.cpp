#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <unordered_map>
using namespace std;

class Employee {
protected:
    int employeeID;
    string name;
    double salary;
    bool projectCompleted;
    int leavesTaken;

public:
    Employee() : projectCompleted(false), leavesTaken(0) {}
    Employee(int id, string n, double s, bool projectComp, int leaves)
        : employeeID(id), name(n), salary(s), projectCompleted(projectComp), leavesTaken(leaves) {}

    virtual void display() {
        cout << "Employee ID: " << employeeID << ", Name: " << name << ", Salary: Rs" << salary;
        cout << ", Project Completed: " << (projectCompleted ? "Yes" : "No") << ", Leaves Taken: " << leavesTaken << endl;
    }
    void updateProjectCompletion(bool completed) {
        projectCompleted = completed;
    }
    int getID() {
        return employeeID;
    }

    bool isProjectCompleted() {
        return projectCompleted;
    }

    int getLeavesTaken() {
        return leavesTaken;
    }

    void incrementLeaves() {
        leavesTaken++;
    }

    virtual void save(ofstream& out) {
        out << employeeID << "," << name << "," << salary << "," << projectCompleted << "," << leavesTaken;
    }

    virtual ~Employee() {}
};

class Developer : public Employee {
private:
    string programmingLanguage;

public:
    Developer(int id, string n, double s, string lang, bool projectComp, int leaves)
        : Employee(id, n, s, projectComp, leaves), programmingLanguage(lang) {}

    void display() override {
        cout << "Developer - ";
        Employee::display();
        cout << ", Programming Language: " << programmingLanguage << endl;
    }

    void save(ofstream& out) override {
        out << "Developer,";
        Employee::save(out);
        out << "," << programmingLanguage << endl;
    }
};

class Designer : public Employee {
private:
    string designTool;

public:
    Designer(int id, string n, double s, string tool, bool projectComp, int leaves)
        : Employee(id, n, s, projectComp, leaves), designTool(tool) {}

    void display() override {
        cout << "Designer - ";
        Employee::display();
        cout << ", Design Tool: " << designTool << endl;
    }

    void save(ofstream& out) override {
        out << "Designer,";
        Employee::save(out);
        out << "," << designTool << endl;
    }
};

class Manager : public Employee {
private:
    int teamSize;

public:
    Manager(int id, string n, double s, int size, bool projectComp, int leaves)
        : Employee(id, n, s, projectComp, leaves), teamSize(size) {}

    void display() override {
        cout << "Manager - ";
        Employee::display();
        cout << ", Team Size: " << teamSize << endl;
    }

    void save(ofstream& out) override {
        out << "Manager,";
        Employee::save(out);
        out << "," << teamSize << endl;
    }
};

class Department {
private:
    int departmentID;
    string name;
    Employee** employees;
    int employeeCount;
    int employeeCapacity;

public:
    Department(int id, string n) {
        departmentID = id;
        name = n;
        employeeCount = 0;
        employeeCapacity = 5;
        employees = new Employee * [employeeCapacity];
    }

    void addEmployee(Employee* e) {
        if (employeeCount == employeeCapacity) {

            employeeCapacity *= 2;
            Employee** newEmployees = new Employee * [employeeCapacity];
            for (int i = 0; i < employeeCount; ++i) {
                newEmployees[i] = employees[i];
            }
            delete[] employees;
            employees = newEmployees;
        }
        employees[employeeCount++] = e;
    }

    void displayEmployees() {
        cout << "Department: " << name << endl;
        for (int i = 0; i < employeeCount; ++i) {
            employees[i]->display();
        }
    }

    int getID() {
        return departmentID;
    }

    void save(ofstream& out) {
        out << departmentID << "," << name << endl;
        for (int i = 0; i < employeeCount; ++i) {
            employees[i]->save(out);
        }
    }

    ~Department() {
        for (int i = 0; i < employeeCount; ++i) {
            delete employees[i];
        }
        delete[] employees;
    }
};

class Company {
private:
    Department** departments;
    int departmentCount;
    int departmentCapacity;

public:
    Company() {
        departmentCount = 0;
        departmentCapacity = 5;
        departments = new Department * [departmentCapacity];
    }

    void addDepartment(Department* d) {
        if (departmentCount == departmentCapacity) {

            departmentCapacity *= 2;
            Department** newDepartments = new Department * [departmentCapacity];
            for (int i = 0; i < departmentCount; ++i) {
                newDepartments[i] = departments[i];
            }
            delete[] departments;
            departments = newDepartments;
        }
        departments[departmentCount++] = d;
    }

    void addEmployeeToDepartment(int deptID, Employee* e) {
        for (int i = 0; i < departmentCount; ++i) {
            if (departments[i]->getID() == deptID) {
                departments[i]->addEmployee(e);
                return;
            }
        }
        cout << "Department not found!" << endl;
    }

    void displayAllDepartments() {
        for (int i = 0; i < departmentCount; ++i) {
            departments[i]->displayEmployees();
            cout << endl;
        }
    }

    void save(const string& filename) {
        ofstream out(filename);
        for (int i = 0; i < departmentCount; ++i) {
            departments[i]->save(out);
        }
        out.close();
    }

    void displayFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }

        inFile.close();
    }

    void deleteEmployeeFromFile(const string& filename, int employeeID) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        ofstream tempFile("temp.txt");
        string line;
        bool employeeFound = false;

        while (getline(inFile, line)) {
            istringstream iss(line);
            string role, idStr;

            getline(iss, role, ',');
            getline(iss, idStr, ',');

            try {
                int id = stoi(idStr);
                if (id == employeeID) {
                    employeeFound = true;
                    continue;
                }
            }
            catch (const invalid_argument& e) {


            }
            catch (const out_of_range& e) {


            }

            tempFile << line << endl;
        }

        inFile.close();
        tempFile.close();

        if (!employeeFound) {
            cout << "Employee with ID " << employeeID << " not found." << endl;
            remove("temp.txt");
            return;
        }

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        cout << "Employee with ID " << employeeID << " deleted successfully." << endl;
    }

    void searchEmployeeInFile(const string& filename, int employeeID) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            istringstream iss(line);
            string role, idStr;

            getline(iss, role, ',');
            getline(iss, idStr, ',');

            try {
                int id = stoi(idStr);
                if (id == employeeID) {
                    cout << "Employee found: " << line << endl;
                    inFile.close();
                    return;
                }
            }
            catch (const invalid_argument& e) {

            }
            catch (const out_of_range& e) {


            }
        }

        cout << "Employee with ID " << employeeID << " not found." << endl;
        inFile.close();
    }

    void markAttendance(int employeeID, const string& status) {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        tm local_time;
        localtime_s(&local_time, &now_time);

        ostringstream dateStream, timeStream;
        dateStream << put_time(&local_time, "%Y-%m-%d");
        timeStream << put_time(&local_time, "%H:%M:%S");

        string date = dateStream.str();
        string time = timeStream.str();


        bool lateArrival = false;
        if (status == "Absent") {
            lateArrival = true;
        }
        else {
            string arrivalTime = time.substr(0, 5);
            if (arrivalTime > "09:00") {
                lateArrival = true;
            }
        }

        ofstream outFile("attendance.txt", ios::app);
        outFile << employeeID << "," << date << "," << time << "," << status << endl;
        outFile.close();

        if (lateArrival && status != "Absent") {
            updateLeaves(employeeID);
            deductSalary(employeeID, 50);
            cout << "Salary deducted for late arrival." << endl;
        }
    }


    void viewAttendance(int employeeID) {
        ifstream inFile("attendance.txt");
        if (!inFile) {
            cout << "Error opening attendance file." << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(inFile, line)) {
            istringstream iss(line);
            string idStr, date, time, status;
            getline(iss, idStr, ',');
            getline(iss, date, ',');
            getline(iss, time, ',');
            getline(iss, status, ',');

            try {
                int id = stoi(idStr);
                if (id == employeeID) {
                    cout << "Date: " << date << ", Time: " << time << ", Status: " << status << endl;
                    found = true;
                }
            }
            catch (const invalid_argument& e) {
                cout << "Invalid data in attendance file." << endl;
            }
            catch (const out_of_range& e) {
                cout << "Out of range error in attendance file." << endl;
            }
        }

        if (!found) {
            cout << "No attendance records found for employee ID " << employeeID << endl;
        }

        inFile.close();
    }
    void deductSalary(int employeeID, double amount) {
        ifstream inFile("company_data.txt");
        if (!inFile) {
            cout << "Error opening company data file." << endl;
            return;
        }

        ofstream tempFile("temp.txt");
        string line;

        while (getline(inFile, line)) {
            istringstream iss(line);
            string role, idStr, name, salaryStr, projectCompStr, leavesStr;
            getline(iss, role, ',');
            getline(iss, idStr, ',');
            getline(iss, name, ',');
            getline(iss, salaryStr, ',');
            getline(iss, projectCompStr, ',');
            getline(iss, leavesStr, ',');

            try {
                int id = stoi(idStr);
                if (id == employeeID) {
                    double salary = stod(salaryStr);
                    salary -= amount;
                    if (salary < 0) {
                        salary = 0;
                    }
                    tempFile << role << "," << idStr << "," << name << "," << salary << "," << projectCompStr << "," << leavesStr;

                    while (getline(iss, line, ',')) {
                        tempFile << "," << line;
                    }
                    tempFile << endl;

                    continue;
                }
            }
            catch (const invalid_argument& e) {

            }
            catch (const out_of_range& e) {

            }

            tempFile << line << endl;
        }

        inFile.close();
        tempFile.close();

        remove("company_data.txt");
        rename("temp.txt", "company_data.txt");
    }


    void updateLeaves(int employeeID) {
        ifstream inFile("company_data.txt");
        if (!inFile) {
            cout << "Error opening company data file." << endl;
            return;
        }

        ofstream tempFile("temp.txt");
        string line;

        while (getline(inFile, line)) {
            istringstream iss(line);
            string role, idStr;
            getline(iss, role, ',');
            getline(iss, idStr, ',');

            try {
                int id = stoi(idStr);
                if (id == employeeID) {
                    string name, salaryStr, projectCompStr, leavesStr;
                    getline(iss, name, ',');
                    getline(iss, salaryStr, ',');
                    getline(iss, projectCompStr, ',');
                    getline(iss, leavesStr, ',');

                    int leaves = stoi(leavesStr) + 1;
                    tempFile << role << "," << id << "," << name << "," << salaryStr << "," << projectCompStr << "," << leaves;

                    while (getline(iss, line, ',')) {
                        tempFile << "," << line;
                    }
                    tempFile << endl;

                    continue;
                }
            }
            catch (const invalid_argument& e) {

            }
            catch (const out_of_range& e) {

            }

            tempFile << line << endl;
        }

        inFile.close();
        tempFile.close();

        remove("company_data.txt");
        rename("temp.txt", "company_data.txt");
    }

    void calculateSalaries() {
        ifstream inFile("company_data.txt");
        if (!inFile) {
            cout << "Error opening company data file." << endl;
            return;
        }

        ofstream tempFile("temp.txt");
        string line;

        while (getline(inFile, line)) {
            istringstream iss(line);
            string role, idStr, name, salaryStr, projectCompStr, leavesStr;
            getline(iss, role, ',');
            getline(iss, idStr, ',');
            getline(iss, name, ',');
            getline(iss, salaryStr, ',');
            getline(iss, projectCompStr, ',');
            getline(iss, leavesStr, ',');

            try {
                int leaves = stoi(leavesStr);
                double salary = stod(salaryStr);
                bool projectCompleted = (projectCompStr == "1");

                if (leaves > 3) {
                    salary -= (leaves - 3) * 100;
                }

                if (projectCompleted) {
                    salary += 500;
                }

                tempFile << role << "," << idStr << "," << name << "," << salary << "," << projectCompStr << "," << leaves;

                while (getline(iss, line, ',')) {
                    tempFile << "," << line;
                }
                tempFile << endl;
            }
            catch (const invalid_argument& e) {

            }
            catch (const out_of_range& e) {

            }
        }

        inFile.close();
        tempFile.close();

        remove("company_data.txt");
        rename("temp.txt", "company_data.txt");
    }

    ~Company() {
        for (int i = 0; i < departmentCount; ++i) {
            delete departments[i];
        }
        delete[] departments;
    }
};

Employee* createEmployee() {
    int id;
    string name;
    double salary;
    bool projectCompleted;
    int leavesTaken = 0;
    int type;

    cout << "Enter Employee ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Salary: ";
    cin >> salary;
    cout << "Has the employee completed the project? (1 for Yes, 0 for No): ";
    cin >> projectCompleted;
    cout << "Select Employee Type (1. Developer 2. Designer 3. Manager): ";
    cin >> type;

    if (type == 1) {
        string lang;
        cout << "Enter Programming Language: ";
        cin >> lang;
        return new Developer(id, name, salary, lang, projectCompleted, leavesTaken);
    }
    else if (type == 2) {
        string tool;
        cout << "Enter Design Tool: ";
        cin >> tool;
        return new Designer(id, name, salary, tool, projectCompleted, leavesTaken);
    }
    else if (type == 3) {
        int size;
        cout << "Enter Team Size: ";
        cin >> size;
        return new Manager(id, name, salary, size, projectCompleted, leavesTaken);
    }
    else {
        cout << "Invalid type selected." << endl;
        return nullptr;
    }
}
unordered_map<string, string> loadUsers(const string& filename) {
    unordered_map<string, string> users;
    ifstream infile(filename);
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string username, password;
        getline(ss, username, ',');
        getline(ss, password, ',');
        users[username] = password;
    }
    return users;
}


void saveUser(const string& filename, const string& username, const string& password) {
    ofstream outfile(filename, ios::app);
    outfile << username << "," << password << endl;
}


void registerUser(const string& filename) {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;

    saveUser(filename, username, password);
    cout << "User registered successfully!" << endl;
}

bool verifyLogin(const unordered_map<string, string>& users) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        cout << "Login successful!" << endl;
        return true;
    }
    else {
        cout << "Invalid username or password." << endl;
        return false;
    }
}
int main() {
    string usersFile = "users.txt";


    int choice;
    cout << "1. Register\n2. Login\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        registerUser(usersFile);
        return 0;
    }

    unordered_map<string, string> users = loadUsers(usersFile);


    if (!verifyLogin(users)) {
        return 0;
    }

    Company company;

    while (true) {
        cout << endl;
        cout << "\t\t\t\t\t.......*****HAMZA & Co*****......." << endl;
        cout << "\t\t\t\t\t  .............MENU.............";
        cout << endl;
        cout << "\n1. Add Department\n2. Add Employee\n3. Display All Departments\n4. Save to File\n5. Display all employees information\n6. Search Employee\n7. Delete Employee\n8. Mark Attendance\n9. View Attendance\n10. Calculate Salaries\n11. Exit\nEnter your choice: ";
        cin >> choice;
        if (choice == 1) {
            int deptID;
            string deptName;
            cout << "Enter Department ID: ";
            cin >> deptID;
            cout << "Enter Department Name: ";
            cin.ignore();
            getline(cin, deptName);
            Department* dept = new Department(deptID, deptName);
            company.addDepartment(dept);
        }
        else if (choice == 2) {
            int deptID;
            cout << "Enter Department ID to add employee to: ";
            cin >> deptID;
            Employee* emp = createEmployee();
            if (emp != nullptr) {
                company.addEmployeeToDepartment(deptID, emp);
            }
        }
        else if (choice == 3) {
            company.displayFromFile("company_data.txt");
            company.displayAllDepartments();
        }
        else if (choice == 4) {
            company.save("company_data.txt");
            cout << "Data saved to company_data.txt" << endl;
        }
        else if (choice == 5) {
            company.displayFromFile("company_data.txt");
        }
        else if (choice == 6) {
            int empid;
            cout << "Enter employee id: ";
            cin >> empid;
            company.searchEmployeeInFile("company_data.txt", empid);
        }
        else if (choice == 7) {
            int empid;
            cout << "Enter employee id to delete: ";
            cin >> empid;
            company.deleteEmployeeFromFile("company_data.txt", empid);
        }
        else if (choice == 8) {
            int empid;
            string status;
            cout << "Enter employee ID: ";
            cin >> empid;
            cout << "Enter attendance status (Present/Absent): ";
            cin >> status;
            company.markAttendance(empid, status);
            cout << "Attendance marked." << endl;
        }
        else if (choice == 9) {
            int empid;
            cout << "Enter employee ID: ";
            cin >> empid;
            company.viewAttendance(empid);
        }
        else if (choice == 10) {
            company.calculateSalaries();
            cout << "Salaries calculated and updated in the file." << endl;
        }
        else if (choice == 11) {
            break;
        }
        else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}

