#include <iostream>
#include "bank.h"

using namespace std;

int main()
{
    // 1. Setup Bank
    Bank myBank;

    // 2. Create a Customer
    myBank.createCustomer("Osama");
    // We assume the ID generated is accessible or printed.
    // For this test, let's assume the ID generated was handled internally or we just guess it's the first one.
    // NOTE: In your code, createCustomer generates a random ID.
    // You might want to print that ID so the user knows what it is!

    int customerId = myBank.Customers[0].getCustomerId(); // Hack to get the ID for testing
    cout << "Customer created with ID: " << customerId << endl;

    // 3. Use the FACTORY PATTERN to create accounts

    // Create a Savings Account
    SavingsAccountFactory savingsFactory;
    myBank.openAccount(&savingsFactory, customerId);

    // Create a Checking Account
    CheckingAccountFactory checkingFactory;
    myBank.openAccount(&checkingFactory, customerId);

    // 4. Retrieve the Customer pointer
    Customer *osama = nullptr;
    for (auto &c : myBank.Customers)
    {
        if (c.getCustomerId() == customerId)
            osama = &c;
    }

    // 5. Test Operations
    if (osama)
    {
        // Get the first account (Savings)
        Account *acc1 = osama->getAccount(0);
        cout << "\n--- Testing Savings (Acc ID: " << acc1->getAccountNumber() << ") ---" << endl;
        acc1->deposit(500);
        acc1->withdraw(200);
        acc1->withdraw(1000); // Should Fail

        // Get the second account (Checking)
        Account *acc2 = osama->getAccount(1);
        cout << "\n--- Testing Checking (Acc ID: " << acc2->getAccountNumber() << ") ---" << endl;
        acc2->deposit(100);
        acc2->withdraw(400); // Should Work (Overdraft)

        acc2->printStatement();
    }

    return 0;
}