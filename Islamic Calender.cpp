#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Month;

class Muharram;
class Safar;
class Rabbi_ul_Awwal;
class Rabbi_uth_Thani;
class Jamid_ul_Awwal;
class Jamid_uth_Thani;
class Rajab;
class Shaban;
class Ramazan;
class Shawwal;
class Zul_Qada;
class Zul_Hajj;

class Month
{
private:
    string daysOfWeek[7] = { "Yaum al Ahad", "Yaum al ithnayn", "Yaum as Salatha", "Yaum al Arba'aa", "Yaum al Khamees", "Yaum al Jumu'ah", "Yaum as Sabt" };
    string monthName, fajr, zuhr, asr, maghrib, isha, sahrTimings, iftarTimings, sunriseTimings, sunsetTimings, festivals;
public:
    Month(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        : monthName(mn), fajr(f), zuhr(z), asr(a), maghrib(m), isha(is), sahrTimings(sa), iftarTimings(ift), sunriseTimings(sr), sunsetTimings(ss), festivals(fe) {}

    void incrementTime(string& time) {
        int hour = stoi(time.substr(0, 2));
        int minute = stoi(time.substr(3, 2));
        minute++;
        if (minute == 60) {
            minute = 0;
            hour++;
        }
        time = (hour < 10 ? "0" : "") + to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
    }

    void decrementTime(string& time) {
        int hour = stoi(time.substr(0, 2));
        int minute = stoi(time.substr(3, 2));
        if (minute == 0) {
            minute = 59;
            hour--;
        }
        else {
            minute--;
        }
        time = (hour < 10 ? "0" : "") + to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
    }

    void calculatePrayerTimings(ofstream& outFile) {
        for (int i = 0; i < 30; ++i) {
            decrementTime(fajr);
            incrementTime(zuhr);
            incrementTime(asr);
            incrementTime(maghrib);
            incrementTime(isha);

            cout << setw(2) << i + 1 << " " << monthName << ":\n";
            cout << "Fajr: " << fajr << " am\t\t"
                << "Zuhr: " << zuhr << " pm\t\t"
                << "Asr: " << asr << " pm\t\t"
                << "Maghrib: " << maghrib << " pm\t\t"
                << "Isha: " << isha << " pm\n\n";

            outFile << setw(2) << i + 1 << " " << monthName << ":\n";
            outFile << "Fajr: " << fajr << " am\t"
                << "Zuhr: " << zuhr << " pm\t"
                << "Asr: " << asr << " pm\t"
                << "Maghrib: " << maghrib << " pm\t"
                << "Isha: " << isha << " pm\n\n";
        }
    }

    void calculateSunriseSunsetTimings(ofstream& outFile) {
        outFile << "\nSunrise Timings:\n";
        cout << "\nSunrise Timings:\n";

        for (int i = 0; i < 30; ++i) {
            decrementTime(sunriseTimings);

            cout << setw(2) << i + 1 << " " << monthName << ": " << sunriseTimings << " am\t";
            outFile << setw(2) << i + 1 << " " << monthName << ": " << sunriseTimings << " am\t";

            if ((i + 1) % 3 == 0) {
                cout << "\n";
                outFile << "\n";
            }
        }

        outFile << "\n\nSunset Timings:\n";
        cout << "\n\nSunset Timings:\n";

        for (int i = 0; i < 30; ++i) {
            incrementTime(sunsetTimings);

            cout << setw(2) << i + 1 << " " << monthName << ": " << sunsetTimings << " pm\t";
            outFile << setw(2) << i + 1 << " " << monthName << ": " << sunsetTimings << " pm\t";

            if ((i + 1) % 3 == 0) {
                cout << "\n";
                outFile << "\n";
            }
        }
    }

    void calculateSahrIftarTimings(ofstream& outFile) {
        outFile << "\nSahr Timings:\n";
        cout << "\nSahr Timings:\n";

        for (int i = 0; i < 30; ++i) {
            decrementTime(sahrTimings);

            cout << setw(2) << i + 1 << " " << monthName << ": " << sahrTimings << "\t";
            outFile << setw(2) << i + 1 << " " << monthName << ": " << sahrTimings << "\t";

            if ((i + 1) % 3 == 0) {
                cout << "\n";
                outFile << "\n";
            }
        }

        outFile << "\n\nIftar Timings:\n";
        cout << "\n\nIftar Timings:\n";

        for (int i = 0; i < 30; ++i) {
            incrementTime(iftarTimings);

            cout << setw(2) << i + 1 << " " << monthName << ": " << iftarTimings << "\t";
            outFile << setw(2) << i + 1 << " " << monthName << ": " << iftarTimings << "\t";

            if ((i + 1) % 3 == 0) {
                cout << "\n";
                outFile << "\n";
            }
        }
    }

    void calculateDaysOfWeek(ofstream& outFile)
    {
        string daysOfMonth[30];
        for (int i = 0; i < 30; ++i) {

            daysOfMonth[i] = daysOfWeek[i % 7];
        }

        cout << "\nDays of the week for the entire month:\n";
        outFile << "\nDays of the week for the entire month:\n";
        for (int i = 0; i < 30; ++i) {

            cout << "\t";

            if (i > 8)
                cout << "\b";

            cout << i + 1 << " " << monthName << ": " << daysOfMonth[i] << "\n";
            outFile << i + 1 << " " << monthName << ": " << daysOfMonth[i] << "\n";

        }
    }

    void calculateTimingsForDate(int day, ofstream& outFile) {
        int dayIndex = day;
        string prayerTimings[] = { fajr, zuhr, asr, maghrib, isha };
        string prayerNames[] = { "Fajr", "Zuhr", "Asr", "Maghrib", "Isha" };

        for (int i = 0; i < dayIndex; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (j == 0)
                    decrementTime(prayerTimings[0]);
                else
                {
                    incrementTime(prayerTimings[j]);
                }
            }
        }

        cout << "\nTimings for " << day << " " << monthName << ":\n";
        outFile << "\nTimings for " << day << " " << monthName << ":\n";

        for (int j = 0; j < 5; ++j) {
            cout << prayerNames[j] << ": " << prayerTimings[j] << (j < 2 ? " am" : " pm") << "\n";
            outFile << prayerNames[j] << ": " << prayerTimings[j] << (j < 2 ? " am" : " pm") << "\n";

        }


        for (int i = 0; i < dayIndex; ++i) {
            decrementTime(sunriseTimings);
            incrementTime(sunsetTimings);

        }

        cout << "Sunrise: " << sunriseTimings << " am\n";
        outFile << "Sunrise: " << sunriseTimings << " am\n";
        cout << "Sunset: " << sunsetTimings << " pm\n";
        outFile << "Sunset: " << sunsetTimings << " pm\n";

        for (int i = 0; i < dayIndex; ++i) {

            decrementTime(sahrTimings);

            incrementTime(iftarTimings);
        }
        cout << "Sahr: " << sahrTimings << "\n";
        outFile << "Sahr: " << sahrTimings << "\n";
        cout << "Iftar: " << iftarTimings << "\n";
        outFile << "Iftar: " << iftarTimings << "\n";

    }

    void displaySelectionMenu() const {
        cout << "Menu:\n"
            << "Display for the entire month:\n"
            << "1. Display Prayer Timings\n"
            << "2. Display Sunrise and Sunset Timings\n"
            << "3. Display Sahr and Iftar Timings\n"
            << "4. Display Days of the Week\n"
            << "5. Display Festivals/Important Dates to Remember\n"
            << "Specific date:\n"
            << "6. Search Timings by Date\n"
            << "7. Exit\n";
    }

    void displaySelection(int choice) {
        ofstream outFile("Calendar.txt", ios::app);
        if (!outFile) {
            cerr << "\nError opening file" << endl;
            return;
        }
        switch (choice) {
        case 1:
            cout << "\nPrayer Timings:\n";
            outFile << "\nPrayer Timings:\n";
            calculatePrayerTimings(outFile);
            break;
        case 2:
            calculateSunriseSunsetTimings(outFile);
            break;
        case 3:
            calculateSahrIftarTimings(outFile);
            break;
        case 4:
            calculateDaysOfWeek(outFile);
            break;
        case 5:
            cout << "Festivals/Important Dates to Remember: " << festivals << "\n";
            break;
        case 6:
            int day;
            cout << "Enter the date (1-30): ";
            cin >> day;
            if (day < 1 || day > 30) {
                cout << "Invalid date. Please enter a date between 1 and 30.\n";
                break;
            }
            calculateTimingsForDate(day, outFile);
            break;

        case 7:
            cout << "Exiting calendar\n";
            outFile.close();
            break;
        default:
            cout << "Invalid choice\n";
        }
    }
};


class  Muharram : public Month {
public:
    Muharram(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        :Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

class Safar : public Month {
public:
    Safar(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        :Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

class Rabbi_ul_Awwal : public Month {
public:
    Rabbi_ul_Awwal(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        :Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

class Rabbi_uth_Thani : public Month {
public:
    Rabbi_uth_Thani(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        :Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};
class Jamid_ul_Awwal : public Month {
public:
    Jamid_ul_Awwal(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        : Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

class Jamid_uth_Thani : public Month {
public:
    Jamid_uth_Thani(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        : Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

class Rajab : public Month {
public:
    Rajab(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        : Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

class Shaban : public Month {
public:
    Shaban(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        : Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

class Ramazan : public Month {
public:
    Ramazan(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        :Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

class Shawwal : public Month {
public:
    Shawwal(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        : Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

class Zul_Qada : public Month {
public:
    Zul_Qada(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        : Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

class Zul_Hajj : public Month {
public:
    Zul_Hajj(string mn, string f, string z, string a, string m, string is, string sa, string ift, string sr, string ss, string fe)
        : Month(mn, f, z, a, m, is, sa, ift, sr, ss, fe) {}

};

int main() {
    system("color F1");
    int choice1;
    int choice2;

    cout << "\t\t\t\t\t\tHijri Calendar 1445 A.H\n";

    do {
        Muharram muharram("Muharram", "05:30", "11:25", "03:00", "5:00", "07:00",
            "05:30", "05:00", "06:32", "05:00", "9th and 10th Muharram");

        Safar safar("Safar", "05:20", "11:30", "03:10", "05:20", "07:20",
            "05:20", "05:20", "06:20", "05:20", "Null");

        Rabbi_ul_Awwal rabbi_ul_Awwal("Rabbi-ul-Awwal", "05:00", "11:35", "03:15", "05:15", "08:00",
            "05:00", "05:15", "06:30", "05:15", "Null");

        Rabbi_uth_Thani rabbi_uth_Thani("Rabbi-uth-Thani", "04:45", "11:40", "03:30", "05:30", "08:00",
            "04:45", "05:30", "06:15", "05:30", "Null");

        Jamid_ul_Awwal  jamid_ul_Awwal(" Jamid-ul-Awwal", "04:30", "11:45", "03:45", "05:45", "08:00",
            "04:30", "05:45", "06:00", "05:45", "Null");

        Jamid_uth_Thani  jamid_uth_Thani("Jamid-uth-Thani ", "04:15", "11:50", "04:00", "06:00", "08:00",
            "04:15", "06:00", "05:45", "06:00", "Null");

        Rajab rajab("Rajab", "04:05", "11:55", "04:15", "06:15", "08:00",
            "04:05", "06:15", "05:35", "06:15", "Null");

        Shaban shaban("Shaban", "03:55", "12:00", "04:30", "06:30", "08:00",
            "03:55", "06:30", "05:25", "06:30", "Null");

        Ramazan ramazan("Ramadhan", "03:40", "12:05", "04:45", "06:45", "08:00",
            "03:40", "06:45", "05:10", "06:45", "Laylat-ul-Qadr: 21,23,25,27,29");

        Shawwal shawwal(" Shawwal", "03:30", "12:10", "05:00", "07:00", "08:00",
            "03:30", "07:00", "05:00", "07:00", "Eid ul Fitr (1st of Shawwal");

        Zul_Qada zul_qada("Zul-Qada", "03:20", "12:15", "05:15", "07:15", "08:00",
            "03:20", "07:15", "04:50", "07:15", "Null");

        Zul_Hajj zul_Hajj("Zul-Hajj", "03:05", "12:20", "05:30", "07:30", "08:00",
            "03:05", "07:30", "04:35", "07:30", "Eid ul Adha, first 10 Days of this month");

        cout << "\n\nSelect a month (1-12): ";
        cin >> choice1;

        if (choice1 == 1)
        {
            cout << "\nSelected month: " << "Muharram" << "\n\n";
            muharram.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            muharram.displaySelection(choice2);
        }

        else if (choice1 == 2)
        {
            cout << "\nSelected month: " << "Safar" << "\n\n";
            safar.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            safar.displaySelection(choice2);
        }

        else if (choice1 == 3)
        {
            cout << "\nSelected month: " << "Rabbi-ul-Awwal" << "\n\n";
            rabbi_ul_Awwal.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            rabbi_ul_Awwal.displaySelection(choice2);
        }

        else if (choice1 == 4)
        {
            cout << "\nSelected month: " << "Rabbi-uth-Thani" << "\n\n";
            rabbi_uth_Thani.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            rabbi_uth_Thani.displaySelection(choice2);
        }

        else if (choice1 == 5)
        {
            cout << "\nSelected month: " << "Jamid-ul-Awwal" << "\n\n";
            jamid_ul_Awwal.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            jamid_ul_Awwal.displaySelection(choice2);
        }

        else if (choice1 == 6)
        {
            cout << "\nSelected month: " << "Jamid-uth-Thani" << "\n\n";
            jamid_uth_Thani.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            jamid_uth_Thani.displaySelection(choice2);
        }

        else if (choice1 == 7)
        {
            cout << "\nSelected month: " << "Rajab" << "\n\n";
            rajab.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            rajab.displaySelection(choice2);
        }
        else if (choice1 == 8)
        {
            cout << "\nSelected month: " << "Shaban" << "\n\n";
            shaban.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            shaban.displaySelection(choice2);
        }
        else if (choice1 == 9) {
            cout << "\nSelected month: " << "Ramadhan" << "\n\n";
            ramazan.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            ramazan.displaySelection(choice2);
        }

        else if (choice1 == 10)
        {
            cout << "\nSelected month: " << "Shawwal" << "\n\n";
            shawwal.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            shawwal.displaySelection(choice2);
        }

        else if (choice1 == 11)
        {
            cout << "\nSelected month: " << "Zul-qada" << "\n\n";
            zul_qada.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            zul_qada.displaySelection(choice2);

        }

        else if (choice1 == 12)
        {
            cout << "\nSelected month: " << "Zul-Hajj" << "\n\n";
            zul_Hajj.displaySelectionMenu();
            cout << "\nEnter your choice: ";
            cin >> choice2;
            zul_Hajj.displaySelection(choice2);
        }

        else {
            cout << "Invalid month selection. Please try again.\n\n";
        }
    } while (choice2 != 7);

    return 0;
}
