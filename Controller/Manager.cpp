#include "Manager.h"
#include "../Model/DataAccess.h"
#include "../Model/Book.h"
#include "../Model/User.h"
#include "Functions.h"
#include "../Model/Log.h"

#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

extern vector<Book> Bookvector;
extern vector<Log> IssuedBookvector;
extern string loggedinUser;
extern vector<User> Uservector;

DataAccess acdata;

// * This method duisplays the home interface for the staff user
void ManagerUI::managerInterface()
{
    int i;
    cout << "\n\t*********** LIBRARY MANAGEMENT SYSTEM - Manager Interface ***********\n";
    cout << "\n\t\t>>Please Choose Any Option \n";
    cout << "\n\t\t1.Books Availability\n\n\t\t2.Return Issued Book\n\n\t\t3.View Checkout Log\n\n\t\t4.Add Book\n\n\t\t5.Add Staff\n\n\t\t6.Log out\n\n\t\t7.Close Application\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "................";
        cin >> i;
    }

    if (i == 1)
    {
        Manager m;
        m.listbooks();
    }
    else if (i == 2)
    {
        returnBookInterface();
    }
    else if (i == 3)
    {
        Manager m;
        m.showdetails();
    }
    else if (i == 4)
    {
        string name, isbn, author, information;
        int count;

        int i, addbook;
        cout << "\n\t*********** LIBRARY MANAGEMENT SYSTEM - Manager Interface ***********\n";
        cout << "\n\t\t>>You have choose Add Staff:  \n";
        cout << "\n\t\tEnter name of Book:";
        cin >> name;
        cout << "\n";
        cout << "\n\t\tEnter ISBN of Book:";
        cin >> isbn;
        cout << "\n";
        cout << "\n\t\tEnter authors of Book:";
        cin >> author;
        cout << "\n";
        cout << "\n\t\tEnter Information about Book:";
        cin >> information;
        cout << "\n";
        cout << "\n\t\tEnter number of Book available:";
        cin >> count;
        cout << "\n";

        Manager manager;

        bool bookexist = manager.isBookAvail(isbn);

        if (!bookexist)
        {

            addbook = manager.AddBook(name, isbn, author, information, count);

            if (addbook == 1)
            {
                cout << "\n\t*****************************************************************************************\n";
                cout << "\t\tBook added Successfully: :)\n\n";
                cout << "\n\t*****************************************************************************************\n";
                managerInterface();
            }
            else
            {
                cout << "\n\t*****************************************************************************************\n";
                cout << "\t\tTrouble Entering book into system :(\n\n";
                cout << "\n\t*****************************************************************************************\n";
                managerInterface();
            }
        }
        else
        {

            cout << "\n\t*****************************************************************************************\n";
            cout << "\t\tBook already exists into system :(\n\n";
            cout << "\n\t*****************************************************************************************\n";
            managerInterface();
        }
    }
    else if (i == 5)
    {
        string name, username, passowrd;

        int i, addstaff;
        cout << "\n\t*********** LIBRARY MANAGEMENT SYSTEM - Manager Interface ***********\n";
        cout << "\n\t\t>>You have choose Add Staff:  \n";
        cout << "\n\t\tEnter name of Staff member:";
        cin >> name;
        cout << "\n";
        cout << "\n\t\tEnter Username for Staff member:";
        cin >> username;
        cout << "\n";
        cout << "\n\t\tEnter password for Staff member:";
        cin >> passowrd;
        cout << "\n";

        Manager manager;

        bool userexist = manager.isUserExist(username);

        if (!userexist)
        {

            addstaff = manager.AddStaff(name, username, passowrd);

            if (addstaff == 1)
            {
                cout << "\n\t*****************************************************************************************\n";
                cout << "\t\tStaff member added Successfully: :)\n\n";
                cout << "\n\t*****************************************************************************************\n";
                managerInterface();
            }
            else
            {
                cout << "\n\t*****************************************************************************************\n";
                cout << "\t\tStaff member not entered successfully :(\n\n";
                cout << "\n\t*****************************************************************************************\n";
                managerInterface();
            }
        }
        else
        {

            cout << "\n\t*****************************************************************************************\n";
            cout << "\t\tStaff member already exists :(\n\n";
            cout << "\n\t*****************************************************************************************\n";
            managerInterface();
        }
    }
    else if (i == 6)
    {
        Functions functions;
        functions.startup();
    }
    else if (i == 7)
    {
        exit(0);
    }
    else
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\n\t\tPlease enter correct option :(\n";
        cout << "\n\t*****************************************************************************************\n";
        staffInterface();
    }
}
/* This method displayes the book to the manager*/
void Manager::listbooks()
{
    int i;
    cout << "Books Availability in the System:" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|       ISBN       |             Name            |      Author      |           Information           |   Availability    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
    for (auto i : Bookvector)
    {

        cout << "|" << setw(18) << i.getIsbn() << "|" << setw(29) << i.getName() << "|"
             << setw(18) << i.getAuthor() << "|" << setw(33) << i.getInformation() << "|" << setw(19) << i.getCount() << "|" << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------\n\n"
         << endl;

    cout << "1.Home\t\t\t 2. Log out\t\t\t3. Close Application\n\n";
    cout << "Choose the option: ";
    cin >> i;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << ".........";
        cin >> i;
    }

    if (i == 1)
    {
        managerInterface();
    }

    else if (i == 2)
    {
        Functions functions;
        functions.startup();
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
        listbooks();
    }
}

/*
This method is used to display UI for returning the book
*/
void ManagerUI::returnBookInterface()
{
    string username, isbn;

    int i, retbook;
    cout << "\n\t*********** LIBRARY MANAGEMENT SYSTEM - Staff Interface ***********\n";
    cout << "\n\t\t>>Return Book Interface \n";
    cout << "\n\t\tEnter ISBN number of Book : ";
    cin >> isbn;
    cout << "\n\t\tEnter Username of Book Borrower : ";
    cin >> username;

    Manager mg;
    retbook = mg.returnIssuedBook(isbn, username);

    if (retbook == 1)
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\t\tBook Returned Successfully: :)\n\n";
        cout << "\n\t*****************************************************************************************\n";
        managerInterface();
    }
    else
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\t\tThe book you are trying to return is not found in log :(\n\n";
        cout << "\n\t*****************************************************************************************\n";
        returnBookInterface();
    }
}

/*
This method displayes thhe details about the books and its availability
*/
void Manager::showdetails()
{
    int i;
    cout << "This is the details:" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|     Username     |       ISBN       |             BookName            |      IssueDate      |        ReturnDate       |      Status      |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (auto i : IssuedBookvector)
    {

        cout << "|" << setw(18) << i.getUsername() << "|" << setw(18) << i.getIsbn() << "|" << setw(33) << i.getBookname() << "|"
             << setw(21) << i.getIssueDate() << "|" << setw(25) << i.getReturnDate() << "|" << setw(18) << i.getstatus() << "|" << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\n\n"
         << endl;

    cout << "1.Home\t\t\t 2. Log out\t\t\t3. Close Application\n\n";
    cout << "Choose the option: ";
    cin >> i;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << ".........";
        cin >> i;
    }
    if (i == 1)
    {
        managerInterface();
    }

    else if (i == 2)
    {
        Functions functions;
        functions.startup();
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
        showdetails();
    }
}

/*This method adds the staff user in the system*/
int Manager::AddStaff(string name, string username, string password)
{
    User staffmember;
    staffmember.setname(name);
    staffmember.setusername(username);
    staffmember.setpassword(password);
    staffmember.setStatus("2");
    Uservector.push_back(staffmember);

    ofstream userFile("DataFiles/User.txt", std::ofstream::out | std::ofstream::app);
    if (userFile.is_open())
    {
        userFile << name + " " + username + " " + password + "2"
                 << "\n";

        userFile.close();
        return 1;
    }
    else
    {
        cout << "Unable to open User.txt file";
        return 0;
    }

    return 1;
}

/*This method adds books in the database*/
int Manager::AddBook(string name, string isbn, string author, string information, int count)
{

    Book oldbook;
    oldbook.setName(name);
    oldbook.setIsbn(isbn);
    oldbook.setAuthor(author);
    oldbook.setInformation(information);
    oldbook.setCount(count);

    Bookvector.push_back(oldbook);
    string ct = to_string(count);

    ofstream userFile("DataFiles/Books.txt", std::ofstream::out | std::ofstream::app);
    if (userFile.is_open())
    {
        userFile << name + " " + isbn + " " + author + " " + information + " " + ct
                 << "\n";

        userFile.close();
        return 1;
    }
    else
    {
        cout << "Unable to open User.txt file";
        return 0;
    }

    return 1;
}

/*This method is used to check if the book is available */
bool Manager::isBookAvail(string isbn)
{
    bool availability = false;

    for (auto i : Bookvector)
    {
        if (i.getIsbn() == isbn)
        {
            // if book is present, then it checks if the count is greater than 0.
            // If count is 0 then the book is not available
            if (i.getCount() > 0)
            {
                bool availability = true;
                return availability;
            }
        }
    }
    return availability;
}

/*This method is used to return the book issues by the customer*/
int Manager::returnIssuedBook(string isbn, string username)
{
    int ret = 0;

    for (int i = 0; i < IssuedBookvector.size(); i++)
    {
        //checks the IssuedBookvector to see if the the book with given isbn is issued to the customer with the given username
        if (IssuedBookvector[i].getIsbn() == isbn && IssuedBookvector[i].getUsername() == username && IssuedBookvector[i].getstatus() == "checked-out")
        {
            IssuedBookvector[i].setstatus("returned");
            acdata.UpdateIssueBookData();
            ret = 1;

            //increases the count of the book from Bookvector after it is returned and update the database
            for (int j = 0; j < Bookvector.size(); j++)
            {
                if (Bookvector[j].getIsbn() == isbn)
                {

                    Bookvector[j].setCount(Bookvector[j].getCount() + 1);
                    acdata.UpdateBookData();
                }
            }
            return ret;
        }
    }
    return ret;
}