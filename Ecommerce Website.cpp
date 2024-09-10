#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class user {
public:
    string username;
    string password;
    string email;
    string address;
    bool shoppingcart = false; // Initialize member variable
public:
    void login() {
        cout << "\t\t\t\t\t\t** ENTER YOUR DETAILS TO CONFIRM YOUR ORDER:** " << endl;
        cout << " Enter your name  ";
        cin.ignore();
        getline(cin, username);
        cout << " Enter your password  ";
        cin >> password;
        cin.ignore();
        cout << " enter your email address  ";
        getline(cin, email);
        ifstream infile("myfile.txt");
        if (infile.is_open()) {
            string file_username, file_password;
            while (infile >> file_username >> file_password) {
                if (file_username == username && file_password == password) {
                    cout << "Login successful.\n";
                    infile.close();
                }
            }
            infile.close();
        }

    }
    void browse_product() {
        cout << " Here you can find everything you need to buy" << endl;
        int choice;
        cout << " which type of product you want to browse" << endl;
        cout << " press 1 clothing and shoes" << endl;
        cout << " press 2 for electronics" << endl;
        cout << " press 3 for sports and outdoors" << endl;
        cout << " press 4 for toys and games" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            cout << " HERE YOU GO WITH ALL CLOTHING AND SHOES BRANDS OF " << endl;
            cout << " t-shirts \n  jeans \n  dresses \n  shoes \n  handbags" << endl;
            break;
        case 2:
            cout << " HERE YOU GO WITH ALL ELECTRONICS BRANDS OF " << endl;
            cout << " smart phones \n laptops \n televisions \n headphones \n smartwatches" << endl;
            break;
        case 3:
            cout << " HERE YOU GO WITH ALL SPORTS BRANDS OF " << endl;
            cout << " balls \n bats \n bicycles \n rackets \n camping stoves" << endl;
            break;
        case 4:
            cout << " HERE YOU GO WITH ALL TOYS AND GAMES " << endl;
            cout << " puzzles \n board games \n video games \n action figures \n educational toys" << endl;
            break;

        default:
            cout << " invalid input please enter ( 1 - 4 )" << endl;
            browse_product();
        }
    }

    void add_to_cart() {
        char n;
        string prd;
        //int a;
        cout << "\t\t\t\t\t\t ADD TO CART   \t\t\t\t " << endl;

        cout << "Do you want to add any product to cart (y/n)" << endl;
        cin >> n;
        if (n == 'y' || n == 'Y') {
            cout << "The product has been added to the cart successfully " << endl;
            shoppingcart = true;
        }
        else if (n == 'n' || n == 'N') {
            cout << "Enjoy browsing products" << endl;
            browse_product();
            add_to_cart();
        }
        else
        {
            cout << "Invalid input provided\n";
        }
    }
    void logout() {
        char c1;
        string user;
        string pass;
        cout << " do you want to logout (y/n)";
        cin >> c1;
        if (c1 == 'y' || c1 == 'Y') {
            cout << " Enter your name  ";
            cin >> user;
            cout << " Enter your password  ";
            cin >> pass;
            if (user == username && pass == password) {
                cout << " you are logged out successfully" << endl;
            }
            else {
                cout << "Enter correct password and username";
                logout();
            }
        }
        else {
            cout << " enjoy browsing products" << endl;
        }
    }
};
class product {
public:
    string name;
    int id;
    string brand;
    int price;
    int quantity;
    bool available;
    int sold_out;
    const int max_quantity;
    const int quantity_tshirts = 30;
    const int quantity_jeans = 30;
    const int quantity_dresses = 30;
    const int quantity_shoes = 30;
    const int quantity_handbags = 30;
    const int quantity_smartphones = 30;
    const int quantity_laptops = 30;
    const int quantity_televisions = 30;
    const int quantity_headphones = 30;
    const int quantity_smartwatches = 30;
    const int quantity_balls = 30;
    const int quantity_bats = 30;
    const int quantity_bicycles = 30;
    const int quantity_rackets = 30;
    const int quantity_camping_stoves = 30;
    const int quantity_puzzles = 30;
    const int quantity_boardgames = 30;
    const int quantity_videogames = 30;
    const int quantity_actionfigures = 30;
    const int quantity_educationaltoys = 30;



public:
    product()
        : name("Unknown"), id(0), brand("Unknown"), price(0), quantity(0), available(true), sold_out(0), max_quantity(0) {}
    product(string productName, int maxQty)
        : name(productName), id(0), price(0), quantity(maxQty), available(true), sold_out(0), max_quantity(maxQty) {}

    void check_item_availability() {
        if (quantity > 0) {
            if (quantity > max_quantity) {
                cout << "All " << max_quantity << " " << name << " are yours. We are now out of stock.\n";
            }
            else {
                cout << name << " is available\n";
                cout << "Sold out: " << sold_out << endl;
                cout << "Your " << name << ": " << quantity << endl;
                cout << "In stock: " << max_quantity - quantity << endl;
            }
        }
        else {
            cout << "OOPS! Enter a positive number !!!! \n";
        }
    }

    void display_availability() {
        cout << "Product: " << name << "\n";
        cout << "In stock: " << quantity << "\n\n";
    }

    void update_quantity(int newQuantity) {
        if (newQuantity >= 1 && newQuantity <= 100) {
            quantity = newQuantity;
            cout << "Stock updated for " << name << ": " << quantity << endl;
        }
        else {
            cout << "Invalid quantity. Please enter a value between 1 and 100.\n";
        }
    }
    void ask_product()

    {
        cout << " here you go with all kinds of products with 100% quality" << endl;
        cout << "\t\t\t\t\t\t * PRODUCT DETAILS*   \t\t\t\t " << endl;

        cout << " enter the name of product you want to buy: ";
        getline(cin, name);
        cout << " enter the brand of product you want to buy: ";
        getline(cin, brand);
        cout << " enter the number of product you want to buy: ";
        cin >> quantity;
        cout << endl;
    }
    void checkitem_availability()
    {
        if (name == "t_shirts")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_tshirts)
                {
                    cout << "All " << quantity_tshirts << " t-shirts are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "T-shirt is available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your t-shirts " << quantity << endl;
                    cout << "In stock " << quantity_tshirts - quantity << endl;
                }
            }
            else
            {
                cout << " OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "jeans")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_jeans)
                {
                    cout << "All " << quantity_jeans << " jeans are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Jeans are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your jeans " << quantity << endl;
                    cout << "In stock " << quantity_jeans - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "dresses")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_dresses)
                {
                    cout << "All " << quantity_dresses << " dresses are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Dresses are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your dresses " << quantity << endl;
                    cout << "In stock " << quantity_dresses - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "shoes")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_shoes)
                {
                    cout << "All " << quantity_shoes << " shoes are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Shoes are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your shoes " << quantity << endl;
                    cout << "In stock " << quantity_shoes - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "handbags")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_handbags)
                {
                    cout << "All " << quantity_handbags << " handbags are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Handbags are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your handbags " << quantity << endl;
                    cout << "In stock " << quantity_handbags - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "smart phones")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_smartphones)
                {
                    cout << "All " << quantity_smartphones << " smartphones are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Smartphones are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your smartphones " << quantity << endl;
                    cout << "In stock " << quantity_smartphones - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "laptops")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_laptops)
                {
                    cout << "All " << quantity_laptops << " laptops are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Laptops are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your laptops " << quantity << endl;
                    cout << "In stock " << quantity_laptops - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "televisions")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_televisions)
                {
                    cout << "All " << quantity_televisions << " televisions are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Televisions are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your televisions " << quantity << endl;
                    cout << "In stock " << quantity_televisions - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "headphones")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_headphones)
                {
                    cout << "All " << quantity_headphones << " headphones are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Headphones are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your headphones " << quantity << endl;
                    cout << "In stock " << quantity_headphones - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "smart watches")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_smartwatches)
                {
                    cout << "All " << quantity_smartwatches << " smartwatches are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Smartwatches are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your smartwatches " << quantity << endl;
                    cout << "In stock " << quantity_smartwatches - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "balls")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_balls)
                {
                    cout << "All " << quantity_balls << " balls are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Balls are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your balls " << quantity << endl;
                    cout << "In stock " << quantity_balls - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "bats")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_bats)
                {
                    cout << "All " << quantity_bats << " bats are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Bats are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your bats " << quantity << endl;
                    cout << "In stock " << quantity_bats - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "bicycles")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_bicycles)
                {
                    cout << "All " << quantity_bicycles << " bicycles are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Bicycles are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your bicycles " << quantity << endl;
                    cout << "In stock " << quantity_bicycles - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "rackets")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_rackets)
                {
                    cout << "All " << quantity_rackets << " rackets are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Rackets are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your rackets " << quantity << endl;
                    cout << "In stock " << quantity_rackets - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "camping stoves")
        {
            if (quantity > 0)
            {
                if (quantity > quantity_camping_stoves)
                {
                    cout << "All " << quantity_camping_stoves << " camping stoves are yours. We are now out of stock.\n";
                }
                else
                {
                    cout << "Camping stoves are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your camping stoves " << quantity << endl;
                    cout << "In stock " << quantity_camping_stoves - quantity << endl;
                }
            }
            else
            {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "puzzles") {
            if (quantity > 0) {
                if (quantity > quantity_puzzles) {
                    cout << "All " << quantity_puzzles << " puzzles are yours. We are now out of stock.\n";
                }
                else {
                    cout << "Puzzles are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your puzzles: " << quantity << endl;
                    cout << "In stock: " << quantity_puzzles - quantity << endl;
                }
            }
            else {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "board games") {
            if (quantity > 0) {
                if (quantity > quantity_boardgames) {
                    cout << "All " << quantity_boardgames << " board games are yours. We are now out of stock.\n";
                }
                else {
                    cout << "Board games are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your board games: " << quantity << endl;
                    cout << "In stock: " << quantity_boardgames - quantity << endl;
                }
            }
            else {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "video games") {
            if (quantity > 0) {
                if (quantity > quantity_videogames) {
                    cout << "All " << quantity_videogames << " video games are yours. We are now out of stock.\n";
                }
                else {
                    cout << "Video games are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your video games: " << quantity << endl;
                    cout << "In stock: " << quantity_videogames - quantity << endl;
                }
            }
            else {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == " action figures") {
            if (quantity > 0) {
                if (quantity > quantity_actionfigures) {
                    cout << "All " << quantity_actionfigures << " action figures are yours. We are now out of stock.\n";
                }
                else {
                    cout << "Action figures are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your action figures: " << quantity << endl;
                    cout << "In stock: " << quantity_actionfigures - quantity << endl;
                }
            }
            else {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else if (name == "educational toys") {
            if (quantity > 0) {
                if (quantity > quantity_educationaltoys) {
                    cout << "All " << quantity_educationaltoys << " educational toys are yours. We are now out of stock.\n";
                }
                else {
                    cout << "Educational toys are available\n";
                    cout << "Sold out " << sold_out << endl;
                    cout << "Your educational toys: " << quantity << endl;
                    cout << "In stock: " << quantity_educationaltoys - quantity << endl;
                }
            }
            else {
                cout << "OOPS! enter a positive number !!!! \n";
            }
        }
        else
        {
            cout << "Invalid item name or number.\n";
        }

    }
    void buy_product() {
        char ch;
        cout << "Do you want to buy any product";
        cin >> ch;
        if (ch == 'y' || ch == 'Y') {
            cout << "You chose " << quantity << " " << name << endl;
            cout << "Pay now " << endl;
        }
        else
        {
            cout << "Thanks for visiting\n";
        }
    }
    void set_name(int _name)
    {
        name = _name;
    }
    void set_quantity(int _quant)
    {
        quantity = _quant;
    }
    string get_name() {
        return name;
    }
    string getName()
    {
        return name;
    }
    string getbrand() {
        return brand;
    }
    int get_quantity() {
        return quantity;
    }
};

class Payment : public user {
private:
    string name;
    int quantity;
    int sold_out;
    int quantity_tshirts;
    int quantity_jeans;
    int quantity_dresses;
    int quantity_shoes;
    int quantity_handbags;
    int quantity_smartphones;
    int quantity_laptops;
    int quantity_televisions;
    int quantity_headphones;
    int quantity_smartwatches;
    int quantity_balls;
    int quantity_bats;
    int quantity_bicycles;
    int quantity_rackets;
    int quantity_camping_stoves;
    int quantity_puzzles;
    int quantity_boardgames;
    int quantity_videogames;
    int quantity_actionfigures;
    int quantity_educationaltoys;
    double price_tshirts;
    double price_jeans;
    double price_dresses;
    double price_shoes;
    double price_handbags;
    double price_smartphones;
    double price_laptops;
    double price_televisions;
    double price_headphones;
    double price_smartwatches;
    double total_price;
    double price_balls;
    double price_bats;
    double price_bicycles;
    double price_rackets;
    double price_camping_stoves;
    double price_puzzles;
    double price_board_games;
    double price_video_games;
    double price_action_figures;
    double price_educational_toys;

public:
    Payment(string n, int q) {
        name = n;
        quantity = q;
        sold_out = 0;
        quantity_tshirts = 30;
        quantity_jeans = 30;
        quantity_dresses = 30;
        quantity_shoes = 30;
        quantity_handbags = 30;
        quantity_smartphones = 30;
        quantity_laptops = 30;
        quantity_televisions = 30;
        quantity_headphones = 30;
        quantity_smartwatches = 30;
        quantity_puzzles = 30;
        quantity_boardgames = 30;
        quantity_videogames = 30;
        quantity_educationaltoys = 30;
        quantity_balls = 30;
        quantity_bats = 30;
        quantity_bicycles = 30;
        quantity_rackets = 30;
        quantity_camping_stoves = 30;

        price_tshirts = 20.0;
        price_jeans = 40.0;
        price_dresses = 50.0;
        price_shoes = 60.0;
        price_handbags = 70.0;
        price_smartphones = 500.0;
        price_laptops = 1000.0;
        price_televisions = 800.0;
        price_headphones = 100.0;
        price_smartwatches = 200.0;
        price_balls = 20.0;
        price_bats = 100.0;
        price_bicycles = 150.0;
        price_rackets = 20.0;
        price_camping_stoves = 10.0;
        price_puzzles = 20.0;
        price_board_games = 50.0;
        price_video_games = 80.0;
        price_action_figures = 30.0;
        price_educational_toys = 40.0;
        total_price = 0.0;
    }
    bool check_item_availability() {
        if (name == "t-shirts") {
            return process_payment(quantity_tshirts, price_tshirts, "t-shirts");
        }
        else if (name == "jeans") {
            return process_payment(quantity_jeans, price_jeans, "jeans");
        }
        else if (name == "dresses") {
            return process_payment(quantity_dresses, price_dresses, "dresses");
        }
        else if (name == "shoes") {
            return process_payment(quantity_shoes, price_shoes, "shoes");
        }
        else if (name == "handbags") {
            return process_payment(quantity_handbags, price_handbags, "handbags");
        }
        else if (name == "smartphones") {
            return process_payment(quantity_smartphones, price_smartphones, "smartphones");
        }
        else if (name == "laptops") {
            return process_payment(quantity_laptops, price_laptops, "laptops");
        }
        else if (name == "televisions") {
            return process_payment(quantity_televisions, price_televisions, "televisions");
        }
        else if (name == "headphones") {
            return process_payment(quantity_headphones, price_headphones, "headphones");
        }
        else if (name == "smartwatches") {
            return process_payment(quantity_smartwatches, price_smartwatches, "smartwatches");
        }
        else if (name == "balls") {
            return process_payment(quantity_balls, price_balls, "balls");
        }
        else if (name == "bats") {
            return process_payment(quantity_bats, price_bats, "bats");
        }
        else if (name == "bicycles") {
            return process_payment(quantity_bicycles, price_bicycles, "bicycles");
        }
        else if (name == "rackets") {
            return process_payment(quantity_rackets, price_rackets, "rackets");
        }
        else if (name == "camping_stoves") {
            return process_payment(quantity_camping_stoves, price_camping_stoves, "camping_stoves");
        }
        else if (name == "puzzles") {
            return process_payment(quantity_puzzles, price_puzzles, "puzzles");
        }
        else if (name == "board games") {
            return process_payment(quantity_boardgames, price_board_games, "board games");
        }
        else if (name == "video games") {
            return process_payment(quantity_videogames, price_video_games, "video games");
        }
        else if (name == "educational toys") {
            return process_payment(quantity_educationaltoys, price_educational_toys, "educational toys");
        }
        else if (name == "action figures") {
            return process_payment(quantity_actionfigures, price_action_figures, "action figures");
        }
        else {
            cout << "Invalid item name.\n";
            return false;
        }
    }
    bool process_payment(int& quantity_available, double price, const string& product_name) {
        if (quantity_available > 0) {
            if (quantity > quantity_available) {
                cout << "All " << quantity_available << " " << product_name << " are yours. We are now out of stock.\n";
                print_payment_slip(quantity_available, price, product_name);
                total_price += quantity_available * price;
                quantity_available = 0;
                return true;
            }
            else {
                cout << product_name << " are available\n";
                cout << "Sold out " << sold_out << endl;
                cout << "Your " << product_name << " " << quantity << endl;
                cout << "In stock " << quantity_available - quantity << endl;
                print_payment_slip(quantity, price, product_name);
                total_price += quantity * price;
                quantity_available -= quantity;
                return true;
            }
        }
        else {
            cout << "Oops! Out of stock.\n";
            return false;
        }
    }

    void print_payment_slip(int quantity, double price, const string& product_name) {
        double total = quantity * price;
        cout << "\t\t\t\t\t\t * PAYMENT SLIP*   \t\t\t\t " << endl;
        cout << "Product: " << product_name << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Single piece Price: $" << price << endl;
        cout << "Total Price: $" << total << endl;
        ofstream outfile("myfile.txt", ios::app);
        if (outfile.is_open()) {
            outfile << price << endl;
            outfile << total << "\n";
            outfile.close();
        }
        else {
            cout << "Error opening file for writing.\n";
        }
    }
    double getTotalPrice() {
        return total_price;
    }
};

class Order : public user {
private:
    string product_name;
    int quantity;
    string address;
    bool delivered;
    Payment payment;
    string rev;
    int rate;

public:
    Order(string p_name, int qty, string addr) : payment(p_name, qty) {
        product_name = p_name;
        quantity = qty;
        address = addr;
        delivered = false;
    }

    void place_order() {
        if (payment.check_item_availability()) {
            cout << "Order placed successfully for " << quantity << " " << product_name << "(s) to be delivered to " << address << ".\n";
            cout << "Total amount: $" << payment.getTotalPrice() << endl;
            delivered = true;
            ofstream outfile("myfile.txt", ios::app);
            if (outfile.is_open()) {
                outfile << product_name << endl;
                outfile << quantity << endl;
                outfile << address << endl;
                outfile << delivered << "\n";
                outfile.close();
            }
            else {
                cout << "Error opening file for writing.\n";
            }

        }
        else {
            cout << "Order could not be placed due to stock issues.\n";
        }
    }
    void check_delivery_status() {
        if (delivered) {

            cout << "Order has been delivered.\n";
            cout << "You successfully bought the product.\n";
            cout << "\t\t\t\t\t\t\ ENTER YOUR FEEDBACK **   \t\t\t\t " << endl;
            cout << "Enter the reviews regarding the product you have received ";
            getline(cin, rev);
            cout << "Rate the product out of 10: ";
            cin >> rate;
            cout << "\t\t\t\t\t\ **THANKS FOR VISITING OUR WEBSITE **   \t\t\t\t " << endl;
            ofstream outfile("myfile.txt", ios::app);
            if (outfile.is_open()) {
                outfile << product_name << endl;
                outfile << rate << endl;
                outfile << rev << "\n";
                outfile.close();
            }
            else {
                cout << "Error opening file for writing.\n";
            }
        }
        else {
            cout << "Order is not delivered yet.\n";
        }

    }
};
class Admin {
public:
    string username;
    string email;
    string password;
    product tshirts;
    product jeans;
    product dresses;
    product shoes;
    product handbags;
    product smartphones;
    product laptops;
    product televisions;
    product headphones;
    product smartwatches;
    product balls;
    product bats;
    product bicycles;
    product rackets;
    product camping_stoves;
    product puzzles;
    product boardgames;
    product videogames;
    product actionfigures;
    product educationaltoys;

    Admin()
        : tshirts("t_shirts", 30), jeans("jeans", 30), dresses("dresses", 30), shoes("shoes", 30),
        handbags("handbags", 30), smartphones("smartphones", 30), laptops("laptops", 30),
        televisions("televisions", 30), headphones("headphones", 30), smartwatches("smartwatches", 30),
        balls("balls", 30), bats("bats", 30), bicycles("bicycles", 30), rackets("rackets", 30),
        camping_stoves("camping stoves", 30), puzzles("puzzles", 30), boardgames("board games", 30),
        videogames("video games", 30), actionfigures("action figures", 30), educationaltoys("educational toys", 30) {}

    void signin() {
        cout << "Enter your details to login" << endl;
        cout << " Enter your name  ";
        cin.ignore();
        getline(cin, username);
        cout << " Enter your password  ";
        cin >> password;
        cin.ignore();
        cout << " enter your email address  ";
        getline(cin, email);
        cout << "You are logged in successfully " << endl;
        ofstream infile("myfile.txt", ios::app);
        cout << infile << username << endl;
        cout << infile << password << endl;
        cout << infile << email << endl;
        infile.close();
        infile.close();
    }
    void updateStock() {
        string productName;
        int newQuantity;
        cout << "Enter the name of the product you want to update: ";
        cin.ignore();
        getline(cin, productName);
        cout << "Enter the new quantity (1-100): ";
        cin >> newQuantity;

        if (productName == "t_shirts") {
            tshirts.update_quantity(newQuantity);
        }
        else if (productName == "jeans") {
            jeans.update_quantity(newQuantity);
        }
        else if (productName == "dresses") {
            dresses.update_quantity(newQuantity);
        }
        else if (productName == "shoes") {
            shoes.update_quantity(newQuantity);
        }
        else if (productName == "handbags") {
            handbags.update_quantity(newQuantity);
        }
        else if (productName == "smartphones") {
            smartphones.update_quantity(newQuantity);
        }
        else if (productName == "laptops") {
            laptops.update_quantity(newQuantity);
        }
        else if (productName == "televisions") {
            televisions.update_quantity(newQuantity);
        }
        else if (productName == "headphones") {
            headphones.update_quantity(newQuantity);
        }
        else if (productName == "smartwatches") {
            smartwatches.update_quantity(newQuantity);
        }
        else if (productName == "balls") {
            balls.update_quantity(newQuantity);
        }
        else if (productName == "bats") {
            bats.update_quantity(newQuantity);
        }
        else if (productName == "bicycles") {
            bicycles.update_quantity(newQuantity);
        }
        else if (productName == "rackets") {
            rackets.update_quantity(newQuantity);
        }
        else if (productName == "camping stoves") {
            camping_stoves.update_quantity(newQuantity);
        }
        else if (productName == "puzzles") {
            puzzles.update_quantity(newQuantity);
        }
        else if (productName == "board games") {
            boardgames.update_quantity(newQuantity);
        }
        else if (productName == "video games") {
            videogames.update_quantity(newQuantity);
        }
        else if (productName == "action figures") {
            actionfigures.update_quantity(newQuantity);
        }
        else if (productName == "educational toys") {
            educationaltoys.update_quantity(newQuantity);
        }
        else {
            cout << "Product " << productName << " not found.\n";
        }
    }
    void checkAllProductsAvailability() {
        tshirts.display_availability();
        jeans.display_availability();
        dresses.display_availability();
        shoes.display_availability();
        handbags.display_availability();
        smartphones.display_availability();
        laptops.display_availability();
        televisions.display_availability();
        headphones.display_availability();
        smartwatches.display_availability();
        balls.display_availability();
        bats.display_availability();
        bicycles.display_availability();
        rackets.display_availability();
        camping_stoves.display_availability();
        puzzles.display_availability();
        boardgames.display_availability();
        videogames.display_availability();
        actionfigures.display_availability();
        educationaltoys.display_availability();
    }
};
int main() {
    int choice;
    cout << "\t\t\t\t\t\t WELCOME TO ONLINE SHOPPING APPLICATION   \t\t\t\t " << endl;
    cout << "Press 1 to use the website as a customer\n";
    cout << "Press 2 to use the website as an admin\n";
    cin >> choice;
    cin.ignore();
    if (choice == 1) {
        user u1;
        product p1;
        u1.browse_product();
        p1.ask_product();
        p1.checkitem_availability();
        u1.add_to_cart();
        u1.login();
        p1.buy_product();
        string product_name;
        int quantity;
        string address;
        cout << "\t\t\t\t\t\t\ * CONFIRM YOUR ORDER *   \t\t\t\t " << endl;
        cout << "Enter the product name: ";
        cin.ignore();
        getline(cin, product_name);
        cout << "Enter the quantity: ";
        cin >> quantity;
        cin.ignore();
        cout << "Enter the delivery address: ";
        getline(cin, address);

        Order order(product_name, quantity, address);
        order.place_order();
        order.check_delivery_status();
        u1.logout();
    }
    else if (choice == 2) {
        Admin admin;
        admin.signin();
        char option;
        do {
            cout << "Choose an option:\n";
            cout << "1. Update stock\n";
            cout << "2. Check all products availability\n";
            cout << "3. Exit\n";
            cin >> option;
            switch (option) {
            case '1':
                cout << "\t\t\t\t UPDATE STOCK   \t\t\t\t " << endl;

                admin.updateStock();
                break;
            case '2':
                cout << "\t\t\t\t CHECK ALL PRODUCTS AVAILABILITY   \t\t\t\t " << endl;

                admin.checkAllProductsAvailability();
                break;
            case '3':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
            }
        } while (option != '3');
    }
    else {
        cout << "Please enter 1 or 2" << endl;
    }
    return 0;
}