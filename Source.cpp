#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <cctype>

const int MAX_USERS = 100;
const int MAX_STATIONS = 100;
const int MAX_RIDES = 1000;
const int max_num = 10;

using namespace std;

struct subPlan {
    string type;
    int price;
    int ridenum;
};

subPlan PLAN[max_num] = { {"wallet", 200, 700}, {"student", 33, 180}, {"public", 60, 280} };
int numplan = 3;

struct Date {
    int day, month, year;

    Date() {
        day = month = year = 0;
    }

};


struct RIDE {
    int ride_id = 0;
    string checkin;
    string checkout;
    Date ride_date;
    int user_id = 0;

    RIDE() {
        ride_id = user_id = 0;
        checkin = checkout = "";
    }
};


struct subscription {
    string type = "NO CURRENT SUBSCRIPTION";
    Date startdate;
    Date enddate;
    int ridecount = 0;

    subscription() {
        type = "NO CURRENT SUBSCRIPTION";
        ridecount = 0;
    }
};


struct User {
    string username;
    string password;
    string userType;
    string phoneNo;
    subscription sub;
    int userID = 0;
    int balance = 0;

    User() {
        username = password = userType = phoneNo = "";
        userID = balance = 0;
    }
};

RIDE rides[MAX_RIDES];
int rideNo = 0, rideID = 1001;
User users[MAX_USERS];
int userCount = 0, id = 101;
string stagesnum, payperiod;
string choice1;
int stations_allowed = 0;

string first_line[MAX_STATIONS] = { "Helwan", "Ain Helwan", "Helwan University", "Wadi Hof", "Hadaeq Helwan",
                                   "ElMaasara", "Tora ElAsmant", "Kozzika", "Tora elbalad", "Sakanat elmaadi", "Maadi",
                                   "Hadayeq elmaadi", "Dar elsalam", "Elzahraa", "Mar girgis", "Elmalek elsaleh",
                                   "sayyeda zeinab", "Saad zaghlol", "Sadat", "Nasser", "Orabi", "Elshohadaa", "Ghamra",
                                   "ElDemerdash", "Manshiet ElSadr", "Kobri ElQubba", "HammamatElQubba",
                                   "Saray ElQubba", "Hadayeq ElZaiton", "Helmiet ElZaiton", "Elmattareyya", "Ain Shams",
                                   "Ezbet ElNakhl", "ElMarg", "New Elamrg" };
string second_line[MAX_STATIONS] = { "El Monyeb", "Sakyt Mekky", "Om El masryeen", "El Geza", "Faisal", "Gam3t el kahra",
                                    "El Bohooth", "El Dokki", "El Obra", "Sadat", "Mohammed Nageeb", "ElAttaba",
                                    "El shodaa", "Massara", "Rod el farg", "Santa treza", "El khalfawy", "El mazlat",
                                    "Kolyat el zra3a", "Shobra el khema" };
string third_line[MAX_STATIONS] = { "Adly Mansour", "EL Haikstep", "Omar ebn el kahattab", "qaba2", "Hesham barkat",
                                   "El nozha", "Nady elshams", "Alf maskn", "Helioples", "Haron", "El ahram",
                                   "Kolyat el banat", "el estad", "ard el maard", "el abasyaa", "abdo basha", "el gesh",
                                   "bab el she3rya", "ElAttaba", "nasser", "masbero", "safaa hegazy", "el kit kat" };

void viewRideHistory(User& user);

void ridelogs();

void user_manage_subscription(User& user);

int datecalc_renew(User& user, string choice1, string payperiod);

int datecalc_details(User& user, string choice1, string payperiod);

void upgradesub(string& stagesnum);

int calculatefare(User& user, string stagesnum, string payperiod);

int add_subs(subPlan plans[], int& numplan, const string& name, int price, int ridecount);

void remove_plan(subPlan plans[], int& numplan, const string& type);

void modify(subPlan plans[], int numplan, const string& type, const string& newname, int newridenum, int newprice);

void display_subscriptions(subPlan plans[], int numplan);

void subscriptionmanagement();

void wallet(User& user);

void checkin_checkout(User& user, RIDE ride[], string stagesnum, int stations_allowed);

int balancecalc(User& user, string stagesnum, string choice);

void ride_count(User& user, string payperiod);

void purchaseSubscription(User& user);

void addstation();

void editstation();

void deletestation();

void stationManagment();

void deleteUser(int useridx);

int countUsers(User users[]);

void userManagement();

bool doesUsernameExist(const string& username, const User users[], int userCount);

bool doesPhoneNoExist(string phoneNo, const User users[], int userCount);

string getPasswordFromConsole();

void userMenu(User& user, RIDE rides[]);

void adminMenu(User& user);

int login(string username, string password, User users[], int userCount);

void registerUser(User users[], int& userCount);

void updatePersonalInfo(User& user);

void mainMenu();

int main() {
    mainMenu();
    return 0;
}

string getPasswordFromConsole() {
    string password;
    char ch;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT)); 

    while (true) {
        ch = _getch(); 
        if (ch == '\r' || ch == '\n') { 
            break;
        }
        else if (ch == '\b') { 
            if (!password.empty()) {
                cout << "\b \b"; 
                password.pop_back();
            }
        }
        else {
            cout << "*"; // Print * instead of the actual character
            password.push_back(ch);
        }
    }

    SetConsoleMode(hStdin, mode); // Restore console mode
    return password;
}

bool doesUsernameExist(const string& username, const User users[], int userCount) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == username) {
            return true;
        }
    }
    return false;
}

bool doesPhoneNoExist(string phoneNo, const User users[], int userCount) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].phoneNo == phoneNo) {
            return true;
        }
    }
    return false;
}

void updatePersonalInfo(User& user) {
    while (true) {
        while (true) {
            string choice, newName, newPassword, newPhoneNo;

            cout << "What would you like to update?\n";
            cout << "1. Change username\n";
            cout << "2. Change password\n";
            cout << "3. Change phone number\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == "1") {
                while (true) {
                    cout << "Enter new username: ";
                    cin >> newName;
                    if (doesUsernameExist(newName, users, userCount)) {
                        cout << "Username already exists. Please choose a different username." << endl;
                    }
                    else {
                        user.username = newName;
                        cout << "Username updated successfully.\n";
                        break;
                    }
                }
                break;
            }
            else if (choice == "2") {
                cout << "Enter new password: ";
                newPassword = getPasswordFromConsole();
                user.password = newPassword;
                cout << endl << "Password updated successfully.\n";
                break;
            }
            else if (choice == "3") {
                cout << "Enter new phone number: ";
                while (true) {
                    cout << "Enter phone number: ";
                    cin >> newPhoneNo;
                    if (doesPhoneNoExist(newPhoneNo, users, userCount)) {
                        cout << "Phone number already exist. Please choose a different phone number." << endl;
                        continue;
                    }
                    bool flag = true;
                    for (int i = 0; i < newPhoneNo.size(); i++) {
                        if (newPhoneNo[i] > 57 or newPhoneNo[i] < 48) {
                            flag = false;
                            break;
                        }
                    }
                    if (newPhoneNo.size() != 11 or newPhoneNo[0] != '0' or newPhoneNo[1] != '1') {
                        flag = false;
                    }
                    if (flag) {
                        break;
                    }
                    else {
                        cout << "Not a valid Phone number. Please write a different phone number." << endl;
                    }
                }
                break;
            }
            else {
                cout << "Invalid choice. Please try again\n";
            }
        }
        char tempchoice;
        bool cntniue = true;
        while (true) {
            cout << "Would you like to update anything else? (Y/y || N/n) \n";
            cin >> tempchoice;
            if (tempchoice != 'N' and tempchoice != 'n' and tempchoice != 'Y' and tempchoice != 'y') {
                cout << "Not a valid choice. Please choose again \n";
            }
            else if (tempchoice == 'N' or tempchoice == 'n') {
                cntniue = false;
                break;
            }
            else if (tempchoice == 'Y' or tempchoice == 'y') {
                cntniue = true;
                break;
            }
        }
        if (!cntniue) {
            break;
        }
    }
}

void ride_count(User& user, string payperiod = "3") {
    if (user.sub.type == "1")
        user.sub.ridecount = 180;
    else if (user.sub.type == "2") {
        if (payperiod == "1") {
            user.sub.ridecount = 60;
        }
        else if (payperiod == "12") {
            user.sub.ridecount = 730;
        }
    }

}

int balancecalc(User& user, string stagesnum, string choice1) {

    if (stagesnum == "1") {
        user.balance -= 6;
        return user.balance;
    }
    else if (stagesnum == "2") {
        user.balance -= 8;
        return user.balance;
    }
    else if (stagesnum == "3") {
        user.balance -= 12;
        return user.balance;
    }
    else if (stagesnum == "4") {
        user.balance -= 15;
        return user.balance;
    }
    return user.balance;
}


void checkin_checkout(User& user, RIDE ride[], string stagesnum, int stations_allowed) {
    int check_in_index = -1;
    int check_out_index = -1;
    bool found_in_first_line_checkin = false;
    bool found_in_second_line_checkin = false;
    bool found_in_third_line_checkin = false;
    bool found_in_first_line_checkout = false;
    bool found_in_second_line_checkout = false;
    bool found_in_third_line_checkout = false;
    int num_of_stations_ridden;
    int num_rides_made = 0;
    string repeat = "";
    do {
        do {
            do {
                int result = datecalc_details(user, choice1, payperiod);
                int Result = datecalc_renew(user, choice1, payperiod);
                while (true) {
                    cout << "Enter the date of your trip (day month year):" << endl;
                    cin >> rides[rideNo].ride_date.day >> rides[rideNo].ride_date.month >> rides[rideNo].ride_date.year;
                    if (rides[rideNo].ride_date.day <= 30 && rides[rideNo].ride_date.month <= 12)
                        break;
                    else
                        cout << "Invalid date.Please enter a proper date" << endl;
                }
                if (user.sub.type == "1" || user.sub.type == "2") {
                    if ((rides[rideNo].ride_date.day > user.sub.enddate.day &&
                        rides[rideNo].ride_date.month > user.sub.enddate.month) ||
                        (rides[rideNo].ride_date.month > user.sub.enddate.month)) {
                        cout << "Your subscription has expired.Please renew it." << endl;
                        user_manage_subscription(user);
                    }
                }
                else if (user.sub.type == "3")
                    cout << "unlimited stations" << endl;


                rides[rideNo].ride_id = rideID;
                rides[rideNo].user_id = user.userID;

                cin.clear();
                cin.ignore();
                cout << "Which station will you check in from?" << endl;
                getline(cin, rides[rideNo].checkin);

                for (char& c : rides[rideNo].checkin) {
                    c = toupper(c);
                }

                for (int i = 0; i < MAX_STATIONS; ++i) {
                    string station_uppercase = first_line[i];
                    for (char& c : station_uppercase) {
                        c = toupper(c);
                    }
                    if (station_uppercase == rides[rideNo].checkin) {
                        check_in_index = i;
                        found_in_first_line_checkin = true;
                        break;
                    }
                }

                if (!found_in_first_line_checkin) {
                    for (int i = 0; i < MAX_STATIONS; ++i) {
                        string station_uppercase = second_line[i];
                        for (char& c : station_uppercase) {
                            c = toupper(c);
                        }
                        if (station_uppercase == rides[rideNo].checkin) {
                            check_in_index = i;
                            found_in_second_line_checkin = true;
                            break;
                        }
                    }
                }

                if (!found_in_first_line_checkin && !found_in_second_line_checkin) {
                    for (int i = 0; i < MAX_STATIONS; ++i) {
                        string station_uppercase = third_line[i];
                        for (char& c : station_uppercase) {
                            c = toupper(c);
                        }
                        if (station_uppercase == rides[rideNo].checkin) {
                            check_in_index = i;
                            found_in_third_line_checkin = true;
                            break;
                        }
                    }
                }
                if (!found_in_first_line_checkin && !found_in_second_line_checkin && !found_in_third_line_checkin) {
                    cout << "Invalid station for check-in. Please try again." << endl;
                }
            } while (!found_in_first_line_checkin && !found_in_second_line_checkin && !found_in_third_line_checkin);

            do {
                cout << "Which station will you check out from?" << endl;
                getline(cin, rides[rideNo].checkout);

                for (char& c : rides[rideNo].checkout) {
                    c = toupper(c);
                }

                for (int i = 0; i < MAX_STATIONS; ++i) {
                    string station_uppercase = first_line[i];
                    for (char& c : station_uppercase) {
                        c = toupper(c);
                    }
                    if (station_uppercase == rides[rideNo].checkout) {
                        check_out_index = i;
                        found_in_first_line_checkout = true;
                        break;
                    }
                }

                if (!found_in_first_line_checkout) {
                    for (int i = 0; i < MAX_STATIONS; ++i) {
                        string station_uppercase = second_line[i];
                        for (char& c : station_uppercase) {
                            c = toupper(c);
                        }
                        if (station_uppercase == rides[rideNo].checkout) {
                            check_out_index = i;
                            found_in_second_line_checkout = true;
                            break;
                        }
                    }
                }

                if (!found_in_first_line_checkout && !found_in_second_line_checkout) {
                    for (int i = 0; i < MAX_STATIONS; ++i) {
                        string station_uppercase = third_line[i];
                        for (char& c : station_uppercase) {
                            c = toupper(c);
                        }
                        if (station_uppercase == rides[rideNo].checkout) {
                            check_out_index = i;
                            found_in_third_line_checkout = true;
                            break;
                        }
                    }
                }

                if (!found_in_first_line_checkout && !found_in_second_line_checkout && !found_in_third_line_checkout) {
                    cout << "Invalid station for check-out. Please try again." << endl;
                }
            } while (!found_in_first_line_checkout && !found_in_second_line_checkout && !found_in_third_line_checkout);

            if (found_in_first_line_checkin && found_in_first_line_checkout) {
                num_of_stations_ridden = abs(check_out_index - check_in_index);
            }
            else if (found_in_second_line_checkin && found_in_second_line_checkout) {
                num_of_stations_ridden = abs(check_out_index - check_in_index);
            }
            else if (found_in_third_line_checkin && found_in_third_line_checkout) {
                num_of_stations_ridden = abs(check_out_index - check_in_index);
            }
            else if (found_in_first_line_checkin && found_in_second_line_checkout) {
                int num_of_stations_ridden_first_line_to_sadat = abs(18 - check_in_index);
                int num_of_stations_ridden_sadat_to_second_line_checkout = abs(check_out_index - 9);
                num_of_stations_ridden = num_of_stations_ridden_first_line_to_sadat +
                    num_of_stations_ridden_sadat_to_second_line_checkout;
            }
            else if (found_in_first_line_checkin && found_in_third_line_checkout) {
                int num_of_stations_ridden_first_line = abs(19 - check_in_index);
                int num_of_stations_ridden_third_line = abs(check_out_index - 19);
                num_of_stations_ridden = num_of_stations_ridden_first_line + num_of_stations_ridden_third_line;
            }
            else if (found_in_second_line_checkin && found_in_third_line_checkout) {
                int num_of_stations_ridden_second_line = abs(11 - check_in_index);
                int num_of_stations_ridden_third_line = abs(check_out_index - 18);
                num_of_stations_ridden = num_of_stations_ridden_second_line + num_of_stations_ridden_third_line;
            }
            else if (found_in_third_line_checkin && found_in_second_line_checkout) {
                int num_of_stations_ridden_third_line = abs(18 - check_in_index);
                int num_of_stations_ridden_second_line = abs(check_out_index - 11);
                num_of_stations_ridden = num_of_stations_ridden_third_line + num_of_stations_ridden_second_line;
            }
            else if (found_in_third_line_checkin && found_in_first_line_checkout) {
                int num_of_stations_ridden_third_line = abs(19 - check_in_index);
                int num_of_stations_ridden_first_line = abs(check_out_index - 19);
                num_of_stations_ridden = num_of_stations_ridden_third_line + num_of_stations_ridden_first_line;
            }
            else if (found_in_second_line_checkin && found_in_first_line_checkout) {
                int num_of_stations_ridden_second_line = abs(9 - check_in_index);
                int num_of_stations_ridden_first_line = abs(check_out_index - 18);
                num_of_stations_ridden = num_of_stations_ridden_second_line + num_of_stations_ridden_first_line;
            }
            else {
                cout << "Invalid combination of check-in and check-out stations." << endl;
                continue;
            }
            cin.clear();
            cin.ignore();

            if (num_of_stations_ridden <= stations_allowed)
                break;
            else
                cout << "your ride duration is longer than your current stage.Please try again." << endl;

        } while (num_of_stations_ridden > stations_allowed);

        if (user.sub.type == "1" || user.sub.type == "2") {
            ride_count(user, payperiod);
            if (user.sub.ridecount <= 0) {
                cout << "you have reached your limit of rides" << endl;
            }
        }

        num_rides_made++;
        user.sub.ridecount -= num_rides_made;


        cout << "Ride Id:\t" << rides[rideNo].ride_id << endl;
        if (user.sub.type == "1" || user.sub.type == "2") {
            cout << "number of remaining rides:\t" << user.sub.ridecount << endl;
        }
        else if (user.sub.type == "3") {
            int result = balancecalc(user, stagesnum, choice1);
            cout << "remaining balance:" << result << endl;
        }

        cout << "User checked in at station: " << rides[rideNo].checkin << endl;
        cout << "User checked out at station: " << rides[rideNo].checkout << endl;
        cout << "The user started the trip on: " << rides[rideNo].ride_date.day << "/" << rides[rideNo].ride_date.month
            << "/" << rides[rideNo].ride_date.year << endl;
        cout << "The number of stations the user had ridden is: " << num_of_stations_ridden << endl;
        ++rideNo;
        ++rideID;
        while (true) {
            cout << "Do you want to input another ride? (Y/N): ";
            cin >> repeat;
            if (repeat != "N" && repeat != "n" && repeat != "Y" && repeat != "y") {
                cout << "Invalid choice please try again!\n";
            }
            else {
                break;
            }
        }
        cin.ignore();
    } while (repeat == "Y" || repeat == "y");

}


void wallet(User& user) {
    do {
        cout << "How much do you want to pay? (multiple of 10 and cannot exceed 400)" << endl;
        cin >> user.balance;
        if (user.balance % 10 != 0 || user.balance > 400)
            cout << "error! please enter a valid amount" << endl;
    } while (user.balance % 10 != 0 || user.balance > 400);
    cout << "your balance now is: " << user.balance << endl;
}

int calculatefare(User& user, string stagesnum, string payperiod = "3") {


    int fare = 0;

    if (user.sub.type == "2") {
        if (payperiod == "1") {
            user.sub.ridecount = 60;
            cout << "You have a limit of 60 trips" << endl;

            if (stagesnum == "1")
                return fare = 230;

            else if (stagesnum == "2")
                return fare = 290;

            else if (stagesnum == "3")
                return fare = 340;

            else if (stagesnum == "4")
                return fare = 450;

        }
        else if (payperiod == "12") {
            user.sub.ridecount = 730;
            cout << "You have a limit of 730 trips" << endl;

            if (stagesnum == "1")
                return fare = 1500;

            else if (stagesnum == "2")
                return fare = 2500;

            else if (stagesnum == "3")
                return fare = 3500;

            else if (stagesnum == "4")
                return fare = 4500;

        }

    }
    else if (user.sub.type == "3") {
        wallet(user);
    }
    else if (user.sub.type == "1") {

        user.sub.ridecount = 180;
        cout << "You have a limit of 180 trips" << endl;

        if (stagesnum == "1")
            return fare = 33;

        else if (stagesnum == "2")
            return fare = 41;

        else if (stagesnum == "3")
            return fare = 50;

        else if (stagesnum == "4")
            return fare = 66;

    }

    return fare;
}

void upgradesub(string& stagesnum) {
    string choice1;
    while (true) {
        cout << "what stage do you want to upgrade to?\n" << "1. stage 1\n" << "2. stage 2\n" << "3. stage 3\n"
            << "4. stage 4" << endl;
        cin >> choice1;
        if (choice1 == stagesnum) {
            cout << "error.you already are on ths stage,please choose another" << endl;
        }
        else if (choice1 != "1" && choice1 != "2" && choice1 != "3" && choice1 != "4")
            cout << "Error!this choice is unavailable" << endl;
        else
            break;
    }

    cout << "subscription upgraded succesfully!" << endl;
    cout << "you are now on stage:" << choice1 << endl;
}

int datecalc_renew(User& user, string choice1, string payperiod = "3") {
    if (user.sub.type == "1") {
        if (choice1 == "2") {
            user.sub.enddate = user.sub.startdate;
            user.sub.enddate.month += 6;
            if (user.sub.enddate.month > 12) {
                user.sub.enddate.year++;
                user.sub.enddate.month -= 12;
            }
            return user.sub.enddate.day;
            return user.sub.enddate.month;
            return user.sub.enddate.year;

        }

    }
    else if (user.sub.type == "2") {

        if (choice1 == "2") {
            if (payperiod == "1") {
                user.sub.enddate = user.sub.startdate;
                user.sub.enddate.month += 2;
                if (user.sub.enddate.month > 12) {
                    user.sub.enddate.year++;
                    user.sub.enddate.month -= 12;
                }
            }
            else if (payperiod == "12") {
                user.sub.enddate = user.sub.startdate;
                user.sub.enddate.year += 2;
            }

            return user.sub.enddate.day;
            return user.sub.enddate.month;
            return user.sub.enddate.year;

        }
    }
    return -1;
}

int datecalc_details(User& user, string choice1, string payperiod = "3") {
    if (user.sub.type == "1") {
        user.sub.enddate = user.sub.startdate;
        user.sub.enddate.month += 3;
        if (user.sub.enddate.month > 12) {
            user.sub.enddate.year++;
            user.sub.enddate.month -= 12;

        }

        return user.sub.enddate.day;
        return user.sub.enddate.month;
        return user.sub.enddate.year;
    }
    else if (user.sub.type == "2") {

        if (payperiod == "1") {
            user.sub.enddate = user.sub.startdate;
            user.sub.enddate.month += 1;
            if (user.sub.enddate.month > 12) {
                user.sub.enddate.year++;
                user.sub.enddate.month -= 12;
            }

            return user.sub.enddate.day;
            return user.sub.enddate.month;
            return user.sub.enddate.year;
        }
        else if (payperiod == "12") {
            user.sub.enddate = user.sub.startdate;
            user.sub.enddate.year++;

            return user.sub.enddate.day;
            return user.sub.enddate.month;
            return user.sub.enddate.year;
        }
    }
    return -1;
}

void user_manage_subscription(User& user) {

    string choice1;
    do {
        cout << "1. Display details\n" << "2. Renew subscription\n" << "3. Upgrade subscription" << endl;
        cin >> choice1;
        if (choice1 != "1" && choice1 != "2" && choice1 != "3")
            cout << "Invalid choice. Please choose 1, 2, or 3" << endl;
    } while (choice1 != "1" && choice1 != "2" && choice1 != "3");

    if (user.sub.type == "1") {
        if (choice1 == "1") {
            cout << "Subscription type: Student" << endl;
            cout << "Remaining rides:" << user.sub.ridecount << endl;
            cout << "the start date is:" << user.sub.startdate.day << '/' << user.sub.startdate.month << '/'
                << user.sub.startdate.year << endl;
            cout << "Your subscription expires on:" << endl;
            int result = datecalc_details(user, choice1);
            cout << user.sub.enddate.day << '/' << user.sub.enddate.month << '/' << user.sub.enddate.year << endl;

        }
        else if (choice1 == "2") {
            cout << "subscription type renewed succesfully!" << endl;
            cout << "the start date is:" << user.sub.startdate.day << '/' << user.sub.startdate.month << '/'
                << user.sub.startdate.year << endl;
            cout << "your subscription now expires on:" << endl;
            cout << datecalc_renew(user, choice1);


        }
        else if (choice1 == "3") {
            upgradesub(stagesnum);
        }
    }
    else if (user.sub.type == "2") {
        if (choice1 == "1") {
            cout << "Subscription type: Public" << endl;
            cout << "Remaining rides:" << user.sub.ridecount << endl;
            cout << "Your subscription expires on:" << endl;
            int result = datecalc_details(user, choice1, payperiod);
            cout << user.sub.enddate.day << '/' << user.sub.enddate.month << '/' << user.sub.enddate.year << endl;
        }
        else if (choice1 == "2") {
            cout << "subscription type renewed succesfully!" << endl;
            cout << "the start date is:" << user.sub.startdate.day << '/' << user.sub.startdate.month << '/'
                << user.sub.startdate.year << endl;
            cout << "your subscription now expires on:" << endl;
            int Result = datecalc_renew(user, choice1, payperiod);
            cout << user.sub.enddate.day << '/' << user.sub.enddate.month << '/' << user.sub.enddate.year << endl;
        }
        else if (choice1 == "3") {
            upgradesub(stagesnum);
        }
    }
    else if (user.sub.type == "3") {
        if (choice1 == "1") {
            cout << "Subscription type: wallet" << endl;
            int result = balancecalc(user, stagesnum, choice1);
            cout << "Remaining balance:" << result << endl;
        }
        else if (choice1 == "2") {
            wallet(user);
            cout << "subscription type renewed succesfully!" << endl;

        }
        else if (choice1 == "3") {
            upgradesub(stagesnum);
        }
    }

}

void purchaseSubscription(User& user) {
    while (true) {
        cout << "which subscription type are you choosing?" << endl;
        cout << "1. Student\n" << "2. Public\n" << "3. Wallet" << endl;
        cin >> user.sub.type;
        if (user.sub.type == "1" || user.sub.type == "2" || user.sub.type == "3")
            break;
        else
            cout << "invalid. Please choose 1, 2, or 3" << endl;
    }

    while (true) {
        cout << "Which stage do you plan on choosing?\n" << "1. stage 1\n" << "2. stage 2\n" << "3. stage 3\n"
            << "4. stage 4" << endl;
        cin >> stagesnum;
        if (stagesnum == "1") {
            stations_allowed = 9;
            break;
        }
        else if (stagesnum == "2") {
            stations_allowed = 16;
            break;
        }
        else if (stagesnum == "3") {
            stations_allowed = 23;
            break;
        }
        else if (stagesnum == "4") {
            stations_allowed = 1000;
            break;
        }
        else
            cout << "invalid. Please choose 1, 2, 3, or 4" << endl;

    }
    if (stagesnum == "1" || stagesnum == "2" || stagesnum == "3")
        cout << "Stations allowed: " << stations_allowed << endl;
    else if (stagesnum == "4")
        cout << "unlimited stations" << endl;
    while (true) {
        cout << "enter date of today (day month year): " << endl;
        cin >> user.sub.startdate.day >> user.sub.startdate.month >> user.sub.startdate.year;
        if (user.sub.startdate.day <= 30 && user.sub.startdate.month <= 12)
            break;
        else
            cout << "Invalid date.Please enter a proper date" << endl;
    }
    if (user.sub.type == "2") {
        cout << "what is the pay period you choose? (1 month, 12 months)" << endl;
        cin >> payperiod;
        int result = calculatefare(user, stagesnum, payperiod);
        cout << "pay: " << result << " please" << endl;
    }
    else if (user.sub.type == "1") {
        int result = calculatefare(user, stagesnum, payperiod);
        cout << "pay:" << result << " please" << endl;
    }
    else if (user.sub.type == "3") {
        int result = calculatefare(user, stagesnum, payperiod);
    }

}

void viewRideHistory(User& user) {
    cout << "--------------------------------------------------------------------------------------------\n";
    cout << "Your Ride History: \n";
    cout << "Date: \t \t       RideID: \t \t Check-IN: \t \t Check-OUT: " << endl;
    for (int i = 0; i < rideNo; i++) {
        if (rides[i].user_id == user.userID) {
            cout << rides[i].ride_date.day << "/" << rides[i].ride_date.month << "/" << rides[i].ride_date.year
                << "\t\t";
            cout << rides[i].ride_id << "\t\t" << " ";
            cout << rides[i].checkin << "\t\t" << " ";
            cout << rides[i].checkout << endl;
        }
    }
    cout << "--------------------------------------------------------------------------------------------\n";
}

void userMenu(User& user, RIDE rides[]) {
    string choice;
    do {
        if (user.sub.type == "NO CURRENT SUBSCRIPTION") {
            purchaseSubscription(user);
        }
        else {
            cout << "1. start a ride" << endl;
            cout << "2. Manage Subscription" << endl;
            cout << "3. View Ride History" << endl;
            cout << "4. Update Personal Information" << endl;
            cout << "5. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == "1") {
                checkin_checkout(user, rides, stagesnum, stations_allowed);
            }
            else if (choice == "2") {
                user_manage_subscription(user);
            }
            else if (choice == "3") {
                viewRideHistory(user);
            }
            else if (choice == "4") {
                updatePersonalInfo(user);
            }
            else if (choice == "5") {
                cout << "Logging out..." << endl;
                break;
            }
            else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    } while (choice != "5");
}

int countUsers(User users[]) {
    int count = 0;
    for (int i = 0; i < MAX_USERS; ++i) {
        if (!users[i].username.empty() && users[i].userType == "user") {
            ++count;
        }
    }
    return count;
}

void deleteUser(int useridx) {
    users[useridx - 101].username = "";
    users[useridx - 101].password = "";
    users[useridx - 101].userType = "";
    users[useridx - 101].phoneNo = "";
    users[useridx - 101].userID = -1;
    users[useridx - 101].balance = -1;
    --userCount;
}

void userManagement() {
    if (countUsers(users) == 0) {
        cout << "No users to manage \n";
    }
    string tempchoice = "y";
    while ((tempchoice == "Y" or tempchoice == "y") && countUsers(users) != 0) {
        cout << "Current users count = " << countUsers(users) << endl;
        cout << "USERS ID: \t USERNAMES: \n";
        for (int i = 0; i < MAX_USERS; ++i) {
            if (!users[i].username.empty() && users[i].userType == "user") {
                cout << users[i].userID << "\t \t" << " " << users[i].username << endl;
            }
        }
        int useridx = 0;
        cout << "Select userID to manage: ";
        bool userExists = false;
        while (true && !userExists) {
            cin >> useridx;
            for (int i = 0; i < MAX_USERS; ++i) {
                if (users[i].userID == useridx && users[i].userType == "user") {
                    userExists = true;
                    break;
                }
            }
            if (!userExists)
                cout << "Invalid user ID. Please select a valid user ID.\n";
        }
        cout << "Username :\t" << users[useridx - 101].username << endl;
        cout << "Password :\t" << users[useridx - 101].password << endl;
        cout << "PhoneNo :\t" << users[useridx - 101].phoneNo << endl;
        if (users[useridx - 101].sub.type == "1") {
            cout << "Subscription Type :\t" << "Student" << endl;
            cout << "Remainig rides :\t" << users[useridx - 101].sub.ridecount << endl;
        }
        else if (users[useridx - 101].sub.type == "2") {
            cout << "Subscription Type :\t" << "Public" << endl;
            cout << "Remainig rides :\t" << users[useridx - 101].sub.ridecount << endl;
        }
        else if (users[useridx - 101].sub.type == "3") {
            cout << "Subscription Type :\t" << "Wallet" << endl;
            cout << "Balance :\t" << users[useridx - 101].balance << endl;
        }
        cout << "1.Update personal information or 2.Delete user : ";
        string choice;
        while (true) {
            cin >> choice;
            if (choice == "1") {
                updatePersonalInfo(users[useridx - 101]);
                break;
            }
            else if (choice == "2") {
                deleteUser(useridx);
                cout << "User deleted succesfully!!" << endl;
                if (countUsers(users) == 0) {
                    cout << "No users left to manage \n";
                    break;
                }
                break;
            }
            else {
                cout << "Invalid user choice. Please select a valid choice.\n";
            }

        }
        if (countUsers(users) > 0) {
            cout << "Would you like to manage more accounts? (Y/y || N/n) \n";
            cin >> tempchoice;
            if (tempchoice == "N" or tempchoice == "n") {
                break;
            }
        }
    }
}

int add_subs(subPlan plans[], int& numplan, const string& name, int price, int ridecount) {
    if (numplan < max_num) {
        plans[numplan].type = name;
        plans[numplan].price = price;
        plans[numplan].ridenum = ridecount;
        numplan++;
        cout << "New subscription plan added successfully" << endl;
        return numplan - 1;
    }
    else {
        cout << "Cannot add more plans. Maximum limit reached." << endl;
        return -1;
    }
}

void modify(subPlan plans[], int numplan, const string& type, const string& newname, int newridenum, int newprice) {
    bool found = false;
    for (int i = 0; i < numplan; i++) {
        if (plans[i].type == type) {
            plans[i].type = newname;
            plans[i].ridenum = newridenum;
            plans[i].price = newprice;
            found = true;
            cout << "Subscription plan modified successfully" << endl;
            break;
        }
    }
    if (!found) {

        if (numplan > 0 && plans[numplan - 1].type == type) {
            plans[numplan - 1].type = newname;
            plans[numplan - 1].ridenum = newridenum;
            plans[numplan - 1].price = newprice;
            found = true;
            cout << "Subscription plan modified successfully" << endl;
        }
        else {
            cout << "Subscription plan not found" << endl;
        }
    }
}

void remove_plan(subPlan plans[], int& numplan, const string& type) {
    bool found = false;
    for (int i = 0; i < numplan; i++) {
        if (plans[i].type == type) {
            for (int j = i; j < numplan - 1; ++j) {
                plans[j] = plans[j + 1];
            }
            numplan--;
            found = true;
            cout << "Subscription plan removed successfully" << endl;
            break;
        }
    }
    if (!found)
        cout << "Subscription plan not found" << endl;
}

void display_subscriptions(subPlan plans[], int numplan) {
    cout << "All Subscriptions:" << endl;
    for (int i = 0; i < numplan; ++i) {
        cout << "Type: " << plans[i].type << ", Price: " << plans[i].price << ", Ride Count: " << plans[i].ridenum << endl;
    }
}

void subscriptionmanagement() {
    char choice;
    cout << "Do you want to edit plan subscription? (y/n): ";
    do {
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            cout << "What subscription plan action do you want to perform?" << endl;
            cout << "[1] Add plan" << endl;
            cout << "[2] Modify plan" << endl;
            cout << "[3] Remove plan" << endl;

            int choicee;
            do {
                cin >> choicee;

                switch (choicee) {
                case 1: {
                    string name;
                    int price, ridecount;
                    cout << "Enter subscription name: ";
                    cin >> name;
                    cout << "Enter subscription price: ";
                    cin >> price;
                    cout << "Enter subscription ride number: ";
                    cin >> ridecount;
                    add_subs(PLAN, numplan, name, price, ridecount);
                    display_subscriptions(PLAN, numplan);
                    break;
                }
                case 2: {
                    string type, newname;
                    int newridenum, newprice;
                    cout << "Enter subscription type you want to modify: ";
                    cin >> type;
                    cout << "Enter the new name: ";
                    cin >> newname;
                    cout << "Enter new ride number: ";
                    cin >> newridenum;
                    cout << "Enter new price: ";
                    cin >> newprice;
                    modify(PLAN, numplan, type, newname, newridenum, newprice);
                    display_subscriptions(PLAN, numplan);
                    break;
                }
                case 3: {
                    string type;
                    cout << "Enter subscription type you want to remove: ";
                    cin >> type;
                    remove_plan(PLAN, numplan, type);
                    display_subscriptions(PLAN, numplan);
                    break;
                }
                default:
                    cout << "Invalid choice, try again: ";
                    break;
                }
            } while (choicee != 1 && choicee != 2 && choicee != 3);
        }
        cout << "Do you want to continue? (y/n): " << endl;
    } while (choice == 'y' || choice == 'Y');
    cout << endl;
}

int last1 = 34, last2 = 20, last3 = 23;

void addstation() {
    string newstation;
    string linenum;
    cout << "What line do u want to add stations to??" << endl << "[1-2-3]" << endl;
    do {
        cin >> linenum;
        if (linenum != "1" && linenum != "2" && linenum != "3") {
            cout << "Invalid number,please try again." << endl;
        }
        else
            break;
    } while (linenum != "1" && linenum != "2" && linenum != "3");

    if (linenum == "1") {
        cout << "Enter the name of the station you want to add:" << endl;
        cin.clear();
        cin.ignore();
        getline(cin, newstation);
        first_line[last1] = newstation;
        cout << "------------------------------------------------------------------------------------------------\n";
        cout << "LINE 1 STATIONS: " << endl;
        for (int i = 0; i <= last1; i++) {
            cout << first_line[i] << endl;
        }
        ++last1;
        cout << "------------------------------------------------------------------------------------------------\n";
    }
    else if (linenum == "2") {
        cout << "Enter the name of the station you want to add:" << endl;
        cin.clear();
        cin.ignore();
        getline(cin, newstation);
        second_line[last2] = newstation;
        cout << "------------------------------------------------------------------------------------------------\n";
        cout << "LINE 2 STATIONS: " << endl;
        for (int i = 0; i <= last2; i++) {
            cout << second_line[i] << endl;
        }
        ++last2;
        cout << "------------------------------------------------------------------------------------------------\n";
    }
    else if (linenum == "3") {
        cout << "Enter the name of the station you want to add:" << endl;
        cin.clear();
        cin.ignore();
        getline(cin, newstation);
        third_line[last3] = newstation;
        cout << "------------------------------------------------------------------------------------------------\n";
        cout << "LINE 3 STATIONS: " << endl;
        for (int i = 0; i <= last3; i++) {
            cout << third_line[i] << endl;
        }
        ++last3;
        cout << "------------------------------------------------------------------------------------------------\n";
    }
}

void editstation() {
    for (int i = 0; i < MAX_STATIONS; i++) {
        transform(first_line[i].begin(), first_line[i].end(), first_line[i].begin(),
            [](unsigned char c) { return toupper(c); });
    }
    for (int i = 0; i < MAX_STATIONS; i++) {
        transform(second_line[i].begin(), second_line[i].end(), second_line[i].begin(),
            [](unsigned char c) { return toupper(c); });
    }
    for (int i = 0; i < MAX_STATIONS; i++) {
        transform(third_line[i].begin(), third_line[i].end(), third_line[i].begin(),
            [](unsigned char c) { return toupper(c); });
    }
    string stationbeforeedit;
    string stationafteredit;
    bool found_in_first_line = false;
    bool found_in_second_line = false;
    bool found_in_third_line = false;
    int index = 0;
    cout << "What's the name of the station that you want to edit??" << endl;
    do {
        cin.clear();
        cin.ignore();
        getline(cin, stationbeforeedit);
        transform(stationbeforeedit.begin(), stationbeforeedit.end(), stationbeforeedit.begin(),
            [](unsigned char c) { return toupper(c); });
        for (int i = 0; i < MAX_STATIONS; i++) {
            if (stationbeforeedit == first_line[i]) {
                found_in_first_line = true;
                index = i;
                break;
            }

        }
        if (!found_in_first_line) {
            for (int i = 0; i < MAX_STATIONS; i++) {
                if (stationbeforeedit == second_line[i]) {
                    found_in_second_line = true;
                    index = i;
                    break;
                }
            }
        }
        if (!found_in_first_line && !found_in_second_line) {
            for (int i = 0; i < MAX_STATIONS; i++) {
                if (stationbeforeedit == third_line[i]) {
                    found_in_third_line = true;
                    index = i;
                    break;
                }
            }
        }
        if (!found_in_first_line && !found_in_second_line && !found_in_third_line) {
            cout << "the station you entered doesn't exist in the system. Please try one more time!!" << endl;
        }
    } while (!found_in_first_line && !found_in_second_line && !found_in_third_line);
    cout << "What do you want to convert it to??" << endl;
    getline(cin, stationafteredit);
    if (found_in_first_line) {
        first_line[index] = stationafteredit;
    }
    else if (found_in_second_line) {
        second_line[index] = stationafteredit;
    }
    else if (found_in_third_line) {
        third_line[index] = stationafteredit;
    }

    cout << " Changes done successfully!!!" << endl;
}

void deletestation() {
    for (int i = 0; i < MAX_STATIONS; i++) {
        transform(first_line[i].begin(), first_line[i].end(), first_line[i].begin(),
            [](unsigned char c) { return toupper(c); });
    }
    for (int i = 0; i < MAX_STATIONS; i++) {
        transform(second_line[i].begin(), second_line[i].end(), second_line[i].begin(),
            [](unsigned char c) { return toupper(c); });
    }
    for (int i = 0; i < MAX_STATIONS; i++) {
        transform(third_line[i].begin(), third_line[i].end(), third_line[i].begin(),
            [](unsigned char c) { return toupper(c); });
    }
    string stationname;
    bool found_in_first_line = false;
    bool found_in_second_line = false;
    bool found_in_third_line = false;
    int index = 0;
    cout << "What station do you like to remove??" << endl;
    do {
        cin.clear();
        cin.ignore();
        getline(cin, stationname);
        transform(stationname.begin(), stationname.end(), stationname.begin(),
            [](unsigned char c) { return toupper(c); });
        for (int i = 0; i < MAX_STATIONS; i++) {
            if (stationname == first_line[i]) {
                found_in_first_line = true;
                index = i;
                --last1;
                break;
            }
        }
        if (!found_in_first_line) {
            for (int i = 0; i < MAX_STATIONS; i++) {
                if (stationname == second_line[i]) {
                    found_in_second_line = true;
                    index = i;
                    --last2;
                    break;
                }
            }
        }
        if (!found_in_first_line && !found_in_second_line) {
            for (int i = 0; i < MAX_STATIONS; i++) {
                if (stationname == third_line[i]) {
                    found_in_third_line = true;
                    index = i;
                    --last3;
                    break;
                }
            }
        }
        if (!found_in_first_line && !found_in_second_line && !found_in_third_line) {
            cout << "the station you entered doesn't exist in the system. Please try one more time!!" << endl;
        }
    } while (!found_in_first_line && !found_in_second_line && !found_in_third_line);
    cout << "Station deleted successfully!!" << endl;
    if (found_in_first_line) {
        for (int j = index; j < MAX_STATIONS; j++) {
            if (j == 99) {
                break;
            }
            else {
                first_line[j] = first_line[j + 1];
            }
        }
    }
    if (found_in_second_line) {
        for (int j = index; j < MAX_STATIONS; j++) {
            if (j == 99) {
                break;
            }
            else {
                second_line[j] = second_line[j + 1];
            }
        }
    }
    if (found_in_third_line) {
        for (int j = index; j < MAX_STATIONS; j++) {
            if (j == 99) {
                break;
            }
            else {
                third_line[j] = third_line[j + 1];
            }
        }
    }
}

void stationManagment() {
    string ans;
    string stationmanagment;
    do {
        cout << "Would you like to:" << endl << "1. Add stations." << endl << "2. Edit stations." << endl
            << "3. Remove stations." << endl;
        do {
            cin >> stationmanagment;
            if (stationmanagment != "1" && stationmanagment != "2" && stationmanagment != "3")
                cout << "The number you chose is invalid, please try again." << endl;
            else
                break;
        } while (stationmanagment != "1" && stationmanagment != "2" && stationmanagment != "3");
        if (stationmanagment == "1") {
            addstation();
        }
        else if (stationmanagment == "2") {
            editstation();
        }
        else if (stationmanagment == "3") {
            deletestation();
        }

        cout << "DO U NEED ANY OTHER SERVICES?? (Y/N)" << endl;
        do {
            cin >> ans;
            if (ans == "n" || ans == "N") {
                break;
            }
            else if (ans == "Y" || ans == "y") {
                break;
            }
            else {
                cout << "invalid letter! Please try one more time." << endl;
            }
        } while (ans != "n" && ans != "N" && ans != "y" && ans != "Y");
    } while (ans == "y" || ans == "Y");

}

void ridelogs() {
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "All Ride Logs: " << endl;
    cout << "Date: \t \t       RideID: \t \t Check-IN: \t \t Check-OUT: \t \t UserID: " << endl;
    for (int i = 0; i < rideNo; i++) {
        cout << rides[i].ride_date.day << "/" << rides[i].ride_date.month << "/" << rides[i].ride_date.year << "\t\t";
        cout << rides[i].ride_id << "\t\t" << " ";
        cout << rides[i].checkin << "\t\t" << " ";
        cout << rides[i].checkout << "\t\t" << " ";
        cout << rides[i].user_id << "\n";
    }
    cout << "------------------------------------------------------------------------------------------------\n";
}

void adminMenu(User& user) {
    string choice;
    do {
        cout << "1. User Management" << endl;
        cout << "2. Subscription Plan Management" << endl;
        cout << "3. View All Ride Logs" << endl;
        cout << "4. Station Management" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            userManagement();
        }
        else if (choice == "2") {
            subscriptionmanagement();
        }
        else if (choice == "3") {
            ridelogs();
        }
        else if (choice == "4") {
            stationManagment();
        }
        else if (choice == "5") {
            cout << "Logging out..." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != "5");
}

int login(string username, string password, User users[], int userCount) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == username && users[i].password == password) {
            return users[i].userID;
        }
    }
    return 0;
}

void registerUser(User users[], int& userCount) {
    if (userCount >= MAX_USERS) {
        cout << "Cannot register. Maximum users reached.\n";
        return;
    }

    string username, password, userType, phoneNo;

    while (true) {
        cout << "Enter username: ";
        cin >> username;

        if (doesUsernameExist(username, users, userCount)) {
            cout << "Username already exist. Please choose a different username." << endl;
        }
        else {
            break;
        }
    }

    cout << "Enter password: ";
    password = getPasswordFromConsole();
    string choice;
    while (true) {
        cout << "\nEnter user type (1.admin or 2.user): ";
        cin >> choice;
        if (choice == "1") {
            userType = "admin";
            break;
        }
        else if (choice == "2") {
            userType = "user";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.";
        }
    }


    while (true) {
        cout << "Enter phone number: ";
        cin >> phoneNo;
        if (doesPhoneNoExist(phoneNo, users, userCount)) {
            cout << "Phone number already exist. Please choose a different phone number." << endl;
            continue;
        }

        bool flag = true;
        for (int i = 0; i < phoneNo.size(); i++) {
            if (phoneNo[i] > 57 or phoneNo[i] < 48) {
                flag = false;
                break;
            }
        }
        if (phoneNo.size() != 11 or phoneNo[0] != '0' or phoneNo[1] != '1') {
            flag = false;
        }
        if (flag) {
            break;
        }
        else {
            cout << "Not a valid Phone number. Please write a different phone number." << endl;
        }
    }

    users[userCount].username = username;
    users[userCount].password = password;
    users[userCount].userType = userType;
    users[userCount].userID = id;
    users[userCount].phoneNo = phoneNo;
    ++userCount;
    ++id;

    cout << "User registered successfully.\n";
}

void mainMenu() {
    cout << "Welcome to Metro Mate system :)\n";

    string command;
    while (true) {
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cin >> command;
        if (command == "1") {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            password = getPasswordFromConsole();
            cout << endl;

            if (login(username, password, users, userCount)) {
                cout << "Login successful!\n";
                int tempidx = login(username, password, users, userCount);
                if (users[tempidx - 101].userType == "user") {
                    userMenu(users[tempidx - 101], rides);
                }
                else if (users[tempidx - 101].userType == "admin") {
                    adminMenu(users[tempidx - 101]);
                }
            }
            else {
                cout << "Incorrect username or password. Please try again.\n";
            }
        }
        else if (command == "2") {
            registerUser(users, userCount);
        }
        else if (command == "3") {
            break;
        }
        else {
            cout << "ERROR! Please enter a valid command.\n";
        }
    }
}