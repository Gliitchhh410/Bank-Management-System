#include <iostream>
#include <vector>
#include <string>
#include "bank.h"
using namespace std;



/*----------------------------------Bank---------------------------------------*/

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
    int newAccId = rand() % 10000;

    newAccount = factory->createAccount(newAccId);

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
    newCustomer.setCustomerId(rand() % 10000);
    Customers.push_back(move(newCustomer)); // move for passing objects without creating extra copies
}


/*----------------------------------Customer---------------------------------------*/



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



/*----------------------------------Transaction---------------------------------------*/
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




/*----------------------------------Account---------------------------------------*/


Account::Account(int accNum){
    this->balance = 0.0;
    this->accountNumber = accNum;
}

void Account::addTransaction(TRANSACTION_TYPE type, double amount){
    int txId = rand() % 10000;
    Transaction newTx(txId, amount, type);
    transactionHistroy.push_back(newTx);
}


int Account::getAccountNumber(){
    return accountNumber;
}





/*----------------------------------CheckingAccount---------------------------------------*/

Account *CheckingAccountFactory::createAccount(int id)
{
    return new CheckingAccount(id);
}


CheckingAccount::CheckingAccount(int id): Account(id){
    this->overdraftLimit = 500.0;
}



/*----------------------------------SavingsAccount---------------------------------------*/

SavingsAccount::SavingsAccount(int id): Account(id){
    this->interestRate = 0.05;
}
Account *SavingsAccountFactory::createAccount(int id)
{
    return new SavingsAccount(id);
}

