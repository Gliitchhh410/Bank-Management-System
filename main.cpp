#include <iostream>
#include "bank.h"
using namespace std;

int main()
{
    // 1. Create Bank
    Bank *myBank = Bank::getInstance();

    // 2. Create Customer
    cout << "--- Creating Customer ---" << endl;
    myBank->createCustomer("Osama");

    // Get the ID of the customer we just created
    // Note: In a real app, you would know the ID or search by name.
    int osamaId = myBank->Customers.back().getCustomerId();

    // 3. Create Accounts using Factories
    cout << "\n--- Opening Accounts ---" << endl;

    SavingsAccountFactory savingsFactory;
    myBank->openAccount(&savingsFactory, osamaId);

    CheckingAccountFactory checkingFactory;
    myBank->openAccount(&checkingFactory, osamaId);

    // 4. Test Logic
    cout << "\n--- Testing Transactions ---" << endl;

    // Retrieve the customer pointer
    Customer *osama = nullptr;
    for (auto &c : myBank->Customers)
    {
        if (c.getCustomerId() == osamaId)
            osama = &c;
    }

    if (osama)
    {
        // Test Savings (First account)
        if (!osama->Accounts.empty())
        {
            Account *savAcc = osama->Accounts[0];
            cout << "Testing Savings Account (ID: " << savAcc->getAccountNumber() << ")" << endl;
            savAcc->deposit(1000);
            savAcc->withdraw(1500); // Should fail
            savAcc->withdraw(200);  // Should pass
        }

        // Test Checking (Second account)
        if (osama->Accounts.size() > 1)
        {
            Account *checkAcc = osama->Accounts[1];
            cout << "\nTesting Checking Account (ID: " << checkAcc->getAccountNumber() << ")" << endl;
            checkAcc->deposit(100);
            checkAcc->withdraw(400); // Should pass (Overdraft)
            checkAcc->printStatement();
        }
    }

    return 0;
}