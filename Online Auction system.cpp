#include<iostream>
#include<conio.h>
#include<Windows.h>
#include <fstream>
#include<vector>

#include <ctime>
#include<string>
#include<string.h>

#include <chrono>
#include <thread>
class user;
class buyer;
class seller;
class item;
using namespace std;
class user {
protected:
	string name;
	string passward;
public:
	user() {
		cout << "Enter your name: ";
		cin >> name;
		cout << "\nEnter the Passward: ";
		cin >> passward;

	}
	virtual void adduser(string status) {
		fstream a(status + ".txt", ios::app);
		a << name << endl;
		a << passward << endl;
		a << status << endl;
		a << "--------------------------------------------\n\n";

	}

};
class buyer :public user {
	string status_;
public:
	buyer() :user() {
		status_ = "buyer";
		adduser(status_);
	}
	buyer(bool b) :user() {


	}

};

class seller :public user {
	string status;
public:
	seller() :user() {
		status = "seller";
		adduser(status);
	}
	seller(bool s) {

	}
	string setsellername() {
		return name;

	}
	bool confirmseller() {
		cout << "\nConfirm seller";
		string s, p;
		fstream file("seller.txt", ios::in);
		while (!file.eof()) {
			file >> s >> p;
			if (s == name) {
				if (p == passward) {
					return true;
				}
				else {
					cout << "\nWrong Passward";
					return false;
				}


			}
			else {
				cout << "User not Exist.";
				return false;
			}
		}
	}
};
class Auction {
	string name;
	string passward;
	string product;
	string startprice;
	double endprice;
public:
	friend class item;
	void setendprice(double p) {
		endprice = p;
	}
	void newprice(string p) {
		startprice = p;
	}
	string getprice() {
		return startprice;
	}
	bool employlogin() {
		cout << "\nEnter your name: ";
		cin >> name;
		cout << "\nEnter your Passward: ";
		cin >> passward;
		fstream file("employ.txt");
		string f_name, f_pass;
		file>>f_name>>f_pass;
		if (name == f_name && passward == f_pass) {
			cout << "\nLogin Sccuessfully.";
			system("pause");
			return true;


		}
		else {
			cout << "\nWrong Name or passward.";
			return false;
		}



	}
	void ask() {
		string start_price;
		  string filename = "item.txt";
		  ifstream file(filename);

		if (!file.is_open()) {
			  cerr << "Unable to open file: " << filename <<   endl;
			return;
		}

		  cout << "\nProducts For Auction available:\n";
		  string content((  istreambuf_iterator<char>(file)), (  istreambuf_iterator<char>()));
		  cout << content <<   endl;

	
		file.clear();
		file.seekg(0,   ios::beg);

		int lines_to_read = 3;
		bool item_found = false;
		  string item_name;
		  cout << "\nEnter the Name of the Product for auction: ";
		  cin >> item_name;

		  string line;
		  string line1, line2, line3; // Declare variables to store the three lines
		  
		  while (getline(file, line)) {
			  if (!item_found && line == item_name) {
				  item_found = true;
				  cout << "Item found:\n" << line << endl;
				  product = line;
			  }
			  else if (item_found && lines_to_read > 0) {
				  
				  if (lines_to_read == 3) {
					  line1 =line ;
				  }
				  else if (lines_to_read == 2) {
					  line2 = line;
				  }
				  else if (lines_to_read == 1) {
					  line3 = line;
				  }
				  lines_to_read--;
			  }
		  }

		  file.close();

		  if (!item_found) {
			  cout << "Item not found in the file." << endl;
		  }
		  else {
			  cout << "\nFollowing lines are after the found item:\n";
			  cout << line1 << endl;
			  cout << line2 << endl;
			  cout << line3 << endl;
		  }
		  newprice(line1);
		 // product = line;

		system("pause");

	

	}
	void product_display() {
		cout << "\nAuction For " << product;
		cout << "\nStarting Price " << startprice;
	}
	void getbuyerinfo() {
		string name, passward;
		cout << "\nEnter your name: ";
		cin >> name;
		cout << "\nEnter Your Passward";
		cin >> passward;
		fstream file("buyer.txt");
		if (!file.is_open()) {
			std::cerr << "Error opening file: "<< std::endl;
			
		}

		
	
	

		std::string nameInFile;
		bool found = false;
		while (std::getline(file, nameInFile)) {
			if (nameInFile == name) {
				found = true;
				break;
			}
		}

		file.close();

		if (!found) {
			std::cout << "Name not found in the file." << std::endl;
			cout << "\nAdd you as a Buyer(y/n).";
			char ch;
			cin >> ch;
			if (ch == 'y') {
				buyer b;
				char ch;
				cout << "\n Do you Confirm the Product you win in Auction(y/n).";
				cin >> ch;
				if (ch == 'y') {
					removeproduct(product);
				}
				else {
					cout << "\nCancelled";
					
				}





			}
			else {
				cout << "Auction is consider as a Invalid. It would Held Again for the Product: " << product;
			}
		}
		else {
			removeproduct(product);
		}
		


	}
	void removeproduct(string productn) {
		string filename = "item.txt";
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "Error opening file: " << filename << std::endl;
			return;
		}

		std::vector<std::string> fileContents;
		std::string line;
		while (std::getline(file, line)) {
			fileContents.push_back(line);
		}
		file.close();

		int startLine = -1;
		
		for (size_t i = 0; i < fileContents.size(); i += 4) {
			if (fileContents[i] == productn) {
				startLine = i;
				break;
			}
		}

		if (startLine == -1) {
			std::cout << "Product not found in the file." << std::endl;
			return;
		}

	
		fileContents.erase(fileContents.begin() + startLine, fileContents.begin() + startLine + 4);

		
		std::ofstream outFile(filename);
		if (!outFile.is_open()) {
			std::cerr << "Error opening file for writing: " << filename << std::endl;
			return;
		}

		for (const auto& line : fileContents) {
			outFile << line << std::endl;
		}
		outFile.close();

		std::cout << "Product deleted successfully." << std::endl;

	}
};

class item {
	string items;
	int startprice;
public:
	friend class Auction;
	void addItem() {
		seller s(false);
		cout << "\nEnter the Item to add: ";
		cin >> items;
		cout << "\n Enter the Starting Price: ";
		cin >> startprice;
		if (s.confirmseller()) {
			
			fstream file("item.txt",ios::app);
			file << items << endl << startprice << endl << s.setsellername()<<endl<<"---------";
			file.close();
			cout << "\nItme added";

		}
	}
	void viewItem() {

		  ifstream file("item.txt");
		if (!file.is_open()) {          
			  cerr << "Unable to open file" <<   endl;
			return;
		}

		
		  string content((  istreambuf_iterator<char>(file)), (  istreambuf_iterator<char>()));
		file.close();  

		
		  cout << content <<   endl;

	}
};
int main() {

	
	int ch;
	cout << "1. for Add a buyer\n2. for add a Seller\n 3.for Add a Item .\n4.View the Items Availibale for Auction\n5.To Start a Auction. ";
	cin >> ch;
	if (ch == 1) {
		buyer b;
	}
	else if (ch == 2) {
		seller s;
	}
	else if (ch == 3) {
		item Itme;
		Itme.addItem();

	}
	else if (ch == 4) {
		item itme;
		itme.viewItem();
	}
	else if (ch == 5) {
		
		Auction a;
		if (a.employlogin()) {
			a.ask();
		}
		clock_t start = clock();

		int i = 5;
		
		system("cls");
		while (i >= 0) {

			if (_kbhit()) {

				string p;
				  cin >> p;
				if (a.getprice() < p) {
					a.newprice(p);
					i = 5;
				}
				else
					cout << "Price Must be Greater than " << a.getprice();
				  this_thread::sleep_for(  chrono::milliseconds(1000));

				a.product_display();

			}

			if (difftime(clock(), start) / CLOCKS_PER_SEC >= 1) {
				system("cls");
				a.product_display();

				  cout << "\n\nTimer: " << i << " seconds remaining" <<   endl;
				cout << "\nAdd new Price";
				i--;
				start = clock();
			}

			  this_thread::sleep_for(  chrono::milliseconds(100));

		}
		cout << "\n The buyer with the price:"<<a.getprice()<<"Wins this auction.\n Now please enter you details:\n";
		a.getbuyerinfo();
	}
	else
		cout << "\nWrong choice.";
	
	
	
	
	



}