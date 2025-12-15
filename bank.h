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
    int getAccountNumber();
    void deposit(double amount);
    virtual void withdraw(double amount) = 0;
    virtual ~Account();
    void printStatement();
};

class Customer
{
    int customerId;
    vector<Account *> Accounts;
    string name;

public:
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

class SavingsAccount : public Account
{
    double interestRate;
    void applyInterest();

public:
    void withdraw(double amount);
};

class CheckingAccount : public Account
{
    double overdraftLimit;

public:
    void withdraw(double amount);
};

class AccountFactory
{
public:
    virtual Account *createAccount() = 0;
};

class CheckingAccountFactory : public AccountFactory
{
    Account *createAccount();
};
class SavingsAccountFactory : public AccountFactory
{
    Account *createAccount();
};