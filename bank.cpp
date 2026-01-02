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

Bank::Bank() {}

Bank *Bank::instance = nullptr;

Bank *Bank::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Bank(); // can only be initialized here
    }
    return instance;
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

Account::Account(int accNum)
{
    this->balance = 0.0;
    this->accountNumber = accNum;
}

Account::~Account() {};

void Account::addTransaction(TRANSACTION_TYPE type, double amount)
{
    int txId = rand() % 10000;
    Transaction newTx(txId, amount, type);
    transactionHistroy.push_back(newTx);
}

int Account::getAccountNumber()
{
    return accountNumber;
}

Account *Account::getAccountByAccountNumber(int accNum)
{
    Bank *Bank = Bank::getInstance();
    for (auto &cust : Bank->Customers)
    {
        for (auto &acc : cust.Accounts)
        {
            if (acc->getAccountNumber() == accNum)
            {
                return acc;
            }
        }
    }
    return nullptr;
}

void Account::setAccountNumber(int accNum)
{
    accountNumber = accNum;
}

bool Account::Transfer(int accNum, double Amount)
{
    Account *toAccount = Account::getAccountByAccountNumber(accNum);
    if (toAccount == nullptr)
    {
        cout << "Transfer Failed: Wrong Account Number" << endl;
        return false;
    }

    if (this == toAccount)
    {
        cout << "Error: Cannot transfer to self." << endl;
        return false;
    }

    lock(this->accMutex, toAccount->accMutex);
    lock_guard<mutex> lock1(this->accMutex, adopt_lock);
    lock_guard<mutex> lock2(toAccount->accMutex, adopt_lock);

    bool canWithdraw = false;

    if (this->balance > Amount)
    {
        canWithdraw = true;
    }
    else
    {
        CheckingAccount *ca = dynamic_cast<CheckingAccount *>(this);
        if (ca && (this->balance + 500.0 >= Amount))
        {
            canWithdraw = true;
        }
    }

    if (canWithdraw)
    {
        this->balance -= Amount;
        toAccount->balance += Amount;

        this->addTransaction(TRANSFER_OUT, Amount);
        toAccount->addTransaction(TRANSFER_IN, Amount);

        cout << "Transfer of " << Amount << " successful!" << endl;
        return true;
    }

    cout << "Transfer failed: Insufficient funds." << endl;
    return false;
}

void Account::deposit(double amount)
{
    lock_guard<mutex> lock(accMutex);
    if (amount < 0)
        cout << "Invalid negative deposit";
    return;

    balance += amount;
    addTransaction(DEPOSIT, amount);
    cout << "Deposited: " << amount << ". New Balance: " << balance << endl;
}

void Account::printStatement()
{
    lock_guard<mutex> lock(accMutex);
    cout << "--- Statement for Account " << accountNumber << " ---" << endl;
    cout << "Current Balance: " << balance << endl;
    for (auto &tx : transactionHistroy)
    {
        cout << tx.getDetails() << endl;
        cout << "-----------------------------------" << endl;
    }
}

/*----------------------------------CheckingAccount---------------------------------------*/

Account *CheckingAccountFactory::createAccount(int id)
{
    return new CheckingAccount(id);
}

bool CheckingAccount::withdraw(double amount)
{
    lock_guard<mutex> lock(accMutex);
    if (balance + overdraftLimit >= amount)
    {
        balance -= amount;
        addTransaction(WITHDRAW, amount);
        cout << "Withdrew: " << amount << ". New Balance: " << balance << endl;
        return true;
    }
    else
    {
        cout << "Error: Exceeded Overdraft Limit" << endl;
        return false;
    }
}

CheckingAccount::CheckingAccount(int id) : Account(id)
{
    this->overdraftLimit = 500.0;
}

/*----------------------------------SavingsAccount---------------------------------------*/

SavingsAccount::SavingsAccount(int id) : Account(id)
{
    this->interestRate = 0.05;
}

bool SavingsAccount::withdraw(double amount)
{
    lock_guard<mutex> lock(accMutex);
    if (balance >= amount)
    {
        balance -= amount;
        addTransaction(WITHDRAW, amount);
        cout << "Withdrew: " << amount << ". New Balance: " << balance << endl;
        return true;
    }
    else
    {
        cout << "Error: Insufficient funds (Savings)" << endl;
        return false;
    }
}
Account *SavingsAccountFactory::createAccount(int id)
{
    return new SavingsAccount(id);
}
