#include "Book.h"
#include "BookDataPersistance.h"
#include "DataAccess.h"
#include "Log.h"
#include "Logging.h"
#include "User.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// * Bookvector contains all the books along with related information.
extern vector<Book> Bookvector;

// * IssueBookvector contains all the books that is issued (borrowed or returned)
extern vector<Log> IssuedBookvector;

// * Uservector contains all the user of the system
extern vector<User> Uservector;

vector<Book> Bookvector;
vector<Log> IssuedBookvector;
vector<User> Uservector;

// * This method is called when ever there is any book transaction (borrow or return)
// * It updates book's count in the database file
void DataAccess::UpdateBookData()
{
    ofstream userFile("DataFiles/Books.txt");
    if (userFile.is_open())
    {
        for (auto i : Bookvector)
        {
            userFile << i.getName() + " " + i.getIsbn() + " " + i.getInformation() + " " + i.getInformation() + " " << i.getCount() << endl;
        }

        userFile.close();
    }
    else
    {
        cout << "Unable to open Books.txt file";
    }
}

// * This method updates the logs when ever there is any transaction (borrow or return).
// * It keeps the date of borrow or return of the book aling with the customer name
void DataAccess::UpdateIssueBookData()
{

    ofstream userFile("DataFiles/IssuedBook.txt");
    if (userFile.is_open())
    {
        for (auto i : IssuedBookvector)
        {
            userFile << i.getUsername() + ";" + i.getIsbn() + ";" + i.getBookname() + ";" + i.getIssueDate() + ";" << i.getReturnDate() + ";" << i.getstatus() << endl;
        }

        userFile.close();
    }
    else
    {
        cout << "Unable to open IssueBook.txt file";
    }
}

// * This method returns the updated Book vector which is used to get the latest data present in the database.
vector<Book> DataAccess ::LoadBookData()
{
    Book oldbook;
    string str;

    ifstream fin("DataFiles/Books.txt"); // Open and read Book.txt
    if (!fin)
    { // If can't open
        cerr << "Books.txt can't open" << endl;
        abort(); // Exit
    }
    while (getline(fin, str))
    {
        size_t i = str.find(" ");          // Find fisrt spacebar
        oldbook.setName(str.substr(0, i)); // Divide str by spacebar and get bookname
        str = str.substr(i + 1);

        i = str.find(" ");                 // Find second spacebar
        oldbook.setIsbn(str.substr(0, i)); // Divide str by spacebar and get ISBN number
        str = str.substr(i + 1);

        i = str.find(" ");
        oldbook.setAuthor(str.substr(0, i)); // Divide str by spacebar and get author
        str = str.substr(i + 1);

        i = str.find(" ");
        oldbook.setInformation(str.substr(0, i)); // Divide str by spacebar and get Information
        str = str.substr(i + 1);

        i = str.find(" ");
        oldbook.setCount(stoi(str.substr(0, i))); // Divide str by spacebar and get count
        Bookvector.push_back(oldbook);            // Add to Bookvector
    }
    fin.close(); // Close Books.txt
    return Bookvector;
}

// * This method returns book Log which is used to track the book transaction
vector<Log> DataAccess ::LoadIssueBookData()
{
    Log oldlog;
    string str;

    ifstream fin("DataFiles/IssuedBook.txt"); // Open and read Book.txt
    if (!fin)
    { // If can't open
        cerr << ".txt can't open" << endl;
        abort(); // Exit
    }
    while (getline(fin, str))
    {
        size_t i = str.find(";");             // Find fisrt spacebar
        oldlog.setUsername(str.substr(0, i)); // Divide str by spacebar and get bookname
        str = str.substr(i + 1);

        i = str.find(";");                // Find second spacebar
        oldlog.setIsbn(str.substr(0, i)); // Divide str by spacebar and get ISBN number
        str = str.substr(i + 1);

        i = str.find(";");
        oldlog.setBookname(str.substr(0, i)); // Divide str by spacebar and get author
        str = str.substr(i + 1);

        i = str.find(";");
        oldlog.setIssueDate(str.substr(0, i)); // Divide str by spacebar and get Information
        str = str.substr(i + 1);

        i = str.find(";");
        oldlog.setReturnDate(str.substr(0, i)); // Divide str by spacebar and get Information
        str = str.substr(i + 1);

        i = str.find(";");
        oldlog.setstatus(str.substr(0, i)); // Divide str by spacebar and get count

        IssuedBookvector.push_back(oldlog); // Add to Bookvector
    }
    fin.close();
    return IssuedBookvector;
}

// * This method returns the updated User vector which is used to get the latest user present in the database.
vector<User> DataAccess::LoadUserData()
{
    User olduser;
    string str;

    ifstream fin("DataFiles/User.txt"); // Open and read User.txt
    if (!fin)
    { // If can't open
        cerr << "User.txt can't open" << endl;
        abort(); // Exit
    }
    while (getline(fin, str))
    {
        size_t i = str.find(" ");          // Find fisrt spacebar
        olduser.setname(str.substr(0, i)); // Divide str by spacebar and get name
        str = str.substr(i + 1);

        i = str.find(" ");                     // Find second spacebar
        olduser.setusername(str.substr(0, i)); // Divide str by spacebar and get userID
        str = str.substr(i + 1);

        i = str.find(" ");                     // Find second spacebar
        olduser.setpassword(str.substr(0, i)); // Divide str by spacebar and get password

        olduser.setStatus(str.substr(i + 1)); // Divide str by spacebar and get status

        Uservector.push_back(olduser); // Add to lib.UserArray
    }
    fin.close(); // Close User.txt
    return Uservector;
}

// * This method is used to Add a new user in the database
void DataAccess::AddUser(string name, string username, string password)
{
    User olduser;
    olduser.setname(name);
    olduser.setusername(username);
    olduser.setpassword(password);
    olduser.setStatus("3");
    Uservector.push_back(olduser);

    ofstream userFile("DataFiles/User.txt", std::ofstream::out | std::ofstream::app);
    if (userFile.is_open())
    {
        userFile << name + " " + username + " " + password + " 3"
                 << "\n";

        userFile.close();
    }
    else
    {
        cout << "Unable to open User.txt file";
    }
}

// string DataAccess::ExternalBookRequest(string username, string isbn, string libraryname)
// {
//     string status = "NO";

//     ofstream userFile("DataFiles/ExternalInterfaceLogs.txt", std::ofstream::out | std::ofstream::app);
//     if (userFile.is_open())
//     {
//         userFile << username+";"+isbn +";"+libraryname  << endl;
//         userFile.close();
//         status = "YES";
//     }
//     else
//     {
//         cout << "Unable to open Books.txt file";
//     }

//     return status;
// }