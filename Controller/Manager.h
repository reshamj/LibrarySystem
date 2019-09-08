#ifndef managerUI_h
#define managerUI_h

#include "../UserInterfaceLayer/UserInterface.h"
#include "../Model/Book.h"
#include "../Model/User.h"
#include "BookInventory.h"
#include "Customer.h"
#include "Functions.h"
#include "Staff.h"
#include <string>

class ManagerInterface
{

public:
  virtual int AddBook(string name, string isbn, string author, string information, int count) = 0;
  virtual int AddStaff(string name, string username, string password) = 0;
};

// * This class implements methods from ManagerUI class.
// * It contains methods specific to the manager role
class Manager : public ManagerUI, public ManagerInterface, public Functions, public BookInventory, public StaffInterface
{
public:
  virtual int AddBook(string name, string isbn, string author, string information, int count);
  virtual int AddStaff(string name, string username, string password);
  virtual void listbooks();
  virtual void showdetails();
  virtual int returnIssuedBook(string isbn, string username);
  bool isBookAvail(string isbn);
};

#endif