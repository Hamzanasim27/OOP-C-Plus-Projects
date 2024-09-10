#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
#include<cstdlib>
using namespace std;
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char choose;
int maxscore = 100;
string username;
string password = "";



void intro()
{
	cout << ANSI_COLOR_CYAN;

	cout << "\n\n\n\n\n\t\t\t\t                WELCOME TO ";
	cout << "\n\n\n\t\t\t\t          QUIZ MANAGMENT SYSTEM";

	cin.get();
}




class  quiz
{
protected:
	string name;
	string regno;
	string quizName;
	string questions[20];
	string options[20][4];
	int correctAnswers[20]; 
	int numQuestions;

public:

quiz() : numQuestions(0) {}
quiz(const string& quizname) : quizName(quizname + ".txt"), numQuestions(0) {}


virtual ~quiz() {};



	void writequiz() {
		string quizname;
		cout << "\nEnter the name of quiz: ";
		getline(cin, quizname);
		quizName = quizname + ".txt";

		ofstream writequiz(quizName);
		if (!writequiz.is_open()) {
			cout << "Failed to open file." << endl;
			return;
		}

		cout << "\nHow many questions does this test contain? ";
		cin >> numQuestions;
		cin.ignore();

		for (int i = 0; i < numQuestions; i++) {
			cout << "Enter Question no " << i + 1 << " = ";
			getline(cin, questions[i]);

			for (int j = 0; j < 4; j++) {
				cout << "Enter option " << j + 1 << ": ";
				getline(cin, options[i][j]);
			}

			cout << "Enter the number of the correct answer (1-4): ";
			cin >> correctAnswers[i];
			correctAnswers[i]--;
			cin.ignore();

			writequiz << "Question " << i + 1 << ": " << questions[i] << endl;
			for (int j = 0; j < 4; j++) {
				writequiz << "Option " << j + 1 << ": " << options[i][j] << endl;
			}
			writequiz << "Correct Answer: " << correctAnswers[i] + 1 << endl;
		}

		writequiz.close();
		cout << "Quiz saved successfully." << endl;
	}

	void loadQuiz(const string& quizname) {
		ifstream readquiz(quizname + ".txt");
		if (!readquiz.is_open()) {
			cout << "Failed to open quiz file." << endl;
			return;
		}

		numQuestions = 0;
		string line;
		while (getline(readquiz, line)) {
			if (line.find("Question ") == 0) {
				questions[numQuestions] = line.substr(line.find(": ") + 2);

				for (int i = 0; i < 4; i++) {
					getline(readquiz, line);
					options[numQuestions][i] = line.substr(line.find(": ") + 2);
				}

				getline(readquiz, line);
				correctAnswers[numQuestions] = stoi(line.substr(line.find(": ") + 2)) - 1;

				numQuestions++;
			}
		}

		readquiz.close();
	}


	char calculateGrade(int score, int totalQuestions) {
		float percentage = ((float)score / totalQuestions) * 100;

		if (percentage >= 90) return 'A';
		if (percentage >= 80) return 'B';
		if (percentage >= 70) return 'C';
		if (percentage >= 60) return 'D';
		if (percentage >= 50) return 'E';
		return 'F';
	}




	void attemptQuiz() {
		cout << "\n=============================================\n";
		cout << "              ENTER YOUR PERSONAL DETAILS              \n";
		cout << "=============================================\n";
		cout << "Enter your name: ";
		getline(cin, name);
		cin.ignore();
		cout << "Enter your registration no: ";
		getline(cin, regno);
		cout << "\n=============================================\n";
		cout << "              DETAILS ENTERED SUCCESSFULLY              \n";
		cout << "=============================================\n";
		string quizname;
		cout << "\nEnter the name of quiz to attempt: ";
		getline(cin, quizname);
		system("cls");
		loadQuiz(quizname);

		int score = 0;
		for (int i = 0; i < numQuestions; i++) {
			cout << "\nQuestion " << i + 1 << ": " << questions[i] << endl;
			for (int j = 0; j < 4; j++) {
				cout << "Option " << j + 1 << ": " << options[i][j] << endl;
			}

			int userAns;
			cout << "Enter your answer (1-4): ";
			while (!(cin >> userAns) || userAns < 1 || userAns > 4) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a number between 1 and 4: ";
			}

			if (userAns - 1 == correctAnswers[i]) {
				cout << "Correct!" << endl;
				score++;
			}
			else {
				cout << "Incorrect. The correct answer was Option " << correctAnswers[i] + 1 << "." << endl;
			}


		}
		cin.ignore();
		char grade = calculateGrade(score, numQuestions);
		cout << "\nQuiz attempted successfully!\n Your score in: " << quizname << " is:  " << score << "/" << numQuestions << endl;
		cout << "Your grade is: " << grade << endl;
		system("pause");

		ofstream reportFile(regno + quizname + ".txt", ios::app);
		if (!reportFile.is_open()) {
			cout << "Failed to open report file." << endl;
			return;
		}

		reportFile << "Quiz: " << quizname << endl;
		reportFile << "Score: " << score << "/" << numQuestions << endl;
		reportFile << "Grade: " << grade << endl;
		reportFile << "-----------------------------------" << endl;
		ofstream reporttFile(regno + ".txt", ios::app);
		reporttFile << "Quiz: " << quizname << endl;
		reporttFile << "Score: " << score << "/" << numQuestions << endl;
		reporttFile << "Grade: " << grade << endl;
		reporttFile << "-----------------------------------" << endl;
	}




	void modifyQuiz() {
		string quizname;
		cout << "\nEnter the name of the quiz to modify: ";
		getline(cin, quizname);
		quizname = quizname + ".txt";

		ifstream readQuiz(quizname);
		if (!readQuiz.is_open()) {
			cout << "Failed to open file." << endl;
			return;
		}

		string tempFileName = "temp_" + quizname;
		ofstream tempFile(tempFileName);
		if (!tempFile.is_open()) {
			cout << "Failed to open temporary file for writing." << endl;
			return;
		}

		string line;
		int questionNumber, currentQuestion = 1;

		cout << "\nExisting quiz content:\n";
		while (getline(readQuiz, line)) {
			cout << line << endl;
		}
		readQuiz.close();
		readQuiz.open(quizname);

		cout << "\nEnter the question number you want to modify: ";
		while (!(cin >> questionNumber) || questionNumber < 1) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid question number. Please enter a number between 1 and " << numQuestions << ": ";
		}


		while (getline(readQuiz, line)) {
			if (line.find("Question " + to_string(currentQuestion) + ":") == 0) {
				if (currentQuestion == questionNumber) {
					string newQuestion;
					string newOptions[4];
					cin.ignore();
					cout << "Enter new text for Question " << questionNumber << ": ";
					getline(cin, newQuestion);

					tempFile << "Question " << questionNumber << ": " << newQuestion << endl;

					for (int j = 0; j < 4; j++) {
						cout << "Enter new text for Option " << j + 1 << ": ";
						getline(cin, newOptions[j]);
						tempFile << "Option " << j + 1 << ": " << newOptions[j] << endl;
					}

					cout << "Enter new correct answer (1-4): ";
					int newCorrectAnswer;
					while (!(cin >> newCorrectAnswer) || newCorrectAnswer < 1 || newCorrectAnswer > 4) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input. Please enter a number between 1 and 4: ";
					}
					cin.ignore(); // Consume newline character left in the buffer

					correctAnswers[questionNumber - 1] = newCorrectAnswer - 1; // Adjust to 0-based index
					tempFile << "Correct Answer: " << correctAnswers[questionNumber - 1] + 1 << endl;
				}
				else {
					tempFile << line << endl; // Copy unchanged lines to temp file
					for (int i = 0; i < 4; ++i) {
						getline(readQuiz, line); // Skip options and correct answer lines
						tempFile << line << endl; // Copy skipped lines to temp file
					}
				}
				++currentQuestion;
			}
			else {
				tempFile << line << endl; // Copy unchanged lines to temp file
			}
		}

		readQuiz.close();
		tempFile.close();

		remove(quizname.c_str());       // Delete original quiz file
		rename(tempFileName.c_str(), quizname.c_str()); // Rename temp file to original quiz file

		cout << "Quiz modified successfully." << endl;
	}
};
class student : public quiz
{
private:
	string readquiz;

	string classs;
	string courses;
	string difficulty_level = "0";
	int current_score;
	int updated_score;
	string quiz_id;
	int numQuizzesTaken = 0;
public:
	void Sentry_menu()
	{
		system("cls");
		cout << "\n\n\n\tSTUDENT MENU";
		cout << "\n\n\t1. ATTEMPT QUIZ";
		cout << "\n\n\t2. CHECK MARKS";
		cout << "\n\n\t3. VIEW NOTIFICATION";
		cout << "\n\n\t4. GIVE FEEDBACK";
		cout << "\n\n\t5. EXIT";
		cout << "\n\n\tPlease Enter Your Choice (1-4): ";

	}
	bool getSaccess()
	{
		system("cls");
		char ch;
		cout << "\n\n\t\t\tSTUDENT LOGIN\n\n";
		cout << "\n\tEnter your user name = ";
		cin.ignore();
		getline(cin, username);
		cout << "\n\tEnter your password = ";
		ch = _getch();
		while (ch != 13) {
			password.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		if (username == "student" && password == "password") {
			cout << ANSI_COLOR_GREEN << "\n\n\n\t\t\t\t\tAccess Granted...\n\n\t\t\t\t\t";
			return true;
		}

		else {
			cout << ANSI_COLOR_RED << "\n\n\n\t\t\t\t\tInvalid Username or Password...\n\n\t\t\t\t\t";
			system("pause");
			return false;
		}
	}



	void giveSFeedback() {
		string feedbackFileName = "STUDENT_feedback.txt";
		ofstream feedbackFile(feedbackFileName, ios::app);
		if (!feedbackFile.is_open()) {
			cout << "Failed to open feedback file." << endl;
			return;
		}

		string feedback;
		cin.ignore();
		cout << "enter your name" << endl;
		getline(cin, name);
		cin.ignore();
		cout << "\nEnter your feedback: ";
		getline(cin, feedback);
		system("pause");
		feedbackFile << "Student: " << name << endl;
		feedbackFile << "Feedback: " << feedback << endl;
		feedbackFile << "--------------------------" << endl;
		system("pause");
		feedbackFile.close();
		cout << "\nFeedback submitted successfully." << endl;
	}



	void checkMarks() {
		string regno, quizname;
		cout << "Enter your registration number: ";
		getline(cin, regno);
		cout << "Enter the quiz name: ";
		getline(cin, quizname);

		string filename = regno + quizname + ".txt";
		ifstream reportFile(filename);
		if (!reportFile.is_open()) {
			cout << "Failed to open report file or no record found." << endl;
			return;
		}

		string line;
		cout << "\nYour marks for the quiz '" << quizname << "':\n";
		while (getline(reportFile, line)) {
			cout << line << endl;
		}
		cin.ignore();

		reportFile.close();
	}


	void displayNotifications() {
		ifstream inFile("notifications.txt");
		string line;
		cout << "\n========== Notifications ==========\n";
		if (inFile.is_open()) {
			while (getline(inFile, line)) {
				size_t pos = line.find("|");
				string date = line.substr(0, pos);
				string message = line.substr(pos + 1);
				cout << date << ": " << message << endl;
			}
			system("pause");
		}
		else {
			cout << "Unable to open file for reading." << endl;
		}
	}
};





class teacher :public quiz
{
protected:
	string name;
	int choose;
	string subject;
	int marks;
	int rollno;

	string reportName;
public:
	bool getTaccess()
	{
		system("cls");
		char ch;
		cout << "\n\n\t\t\tTEACHER LOGIN\n\n";
		cout << "\n\tEnter your user name = ";
		cin.ignore();
		getline(cin, username);
		cout << "\n\tEnter your password = ";
		ch = _getch();
		while (ch != 13) {
			password.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		if (username == "admin" && password == "password") {
			cout << ANSI_COLOR_GREEN << "\n\n\n\t\t\t\t\tAccess Granted...\n\n\t\t\t\t\t";
			cout << "    ";
			return true;
		}
		else {
			cout << ANSI_COLOR_RED << "\n\n\n\t\t\t\t\tInvalid Username or Password...\n\n\t\t\t\t\t";
			system("pause");
			return false;
		}
	}
	void Tentry_menu()
	{

		system("cls");
		cout << "\n\n\n\tENTRY MENU";
		cout << "\n\n\t1.MAKE QUIZ";
		cout << "\n\n\t2.MODIFY QUIZ ";
		cout << "\n\n\t3.CREATE STUDENT REPORT";
		cout << "\n\n\t4.DISPLAY STUDENTS REPORT";
		cout << "\n\n\t5.SEARCH STUDENT REPORT";
		cout << "\n\n\t6.WRITE NOTIFICATION";
		cout << "\n\n\t7.VIEW NOTIFICATION";
		cout << "\n\n\t8.GIVE FEEDBACK";
		cout << "\n\n\t9.EXIT";
		cout << "\n\n\tPlease Enter Your Choice (1-8) ";

	}

	void getdata()
	{
		cout << "\nEnter The roll number of student ";
		cin >> rollno;
		cout << "\n\nEnter The Name of student ";
		cin.ignore();
		getline(cin, name);
		cin.ignore();
	}
	void makereport()
	{

		cout << "Enter the name of the report file: ";
		getline(cin, reportName);
		reportName = reportName + ".txt";

		ofstream reportFile(reportName);
		if (!reportFile.is_open()) {
			cout << "Failed to open file." << endl;
			return;
		}

		int numStudents;
		cout << "Enter the number of students: ";
		cin >> numStudents;
		cin.ignore();
		for (int i = 0; i < numStudents; ++i) {
			getdata();

			reportFile << "Name: " << name << endl;
			reportFile << "Roll Number: " << rollno << endl;
			reportFile << "--------------------------" << endl;
		}

		reportFile.close();
		cout << "\n\n\tReport created successfully." << endl;
	}


	void displayAllReports() {
		for (int regNo = 1; regNo <= 7; ++regNo) {
			string regStr = "bai2330" + (regNo < 7 ? "0" + to_string(regNo) : to_string(regNo));
			string reportName = regStr + ".txt";

			ifstream reportFile(reportName);
			if (!reportFile.is_open()) {
				cout << "Failed to open file: " << reportName << endl;
				continue;
			}

			string line;
			cout << "\nDisplaying report for registration number " << regStr << ":\n\n";
			while (getline(reportFile, line)) {
				cout << line << endl;
			}

			reportFile.close();
			cout << "-----------------------------------\n";
		}
		cout << "\nPress any key to continue...";
		_getch();
	}




	void searchStudentReport() {
		cout << "Enter the name of the report file to search: ";
		getline(cin, reportName);
		reportName = reportName + ".txt";
		ifstream reportFile(reportName);
		if (!reportFile.is_open()) {
			cout << "Failed to open file." << endl;
			return;
		}

		int searchRollNo;
		cout << "Enter the roll number of the student to search: ";
		cin >> searchRollNo;

		string line;
		bool found = false;
		while (getline(reportFile, line)) {
			if (line.find("Roll Number: " + to_string(searchRollNo)) != string::npos) {
				found = true;
				cout << "\nStudent Report Found:\n";
				cout << line << endl;
				for (int i = 0; i < 6; ++i) {
					getline(reportFile, line);
					cout << line << endl;
				}
			}
		}


		if (!found) {
			cout << "No report found for roll number " << searchRollNo << "." << endl;
		}

		reportFile.close();
		cout << "\nPress any key to continue...";
		_getch();
	}
	void giveFeedback() {
		string feedbackFileName = "teacher_feedback.txt";
		ofstream feedbackFile(feedbackFileName, ios::app);
		if (!feedbackFile.is_open()) {
			cout << "Failed to open feedback file." << endl;
			return;
		}

		string feedback;
		cin.ignore();
		cout << "enter your name" << endl;
		getline(cin, name);
		cin.ignore();
		cout << "\nEnter your feedback: ";
		getline(cin, feedback);
		system("pause");
		feedbackFile << "Teacher: " << name << endl;
		feedbackFile << "Feedback: " << feedback << endl;
		feedbackFile << "--------------------------" << endl;
		system("pause");
		feedbackFile.close();
		cout << "\nFeedback submitted successfully." << endl;
	}



	void writeNotification() {
		string message, date;
		cout << "Enter notification message: ";
		cin.ignore();
		getline(cin, message);
		cout << "Enter date (YYYY-MM-DD): ";
		getline(cin, date);

		ofstream outFile("notifications.txt", ios::app);
		if (outFile.is_open()) {
			outFile << date << "|" << message << endl;
			outFile.close();
			cout << "Notification saved successfully." << endl;
		}
		else {
			cout << "Unable to open file for writing." << endl;
		}
	}


	void viewNotifications() {
		ifstream inFile("notifications.txt");
		string line;
		cout << "\n========== Notifications ==========\n";
		if (inFile.is_open()) {
			while (getline(inFile, line)) {
				size_t pos = line.find("|");
				string date = line.substr(0, pos);
				string message = line.substr(pos + 1);
				cout << date << ": " << message << endl;
			}
			system("pause");
		}
		else
		{
			cout << "Unable to open file for reading." << endl;
		}

	}
};
int main()
{

	bool isStudentLoggedIn = false;
	bool isTeacherLoggedIn = false;
	int choice;
	char ch;
	intro();
	teacher t1;
	quiz q1;
	student s1;
	do
	{
		system("cls");
		intro();
		system("cls");
		cout << ANSI_COLOR_CYAN;
		cout << "\n\t\t\t\t=============================\n";
		cout << "\t\t\t\t      QUIZ MANAGEMENT SYSTEM      \n";
		cout << "\t\t\t\t=============================\n";
		cout << "\n\n\n\t\t\t\t\tLOGIN PANEL";
		cout << "\n\n\n\t\t\t\t1. ADMIN";
		cout << "\n\n\t\t\t\t2. STUDENT";
		cout << "\n\n\t\t\t\t3. EXIT\n";
		cout << "\n\t\t\t\tEnter your choice: ";
		cin >> ch;

		switch (ch)
		{
		case '1':
			if (t1.getTaccess())
			{
				isTeacherLoggedIn = true;
				do {
					t1.Tentry_menu();
					cin >> choice;
					system("cls");
					cin.ignore();
					switch (choice)
					{
					case 1:
						q1.writequiz();
						break;
					case 2:
						q1.modifyQuiz();
						break;
					case 3:
						t1.makereport();
						break;
					case 4:
						t1.displayAllReports();
						break;
					case 5:
						t1.searchStudentReport();
						break;
					case 6:
						t1.writeNotification();
						break;
					case 7:
						t1.viewNotifications();
						break;
					case 8:
						t1.giveFeedback();
						break;
					default:
						cout << "\a";
					}
				} while (choice != 9);
				isTeacherLoggedIn = false; 
			}
			break;

		case '2':
			if (s1.getSaccess()) {
				isStudentLoggedIn = true; 
				do {
					s1.Sentry_menu();
					cin >> choice;
					system("cls");
					cin.ignore();
					switch (choice)
					{
					case 1:
						q1.attemptQuiz();
						break;
					case 2:
						s1.checkMarks();
						break;
					case 3:
						s1.displayNotifications();
						break;
					case 4:
						s1.giveSFeedback();
						break;
					default:
						cout << "\a";
					}
				} while (choice != 5); 
				isStudentLoggedIn = false;  
			}
			break;

		case '3':
			break;

		default:
			cout << "\a";
		}
	} while (ch != '3');

	return 0;
}