#include "Functions.h"
#include "Staff.h"
#include "Customer.h"
#include "Manager.h"
#include "../Model/Log.h"
#include "../Model/DataAccess.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Staff staff;
Customer customer;
Manager manager;
DataAccess dAccessF;

extern vector<User> Uservector;
extern vector<Book> Bookvector;
// vector<Book> Bookvector;
extern vector<Log> IssuedBookvector;
extern string loggedinUser;

int Functions::login(string username, string password)
{
    //by default transferring to the customer interface
    int status = 0;

    for (auto i : Uservector)
    {
        if (i.getusername() == username && i.getpasswd() == password)
        {
            loggedinUser = i.getusername();
            return stoi(i.getStatus()); // Return status
        }
    }

    return status;
}

bool Functions::isUserExist(string username)
{
    for (size_t i = 0; i < Uservector.size(); i++)
    {
        if (Uservector[i].getusername() == username)
        { // If find that username, return registerstatus as 0
            cout << "\n\t*****************************************************************************************\n";
            cout << "User already exist! " << endl;
            cout << "\n\t*****************************************************************************************\n";
            return true;
        }
    }

    return false;
}

int Functions::registration(string name, string username, string password)
{

    int registerstatus = 0;
    if (isUserExist(username))
    {

        return registerstatus;
    }
    else
    {
        registerstatus = 1;
        dAccessF.AddUser(name, username, password);
    }

    return registerstatus;
}

void systemUI::loginInterface()
{

    //this is login Interface for all the entity of system
    string username;
    string passwd;
    int status;

    cout << "\n\t*********** LIBRARY MANAGEMENT SYSTEM ***********\n";
    //cout << "\n\t\t>>This is Login Interface \n";
    cout << "\n\t\tUsername:";
    cin >> username;
    cout << "\n\t\tPassword:";
    cin >> passwd;

    Functions f;
    status = f.login(username, passwd);

    //cout << "status is:" + status;
    //status = 9;
    if (status == 1)
    {
        manager.managerInterface();
    }
    if (status == 2)
    {
        staff.staffInterface();
    }

    if (status == 3)
    {
        customer.customerInterface();
    }
    else
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\t\tError... The identity of user is not defined. :(\n";
        cout << "";
        cout << "\n\t*****************************************************************************************\n";
        startup();
    }
}

void systemUI::registrationInterface()
{

    int registerstatus;
    string userID, password, name;
    cout << "\n\t*********** NEW  USER  REGISTERATION  ***********\n";
    cout << "\n\t\t>>Please provide the following details to Register \n";
    cout << "\n\t\tName:";
    cin >> name;
    cout << "\n\t\tEnter desired User ID:";
    cin >> userID;
    cout << "\n\t\tEnter password:";
    cin >> password;

    Functions f;
    registerstatus = f.registration(name, userID, password);

    if (registerstatus == 1)
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\n\t\tThank you for registering, Please login into the system\n";
        cout << "\n\t*****************************************************************************************\n";
        dAccessF.LoadUserData();
        startup();
    }
    else
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\n\t\tRequested Username is not available in the system, please try again... :(\n";
        cout << "\n\t*****************************************************************************************\n";
        startup();
    }
}

void systemUI::startup()
{

    int i;
    cout << "\n\t*********** LIBRARY MANAGEMENT SYSTEM - Startup Interface ***********\n";
    cout << "\n\t\t>>Please Choose Any Option \n";
    cout << "\n\t\t1.Login\n\n\t\t2.Register\n\n\t\t3.Close Application\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    while (cin.fail())
    {

        cin.clear();
        cin.ignore();
        cout << "\n\t*****************************************************************************************\n";
        cout << "\n\t\tPlease enter correct option :(\n";
        startup();
        cin >> i;
    }

    if (i == 1)
    {
        loginInterface();
    }
    else if (i == 2)
    {
        registrationInterface();
    }

    else if (i == 3)
    {
        exit(0);
    }
    else
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\n\t\tPlease enter correct option :(\n";
        cout << "\n\t*****************************************************************************************\n";
        startup();
    }
}
