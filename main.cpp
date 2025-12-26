#include <iostream>
#include <thread> // Required for creating threads
#include "bank.h"

using namespace std;

// This is a "worker function" that the thread will execute
void attemptWithdraw(Account *acc, double amount)
{
    // This thread simulates a user trying to withdraw money
    cout << "Thread: Attempting to withdraw " << amount << "..." << endl;
    acc->withdraw(amount);
}

int main()
{
    // 1. Setup Bank (Singleton)
    Bank *myBank = Bank::getInstance();
    myBank->createCustomer("SharedUser");
    int userId = myBank->Customers.back().getCustomerId();

    SavingsAccountFactory factory;
    myBank->openAccount(&factory, userId);

    Customer *user = &myBank->Customers.back();
    Account *sharedAcc = user->Accounts[0];

    // 2. Initial Deposit: 1000
    cout << "\n--- Initial Deposit ---" << endl;
    sharedAcc->deposit(1000);

    // 3. START MULTITHREADING
    cout << "\n--- Starting Concurrent Withdrawals ---" << endl;
    cout << "Scenario: Two threads trying to withdraw 800 each at the EXACT same time." << endl;

    // Create Thread 1 (e.g., ATM)
    thread t1(attemptWithdraw, sharedAcc, 800);

    // Create Thread 2 (e.g., Mobile App)
    thread t2(attemptWithdraw, sharedAcc, 800);

    // 4. WAIT for threads to finish (Join)
    // "Join" blocks the main function until t1 and t2 are done.
    t1.join();
    t2.join();

    // 5. Final Result
    cout << "\n--- Final Result ---" << endl;
    sharedAcc->printStatement();

    return 0;
}