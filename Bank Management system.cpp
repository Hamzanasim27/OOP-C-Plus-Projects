#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <cstdlib>
#include <regex>
#include <chrono>
#include <thread>
#include <iomanip> 
using namespace std;
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define UNDERLINE "\033[4m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define BLUE "\033[34m"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    bool isValidUsername(const string& username);
bool isUsernameTaken(const string& filename, const string& username);
bool isValidPassword(const string& password);
void signUpWadiah(const string& filename, const string& userType);
void handleWadiahAccount(const string& username);
void handleComplaint(const string& username);
void displayRandomHadith();
bool isValidDate(const string& date);
bool isOver18(const string& date);
void displayUserInformation(const string& username);
bool authenticateUser(const string& filename, const string& username, const string& password);
bool isValidCNIC(const string& cnic);

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

// ANSI color codes for console text colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

class Bank {
public:
    Bank() {
        name = "Object Oriented Bank";
        helpline = "+92345678910";
        address = "objectorientedbank@gmail.com";
        hadith = "\"The Messenger of Allah (SAW) cursed the one who consumes Riba (interest), the one who gives it to others, and the two witnesses to the transaction, and said: they are all alike.\"";
        hadithReference = "(Sunan Ibn Majah, Book 24, Hadith 2821)";
    }

    void printWithTransition(const string& text, const string& color) {
        for (char c : text) {
            cout << color << c << ANSI_COLOR_RESET << flush;
            this_thread::sleep_for(chrono::milliseconds(65));
        }
        cout << endl;
    }

    void clearScreen() {
        // Clear screen
        cout << "\033[2J\033[1;1H";
    }

    void displayBankInfo() {
        clearScreen();

        // Bank name and contact information
        cout << ANSI_COLOR_RED << "\t\t\t******"<<RESET<<ANSI_COLOR_BLUE<<"---------------------------------------------------- "<<RESET<< ANSI_COLOR_RED<<"******" << ANSI_COLOR_RESET << endl;
        printWithTransition("\t\t\t        WELCOME TO OOP BANK MANAGEMENT SYSTEM ", ANSI_COLOR_CYAN);
        printWithTransition("\t\t\t *****----------------------------------------------------*****", ANSI_COLOR_CYAN);
        cout << endl;
        cout << "\t\t\t     " << name << endl;
        cout << "\t\t\t     Helpline: " << helpline << endl;
        cout << "\t\t\t     Address: " << address << endl;
        cout << endl;

        // Hadith about Riba (Interest)
        
        cout << endl;

        // Bottom line separator
        cout << ANSI_COLOR_RED << "\t\t\t----------------------------------------------------" << ANSI_COLOR_RESET << endl;
        cout << endl;
    }

    void showLoading(int durationInSeconds) {
        clearScreen();

        // Display bank information
        

        // Simulate loading process with stick man animation
        const int totalSteps = 20;
        int position = 0;
        cout << "\t\t\t Please wait while we load your account..." << endl;
        cout << "\t\t\t +-------------------------------------------+" << endl;
        cout << "\t\t\t |              LOADING...                   |" << endl;
        cout << "\t\t\t +-------------------------------------------+" << endl;

        for (int i = 0; i <= totalSteps; ++i) {
            cout << "\t\t\t " << string(position, ' ') << " O " << endl;
            cout << "\t\t\t " << string(position, ' ') << "/|\\" << endl;
            cout << "\t\t\t " << string(position, ' ') << " | " << endl;
            cout << "\t\t\t " << string(position, ' ') << "/ \\" << endl;

            // Move position to the right
            ++position;

            // Pause for a short time (200 milliseconds)
            this_thread::sleep_for(chrono::milliseconds(200));

            // Clear the previous stick man animation by moving the cursor up
            if (i < totalSteps) {
                cout << "\033[4A"; // Move cursor up 4 lines
            }
        }
        cout << endl;
        cout << endl;
        cout << endl;
        clearScreen();
        
        cout <<"\t\t\t" <<ANSI_COLOR_YELLOW << "************************************" << RESET << endl;

        // Hadith title
        cout <<"\t\t\t" << ANSI_COLOR_YELLOW << "*  " << ANSI_COLOR_YELLOW << "Hadith about Riba (Interest):           " << ANSI_COLOR_YELLOW << "  " << RESET << endl;

        // Hadith content
        cout <<"\t\t\t" << ANSI_COLOR_YELLOW << "*  " << ANSI_COLOR_GREEN << "The Messenger of Allah (SAW) cursed the one who consumed Riba,  " << ANSI_COLOR_YELLOW << "  " << RESET << endl;
        cout << "\t\t\t" <<ANSI_COLOR_YELLOW << "*  " << ANSI_COLOR_GREEN << "and the one who charged it, those who witnessed it, and the one who recorded it  " << ANSI_COLOR_YELLOW << "  " << RESET << endl;

        // Source
        cout <<"\t\t\t" << ANSI_COLOR_YELLOW << "*  " << ANSI_COLOR_CYAN << "Jami` at-Tirmidhi 1206                         " << ANSI_COLOR_YELLOW << "  " << RESET << endl;

        // Bottom border of the box
        cout <<"\t\t\t" << ANSI_COLOR_YELLOW << "************************************" << RESET << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout <<RED<<"+----------------------------------------+" <<RESET<< endl;
        cout << "|             Please select an option    |" << endl;
        cout << "|             to sign in:                |" << endl;
        cout << RED << "| -------------------------------------- |" << RESET << endl;
        cout << "|    1. Employee Sign In                 |" << endl;
        cout << "|    2. Customer Portal                  |" << endl;
        cout << "|    3. Quit                             |" << endl;
        cout << RED << "+----------------------------------------+" << RESET << endl;
    }

private:
    string name;
    string helpline;
    string address;
    string hadith;
    string hadithReference;
};



class Employee : public Bank {
private:
    string position;
    float salary;

public:
    Employee() {
        cout << "--------------------------------------------------------------------------" << endl;
    }

    void CheckSalary() {
        cout <<"\t\t\t" << "Your salary is: " << salary << endl;
        cout << "\t\t\tDated: " << __DATE__ << endl;
    }

    void CheckRequests() {
        system("cls");
        ifstream myfile("Assist.txt");
        if (!myfile) {
            cout << RED << "Error in opening File! " << RESET << endl;
        }
        else {
            string read;
            while (getline(myfile, read)) {
                cout << read << endl;
                cout << "----------------------------------------------------------" << endl;
            }
        }
        myfile.close();
    }
    void CheckComplains() {
        system("cls");
        ifstream myfile("Complaint.txt");
        if (!myfile) {
            cout << RED << "Error in opening File! " << RESET << endl;
        }
        else {
            string read;
            while (getline(myfile, read)) {
                cout << read << endl;
                cout << "----------------------------------------------------------" << endl;
            }
        }
        myfile.close();
    }

    void CheckNotification() {
        system("cls");
        ifstream myfile("Notificationn.txt");
        if (!myfile) {
            cout << RED << "Error in opening file!" << RESET << endl;
        }
        else {
            string read;
            while (getline(myfile, read)) {
                cout << GREEN << read << RESET << endl;
            }
        }
        myfile.close();
    }

    void Inform() {
        system("cls");
        if (position == "Manager") {
            ofstream myfile("Notificationn.txt", ios::out | ios::app);
            if (!myfile) {
                cout << RED << "Error in Opening File! " << RESET << endl;
            }
            else {
                string Write;
                myfile << "\t\t\tDate: " << __DATE__ << " Time: " << __TIME__ << endl;
                cout << CYAN << "Enter your Message: ";
                cin.ignore();
                getline(cin, Write);
                myfile << Write << endl;
                cout << GREEN << "Notification has been Sent Successfully! " << RESET << endl;
            }
            myfile.close();
        }
        else {
            cout << RED << "You don't have the permission to send notifications! " << RESET << endl;
        }
    }

    void setSalary() {
        if (position == "Manager") {
            salary = 50000;
        }
        else if (position == "AssistantManager") {
            salary = 40000;
        }
        else if (position == "Clerk") {
            salary = 25000;
        }
        else if (position == "Cashier") {
            salary = 20000;
        }
        else if (position == "ITExpert") {
            salary = 40000;
        }
        else if (position == "Intern") {
            salary = 10000;
        }
        else {
            salary = 15000;
        }
    }

    void modifySignIn(const string& filename) {
        system("cls");
        if (position == "ITExpert") {
            string username, password, position;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";

            password.clear();
            char ch;
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (!password.empty()) {
                        password.pop_back();
                        cout << "\b \b";
                    }
                }
                else {
                    cout << "*";
                    password.push_back(ch);
                }
            }
            cout << endl;

            cout << "Enter position: ";
            cin >> position;

            ifstream file(filename);
            if (file.is_open()) {
                string storedUsername, storedPassword, storedPosition;
                bool found = false;
                ofstream temp("temp.txt", ios::out);

                while (file >> storedUsername >> storedPassword >> storedPosition) {
                    if (position == storedPosition) {
                        found = true;
                        cout << "A matching position found in the file." << endl;
                        cout << "Do you want to overwrite it? (Y/N): ";
                        char choice;
                        cin >> choice;

                        if (choice == 'Y' || choice == 'y') {
                            temp << username << " " << password << " " << position << endl;
                            cout << GREEN << "Entry overwritten successfully!" << RESET << endl;
                        }
                        else {
                            cout << GREEN << "Entry not overwritten." << RESET << endl;
                            continue;
                        }
                    }
                    else {
                        temp << storedUsername << " " << storedPassword << " " << storedPosition << endl;
                    }
                }

                if (!found) {
                    cout << YELLOW << "No matching position found in the file." << RESET << endl;
                    cout << "Do you want to add it? (Y/N): ";
                    char choice;
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y') {
                        temp << username << " " << password << " " << position << endl;
                        cout << GREEN << "New entry added successfully!" << RESET << endl;
                    }
                    else {
                        cout << GREEN << "No changes made." << RESET << endl;
                    }
                }

                file.close();
                temp.close();
                remove(filename.c_str());
                rename("temp.txt", filename.c_str());
            }
            else {
                cout << RED << "Error: Unable to open file." << RESET << endl;
            }
        }
        else {
            cout << RED << "Error you don't have permission to add an employee!" << RESET << endl;
        }
    }

    bool signInEmployee(const string& filename) {
        string username, password, storedUsername, storedPassword, storedPosition;
        bool authenticated = false;

        for (int attempt = 0; attempt < 3; attempt++) {
            system("cls");
            cout << "Enter " << CYAN << "Employee" << RESET << " username: ";
            cin >> username;
            cout << "Enter " << CYAN << "Employee" << RESET << " password: ";

            password.clear();
            char ch;
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (!password.empty()) {
                        password.pop_back();
                        cout << "\b \b";
                    }
                }
                else {
                    cout << "*";
                    password.push_back(ch);
                }
            }
            cout << endl;

            ifstream file(filename);
            if (file.is_open()) {
                while (file >> storedUsername >> storedPassword >> storedPosition) {
                    if (storedUsername == username && storedPassword == password) {
                        file.close();
                        authenticated = true;
                        position = storedPosition;
                        setSalary();
                        cout << GREEN << "Employee sign in successful!" << RESET << endl;
                        return true;
                    }
                }
                file.close();
            }

            if (!authenticated) {
                cout << RED << "Invalid username or password. Try again." << RESET << endl;
            }
        }

        cout << RED << "Too many failed attempts. Exiting..." << RESET << endl;
        return false;
    }
};

class Customer : public Bank {
protected:
    string dob;
    string accountno;
    string name;
    string username;
    string acctype;
    string password;
    string nationality;
    string CNIC;
    int balance;
    int currentbalance;
    int remainingbalance;
    int withdrawamount;
    string accountcreationdate;

public:
    Customer() {
        dob = " ";
        accountno = " ";
        name = " ";
        username = " ";
        password = " ";
        nationality = " ";
        balance = 0;
        currentbalance = 0;
        remainingbalance = 0;
        withdrawamount = 0;
    }

    bool isValidUsername(const string& username) {
        return isalpha(username[0]);
    }

    bool isUsernameTaken(const string& filename, const string& username) {
        ifstream file(filename);
        string storedUsername, storedPassword;
        if (file.is_open()) {
            while (file >> storedUsername >> storedPassword) {
                if (storedUsername == username) {
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    bool isValidPassword(const string& password) {
        if (password.length() < 8) return false;
        bool hasSpecialChar = false;
        for (char ch : password) {
            if (ispunct(ch)) {
                hasSpecialChar = true;
                break;
            }
        }
        return hasSpecialChar;
    }

    void signUp(const string& filename, const string& userType) {

        string username, password, name, dob, nationality, acctype;
        double balance;
        system("cls");
        cout << "Enter your First Name: ";
        cin >> name;
        cout << "Enter your Date of Birth: ";
        cin >> dob;
        cout << "Enter your CNIC:";
        cin >> CNIC;
        cout << "Enter your Nationality: ";
        cin >> nationality;
        cout << "Enter balance: (greater than 200): ";
        cin >> balance;

        int choice;
        int attempts = 0;
        do {
            system("cls");
            cout << "What type of account do you want? " << endl;
            cout << "1. Murabahah Account" << endl;
            cout << "2. Wadiah Account" << endl;
            cout << "3. Wakalah Account" << endl;
            cout << "4. Ijarah Account" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            attempts++;
        } while ((choice < 1 || choice > 4) && attempts < 3);

        if (attempts >= 3) {
            cout << RED << "Too many incorrect attempts. Exiting..." << RESET << endl;
            return;
        }

        cout << "Enter your username: ";
        cin >> username;

        if (!isValidUsername(username)) {
            cout << RED << "Username must start with an alphabet." << RESET << endl;
            signUp(filename, userType);
            return;
        }

        if (isUsernameTaken(filename, username)) {
            cout << RED << "Username already taken. Please choose a different username." << RESET << endl;
            signUp(filename, userType);
            return;
        }

        int passwordAttempts = 0;
        do {
            password.clear();
            cout << "Enter your password (minimum 8 characters with at least one special character): ";

            char ch;
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (!password.empty()) {
                        password.pop_back();
                        cout << "\b \b";
                    }
                }
                else {
                    cout << "*";
                    password.push_back(ch);
                }
            }
            cout << endl;

            if (!isValidPassword(password)) {
                cout << RED << "Password does not meet the criteria. Please try again." << RESET << endl;
                passwordAttempts++;
            }
            else {
                break;
            }
        } while (passwordAttempts < 3);

        if (passwordAttempts >= 3) {
            cout << RED << "Too many incorrect attempts. Exiting..." << RESET << endl;
            return;
        }

        ofstream myfile(filename, ios::out | ios::app);
        if (!myfile) {
            cout << RED << "Error in Opening file! " << RESET << endl;
        }
        else {
            myfile << username << " " << password << " " << name << " " << dob << " " << CNIC << " " << nationality << " " << balance << " " << acctype << endl;
            myfile.close();
            cout << GREEN << "Account has been created successfully!" << RESET << endl;
        }
    }

    bool signIn(const string& filename, const string& userType) {
        string storedUsername, storedPassword, storedName, storedDob, storedNationality, storedAcctype;
        int storedBalance;
        bool authenticated = false;

        int attempts = 0;
        do {
            cout << "Enter " << CYAN << userType << RESET << " username: ";
            cin >> username;
            cout << "Enter " << CYAN << userType << RESET << " password: ";

            password.clear();
            char ch;
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (!password.empty()) {
                        password.pop_back();
                        cout << "\b \b";
                    }
                }
                else {
                    cout << "*";
                    password.push_back(ch);
                }
            }
            cout << endl;

            ifstream file(filename);
            if (file.is_open()) {
                while (file >> storedUsername >> storedPassword) {
                    if (storedUsername == username && storedPassword == password) {
                        file.close();
                        authenticated = true;

                        cout << GREEN << "Customer sign in successful!" << RESET << endl;
                        cout << "Welcome to your " << acctype << ". What would you like to do?" << endl;
                        return true;
                    }
                }
                file.close();
            }

            if (!authenticated) {
                cout << RED << "Invalid username or password. Try again." << RESET << endl;
                attempts++;
            }
        } while (attempts < 3);

        if (attempts >= 3) {
            cout << RED << "Too many failed attempts. Exiting..." << RESET << endl;
            return false;
        }
    }

    string getName() const {
        return name;
    }
    void clearScreen() {
#ifdef _WIN32
        system("CLS");
#else

#endif
    }
};

class IslamicAccount : public Customer{
public:
    virtual void deposit(float amount) = 0;
    virtual void withdraw(float amount) = 0;
    virtual void displayBalance() = 0;
    virtual void deductZakat() = 0;
    virtual void giveHibah(float amount) = 0;
    virtual void updateBalanceInFile(const string& username) = 0;
    virtual bool transferMoney(const string& recipientUsername, float amount) = 0;
};

class WadiahAccount : public IslamicAccount {
private:
    float balance;
    string accountNumber;
    string notifications;

public:
    WadiahAccount() : balance(0) {}

    void deposit(float amount) override {
        balance += amount;
        cout << "Deposited " << amount << " into Wadiah Account." << endl;
    }

    void withdraw(float amount) override {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrew " << amount << " from Wadiah Account." << endl;
        }
        else {
            cout << "Insufficient balance." << endl;
        }
    }

    void displayBalance() override {
        cout << "Wadiah Account Balance: " << balance << endl;
    }

    void deductZakat() override {
        balance = balance*0.025;

        cout << "Deducted Successfully" << endl;
    }

    void giveHibah(float amount) override {
        balance += amount;
        cout << "Hibah of " << amount << " given to you! May Allah bless you." << endl;
        displayRandomHadith();
    }

    void updateBalance(float newBalance) {
        balance = newBalance;
    }

    string getAccountNumber() const {
        return accountNumber;
    }

    void setAccountNumber(const string& accNumber) {
        accountNumber = accNumber;
    }

    void updateBalanceInFile(const string& username) override {
        ofstream userFile(username + ".txt");
        if (userFile.is_open()) {
            userFile << "Username: " << username << endl;
            userFile << "Balance: " << balance << endl;
            userFile << "Account Number: " << accountNumber << endl;
            userFile << "Notifications:\n" << notifications << endl;
            userFile.close();
        }
        else {
            cout << RED << "Error updating balance in file for user " << username << RESET << endl;
        }
    }

    void loadBalanceFromFile(const string& username) {
        ifstream userFile(username + ".txt");
        if (userFile.is_open()) {
            string line;
            while (getline(userFile, line)) {
                if (line.find("Balance: ") == 0) {
                    balance = stof(line.substr(9));
                }
                else if (line.find("Account Number: ") == 0) {
                    accountNumber = line.substr(16);
                }
                else if (line.find("Notifications:") == 0) {
                    notifications = line.substr(14);
                }
            }
            userFile.close();
        }
    }

    string generateAccountNumber() {
        srand(static_cast<unsigned int>(time(0)));
        return "IBL-" + to_string(rand() % 1000000);
    }

    bool transferMoney(const string& recipientUsername, float amount) override {
        ifstream recipientFile(recipientUsername + ".txt");
        if (!recipientFile.is_open()) {
            cout << RED << "Recipient account not found." << RESET << endl;
            return false;
        }

        WadiahAccount recipientAccount;
        string line;
        float recipientBalance = 0.0f;
        while (getline(recipientFile, line)) {
            if (line.find("Balance: ") == 0) {
                recipientBalance = stof(line.substr(9));
                break;
            }
        }
        recipientFile.close();

        if (balance >= amount) {
            balance -= amount;
            recipientBalance += amount;

            updateBalanceInFile(recipientUsername);
            recipientAccount.updateBalance(recipientBalance);
            recipientAccount.updateBalanceInFile(recipientUsername);

            cout << GREEN << "Transfer successful." << RESET << endl;
            return true;
        }
        else {
            cout << RED << "Insufficient balance for transfer." << RESET << endl;
            return false;
        }
    }
};

bool isValidUsername(const string& username) {
    return isalpha(username[0]);
}
void printCenteredLine(const string& line, int width) {
    int padding = (width - line.length()) / 2;
    cout << string(padding, ' ') << line << string(padding, ' ') << endl;
}

bool isUsernameTaken(const string& filename, const string& username) {
    ifstream file(filename);
    string storedUsername, storedPassword;
    if (file.is_open()) {
        while (file >> storedUsername >> storedPassword) {
            if (storedUsername == username) {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}

bool isValidPassword(const string& password) {
    if (password.length() < 8) return false;
    bool hasSpecialChar = false;
    for (char ch : password) {
        if (ispunct(ch)) {
            hasSpecialChar = true;
            break;
        }
    }
    return hasSpecialChar;
}

bool isValidDate(const string& date) {
    regex datePattern("^\\d{2}-\\d{2}-\\d{4}$");
    if (!regex_match(date, datePattern)) {
        return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !isLeapYear)) {
            return false;
        }
    }

    return true;
}

bool isOver18(const string& date) {
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    time_t t = time(0);
    struct tm now;
    localtime_s(&now, &t);

    int currentYear = now.tm_year + 1900;
    int currentMonth = now.tm_mon + 1;
    int currentDay = now.tm_mday;

    int age = currentYear - year;
    if (currentMonth < month || (currentMonth == month && currentDay < day)) {
        age--;
    }

    return age >= 18;
}

bool isValidCNIC(const string& cnic) {
    regex cnicPattern("^\\d{5}-\\d{7}-\\d$|^\\d{13}$");
    return regex_match(cnic, cnicPattern);
}

bool authenticateUser(const string& filename, const string& username, const string& password) {
    ifstream file(filename);
    string storedUsername, storedPassword;
    if (file.is_open()) {
        while (file >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}

void signUpWadiah(const string& filename, const string& userType) {
    string username, password, fname, lname, dob, nationality, acctype, CNIC;
    float balance = 0;

    system("cls");
    cout << "Enter your First Name: ";
    cin >> fname;
    cout << "Enter your Last Name: ";
    cin >> lname;

    do {
        cout << "Enter your Date of Birth (dd-mm-yyyy): ";
        cin >> dob;
        if (!isValidDate(dob)) {
            cout << RED << "Invalid date format. Please try again." << RESET << endl;
        }
        else if (!isOver18(dob)) {
            cout << RED << "You must be at least 18 years old to sign up." << RESET << endl;
        }
    } while (!isValidDate(dob) || !isOver18(dob));

    do {
        cout << "Enter your CNIC: ";
        cin >> CNIC;
        if (!isValidCNIC(CNIC)) {
            cout << RED << "Invalid CNIC format. Please try again." << RESET << endl;
        }
    } while (!isValidCNIC(CNIC));

    cout << "Enter your Nationality: ";
    cin >> nationality;

    do {
        cout << "Enter Username (must start with a letter): ";
        cin >> username;
        if (!isValidUsername(username)) {
            cout << RED << "Username must start with a letter. Please try again." << RESET << endl;
        }
        else if (isUsernameTaken(filename, username)) {
            cout << RED << "Username is already taken. Please choose another one." << RESET << endl;
        }
    } while (!isValidUsername(username) || isUsernameTaken(filename, username));

    do {
        cout << "Enter Password (must be at least 8 characters long and contain a special character): ";
        password = "";
        char ch;
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            }
            else {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;
        if (!isValidPassword(password)) {
            cout << RED << "Password must be at least 8 characters long and contain a special character." << RESET << endl;
        }
    } while (!isValidPassword(password));

    cout << "Enter amount to deposit: (greater than 200) ";
    cin >> balance;
    while (balance < 200) {
        cout << RED << "Enter Balance Greater than 200! " << RESET << endl;
        cout << "Enter again: ";
        cin >> balance;
    }
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << username << " " << password << endl;
        file.close();
    }
    else {
        cout << RED << "Unable to open file" << RESET << endl;
    }

    WadiahAccount wadiahAccount;
    wadiahAccount.setAccountNumber(wadiahAccount.generateAccountNumber());
    wadiahAccount.updateBalance(balance);
    wadiahAccount.updateBalanceInFile(username);

    cout << GREEN << "Wadiah Account successfully created." << RESET << endl;
}

void displayRandomHadith() {
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % 5;
    string hadiths[] = {
        "The best among you is the one who doesn’t harm others with his tongue and hands.",
        "A good man treats women with honor.",
        "Seek knowledge from cradle to the grave.",
        "The best of houses is the house where an orphan gets love and kindness.",
        "Do not waste water even if you perform your ablution on the banks of an abundantly-flowing river."
    };
    cout << GREEN << "Hadith: " << hadiths[randomIndex] << RESET << endl;
}

void handleWadiahAccount(const string& username) {
    WadiahAccount wadiahAccount;
    wadiahAccount.loadBalanceFromFile(username);

    int choice;
    do {
        cout << "1. Deposit\n2. Complain\n3. Display Balance\n4. Deduct Zakat\n5. Give Hibah\n6. Transfer Money\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            float amount;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            wadiahAccount.deposit(amount);
            wadiahAccount.updateBalanceInFile(username);
            break;
        }
        case 2: {
            handleComplaint(username);
            break;
        }
        case 3:
            wadiahAccount.displayBalance();
            break;
        case 4:
            wadiahAccount.deductZakat();
            break;
        case 5: {
            float amount;
            cout << "Enter Hibah amount: ";
            cin >> amount;
            wadiahAccount.giveHibah(amount);
            wadiahAccount.updateBalanceInFile(username);
            break;
        }
        case 6: {
            string recipientUsername;
            float amount;
            cout << "Enter recipient username: ";
            cin >> recipientUsername;
            cout << "Enter amount to transfer: ";
            cin >> amount;
            if (wadiahAccount.transferMoney(recipientUsername, amount)) {
                wadiahAccount.updateBalanceInFile(username);
            }
            break;
        }
        case 7:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << RED << "Invalid choice. Please try again." << RESET << endl;
            break;
        }
    } while (choice != 7);
}

void handleComplaint(const string& username) {
    string complaint;
    cout << "Enter your complaint: ";
    cin.ignore();
    getline(cin, complaint);

    ofstream file("Complaint.txt", ios::app);
    if (file.is_open()) {
        file << "DATE: " << __DATE__ << endl;
        file << "Username: " << username << endl;
        file << "Complaint: " << complaint << endl;
        
        file.close();
    }
    else {
        cout << RED << "Unable to open file" << RESET << endl;
    }

    cout << GREEN << "Your complaint has been recorded. Thank you." << RESET << endl;
}
void assist(const string& username, string& contact) {
    string complaint;
    cout << "Enter your query: ";
    cin.ignore();
    getline(cin, complaint);

    ofstream file("Assist.txt", ios::app);
    if (file.is_open()) {
        file << "DATE: " << __DATE__ << endl;
        file << "Name: " << username << endl;
        file << "Query: " << complaint << endl;
        file << "Contact: " << contact << endl;
        file << "----------------------" << endl;
        file.close();
    }
    else {
        cout << RED << "Unable to open file" << RESET << endl;
    }

    cout << GREEN << "Your query has been recorded. Thank you." << RESET << endl;
}

void displayUserInformation(const string& username) {
    ifstream userFile(username + ".txt");
    if (userFile.is_open()) {
        string line;
        while (getline(userFile, line)) {
            cout << line << endl;
        }
        userFile.close();
    }
    else {
        cout << RED << "User information not found." << RESET << endl;
    }
}

void wadiahLogin(const string& filename) {
    string username, password;

    do {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        password = "";
        char ch;
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            }
            else {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;

        if (!authenticateUser(filename, username, password)) {
            cout << RED << "Invalid username or password. Please try again." << RESET << endl;
        }
    } while (!authenticateUser(filename, username, password));

    handleWadiahAccount(username);
}
void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else

#endif
}
int main() {
    Bank bank;
    
    bank.displayBankInfo();
    cout << "\t\t\t Please wait while we load your account...\n\n";
    bank.showLoading(5);
    cout << GREEN << "Please select an option to sign in: " << RESET << endl;
    cout << "1. Employee Sign In" << endl;
    cout << "2. Customer Portal" << endl;
    cout << "3. Quit" << endl;

    int option;
    cin >> option;

    Employee employee;
    Customer customer;
    system("cls");
    while (option != 4) {
        switch (option) {
        case 1:
            while (employee.signInEmployee("Employee.txt")) {
                int employeeChoice;
                do {
                    cout << BLUE << "*************************************" << endl;
                    cout << "*          " << RED << "Employee Menu" << BLUE << "            *" << endl;
                    cout << "*************************************" << endl;
                    cout << BLUE << "*  1. " << RED << "Check Salary" << BLUE << "                   *" << endl;
                    cout << BLUE << "*  2. " << GREEN << "Check Requests" << BLUE << "                 *" << endl;
                    cout << BLUE << "*  3. " << YELLOW << "Check Notifications" << BLUE << "            *" << endl;
                    cout << BLUE << "*  4. " << CYAN << "Inform" << BLUE << "                         *" << endl;
                    cout << BLUE << "*  5. " << MAGENTA << "Modify Sign In" << BLUE << "                 *" << endl;
                    cout << BLUE << "*  7. " << RED << "Check Complains" << BLUE << "                *" << endl;
                    cout << BLUE << "*  6. " << GREEN << "Exit" << BLUE << "                           *" << endl;
                    cout << "*************************************" << RESET << endl;
                    cout << "Enter your choice: ";
                    cin >> employeeChoice;
                   

                    switch (employeeChoice) {
                    case 1:
                        system("cls");
                        employee.CheckSalary();
                        cout << endl;
                        cout << endl;
                        cout << endl;
                        cout << endl;
                        break;
                    case 2:
                        system("cls");
                        employee.CheckRequests();
                        cout << endl;
                        cout << endl;
                        cout << endl;
                        
                        break;
                    case 3:
                        system("cls");
                        employee.CheckNotification();
                        break;
                    case 4:
                        system("cls");
                        employee.Inform();
                        break;
                    case 5:
                        system("cls");
                        employee.modifySignIn("Employee.txt");
                        break;
                    case 6:
                        system("cls");
                        cout << "Exiting Employee Menu." << endl;
                        break;
                    case 7:
                        system("cls");
                        employee.CheckComplains();
                        break;
                       
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
                } while (employeeChoice != 8);
                break;
            }
            break;
        case 2:
        {
            string filename = "Wadiah.txt";
            int choice;

            do {
                cout << "\t\t\t" << BLUE << "****************************" << endl;
                cout << "\t\t\t" << BLUE << "* " << RED << "1. " << GREEN << "Sign Up" << BLUE << "               *" << endl;
                cout << "\t\t\t" << BLUE << "* " << RED << "2. " << YELLOW << "Login" << BLUE << "                 *" << endl;
                cout << "\t\t\t" << BLUE << "* " << RED << "3. " << CYAN << "Assistance" << BLUE << "            *" << endl;
                cout << "\t\t\t" << BLUE << "* " << RED << "4. " << MAGENTA << "Exit" << BLUE << "                 *" << endl;
                cout << "\t\t\t" << BLUE << "****************************" << RESET << endl;
                cout << "\t\t\tEnter your choice: ";
                
                cin >> choice;

                switch (choice) {
                case 1:
                    signUpWadiah(filename, "Wadiah");
                    break;
                case 2:
                    wadiahLogin(filename);
                    break;
                case 3: {
                    string namee;
                    string cc;
                    cout << "Enter your username: ";
                    cin >> namee;
                    cout << "Enter your contact Info: ";
                    cin >> cc;
                    assist(namee, cc);

                    break;
                }
                case 4:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << RED << "Invalid choice. Please try again." << RESET << endl;
                    break;
                }
            } while (choice != 4);

        }
        case 4:
            cout << "Thank you for using our bank services. Goodbye!" << endl;
            return 0; 
        default:
            cout << "Invalid option. Please try again." << endl;
            system("pause"); 
            break;
        }
    }

    return 0;
}


