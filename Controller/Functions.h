#ifndef functions_h
#define functions_h

#include "../Model/Book.h"
#include "../Model/User.h"
#include "../UserInterfaceLayer/UserInterface.h"
#include <vector>

class SystemFunctionInterface
{

  public:
    virtual int login(string username, string passwd) = 0;
    virtual int registration(string name, string username, string password) = 0;
};

// * This class implements methods that acts as starting point to the system.
class Functions : public systemUI, public SystemFunctionInterface
{
  public:
    virtual int login(string username, string passwd);
    virtual int registration(string name, string username, string password);
    bool isUserExist(string username);
};

#endif
