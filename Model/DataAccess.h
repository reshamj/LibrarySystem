#ifndef service_h
#define service_h

#include "BookDataPersistance.h"
#include "Book.h"
#include "Log.h"
#include "Logging.h"
#include "../Controller/ExternalSystem.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DataAccessInterface
{

public:
  virtual vector<User> LoadUserData() = 0;
  virtual void AddUser(string name, string username, string password) = 0;
};

// * This class acts as a DataAccess Layer.
// * This is a bridge between the Database and the business login of the application
// * It contains methods to Log user data and add new user in the account
class DataAccess : public BookDataPersistance, public Logging, public DataAccessInterface
{
public:
  vector<User> LoadUserData();
  void AddUser(string name, string username, string password);
  vector<Log> LoadIssueBookData();
  void UpdateIssueBookData();
  vector<Book> LoadBookData();
  void UpdateBookData();
  //virtual string ExternalBookRequest(string username, string isbn,string libraryname);
};

#endif
