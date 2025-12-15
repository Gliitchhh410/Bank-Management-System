#include <iostream>
#include <vector>
#include <string>
#include "bank.h"
using namespace std;

void Bank::openAccount(AccountFactory *factory, int customerId)
{
    Customer *targetCustomer = nullptr;

    for (auto &cust : Customers)
    {
        if (cust.getCustomerId() == customerId)
        {
            targetCustomer = &cust;
            break;
        }
    }

    if (!targetCustomer)
    {
        cout << "Error: Customer ID not found" << endl;
        return;
    }

    Account *newAccount = nullptr;
    int newAccId = rand() * 1000;

    newAccount = factory->createAccount();

    if (newAccount != nullptr)
    {
        targetCustomer->addAccount(newAccount);
        cout << "account created successfully!!" << endl;
    }
}

void Bank::createCustomer(string name)
{
    Customer newCustomer;

    newCustomer.setName(name);
    newCustomer.setCustomerId(rand() * 1000);
    Customers.push_back(move(newCustomer)); // move for passing objects without creating extra copies
}

void Customer::setName(string n)
{
    name = n;
}

void Customer::setCustomerId(int d)
{
    customerId = d;
}

int Customer::getCustomerId()
{
    return customerId;
}

void Customer::addAccount(Account *acc)
{
    Accounts.push_back(acc);
}

Account *Customer::getAccount(int accountNumber)
{
    for (auto &acc : Accounts)
    {
        if (accountNumber == acc->getAccountNumber())
        {
            return acc;
        }
    }

    return nullptr;
}

string Transaction::getDetails()
{
    return "Transaction Number: " + to_string(transactionId) + ", Amount: " + to_string(amount);
}

Transaction::Transaction(int transactionId, double amount, TRANSACTION_TYPE type)
{
    this->transactionId = transactionId;
    this->amount = amount;
    this->type = type;
}

Account *CheckingAccountFactory::createAccount()
{
    return new CheckingAccount;
}

Account *SavingsAccountFactory::createAccount()
{
    return new SavingsAccount;
}
