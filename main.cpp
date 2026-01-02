#include <iostream>
#include <thread>
#include "bank.h"

using namespace std;

int main()
{
    Bank *myBank = Bank::getInstance();

    // 1. Create two customers
    myBank->createCustomer("Alice");
    myBank->createCustomer("Bob");

    // In a real app, we'd search by name, but here we grab the IDs directly
    int aliceId = myBank->Customers[0].getCustomerId();
    int bobId = myBank->Customers[1].getCustomerId();

    // 2. Give them accounts
    CheckingAccountFactory checkingFactory;

    // Alice gets an account
    myBank->openAccount(&checkingFactory, aliceId);

    // Bob gets an account
    myBank->openAccount(&checkingFactory, bobId);

    // 3. Get pointers to accounts (for testing/setup)
    Account *aliceAcc = myBank->Customers[0].Accounts[0];
    Account *bobAcc = myBank->Customers[1].Accounts[0];

    // 4. Setup Money
    aliceAcc->deposit(1000); // Alice has 1000
    bobAcc->deposit(500);    // Bob has 500

    cout << "\n--- Before Transfer ---" << endl;
    cout << "Alice Balance: 1000" << endl;
    cout << "Bob Balance: 500" << endl;

    // 5. Perform Transfer (Alice -> Bob)
    // CRITICAL UPDATE: We now pass the Account Number (int), not the pointer.
    cout << "\n--- Transferring 300 from Alice to Bob ---" << endl;
    bool result = aliceAcc->Transfer(bobAcc->getAccountNumber(), 300);

    if (result)
    {
        cout << "Transaction Completed!" << endl;
    }
    else
    {
        cout << "Transaction Failed!" << endl;
    }

    // 6. Verify with Statements
    cout << "\n--- Final Statements ---" << endl;
    aliceAcc->printStatement();
    bobAcc->printStatement();

    return 0;
}