#ifndef customerUI_h
#define customerUI_h

#include "../UserInterfaceLayer/UserInterface.h"
#include "BookInventory.h"
#include "ExternalSystem.h"
#include <string>

class CustomerInterface
{
  public:
    virtual int RequestBookLoan(std::string isbn) = 0;
    virtual bool isAvailable(std::string isbn) = 0;
    virtual bool isAlreadyissued(std::string isbn) = 0;
};

// * This class implements methods from CustomerUI class.
// * It contains methods specific to the customer
class Customer : public CustomerUI, public CustomerInterface, public BookInventory
{
  public:
    virtual int RequestBookLoan(std::string isbn);
    virtual bool isAvailable(std::string isbn);
    virtual bool isAlreadyissued(std::string isbn);
    virtual void listbooks();
    virtual void showdetails();
    //virtual std::string ExternalBookRequest(std::string username, std::string isbn, std::string externallibrary);
};

#endif