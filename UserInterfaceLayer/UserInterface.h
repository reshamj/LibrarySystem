#ifndef UI_h
#define UI_h

#include <string>

// * This class contains abstract method which is implemented by the system
//   to display the UI to any user that starts the application
class systemUI
{
  public:
    virtual void loginInterface();
    virtual void registrationInterface();
    virtual void startup();
};

// * This class contains abstract method to specific for Customer's user interface
class CustomerUI
{
  public:
    void customerInterface();
};

// * This class contains abstract methods for Staff's UI
class UILayer : public CustomerUI
{
  public:
    void staffInterface();
    virtual void returnBookInterface();
};

class ManagerUI : public UILayer
{
  public:
    void managerInterface();
    virtual void returnBookInterface();
};

#endif