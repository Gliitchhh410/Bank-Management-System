#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account;
class Customer;

enum TRANSACTION_TYPE
{
    WITHDRAW,
    DEPOSIT
};

class Transaction
{
    int transactionId;
    double amount;
    TRANSACTION_TYPE type;

public:
    Transaction(int transactionId, double amount, TRANSACTION_TYPE type);
    string getDetails();
};

class Account
{

    int accountNumber;

protected:
    double balance;
    void addTransaction(TRANSACTION_TYPE type, double amount);
    vector<Transaction> transactionHistroy;

public:
    Account(int accNum);
    int getAccountNumber();
    void deposit(double amount);
    virtual void withdraw(double amount) = 0;
    virtual ~Account();
    void printStatement();
};

class SavingsAccount : public Account
{
public:
    SavingsAccount(int id);
    void withdraw(double amount);

private:
    double interestRate;
    void applyInterest();
};

class CheckingAccount : public Account
{
public:
    CheckingAccount(int id);

private:
    double overdraftLimit;

public:
    void withdraw(double amount);
};

class AccountFactory
{
public:
    virtual Account *createAccount(int id) = 0;
};

class CheckingAccountFactory : public AccountFactory
{
    Account *createAccount(int id);
};
class SavingsAccountFactory : public AccountFactory
{
    Account *createAccount(int id);
};

class Customer
{
    int customerId;
    string name;

public:
    vector<Account *> Accounts;
    void setName(string);
    void setCustomerId(int);
    int getCustomerId();
    void addAccount(Account *acc);
    Account *getAccount(int id);
};

class Bank
{
public:
    vector<Customer> Customers;
    void createCustomer(string name);
    void openAccount(AccountFactory *factory, int customerId);
};
