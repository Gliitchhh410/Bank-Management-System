#include <iostream>
#include <vector>
#include <string>
#include "bank.h"
using namespace std;




void Bank::openAccount(int customerId, TYPE type){
    Customer* targetCustomer = nullptr;

    for (auto &cust : Customers){
        if (cust.getCustomerId() == customerId){
            targetCustomer = &cust;
            break;
        }
    }

    if (!targetCustomer){
        cout << "Error: Customer ID not found" << endl;
        return;
    }

    Account* newAccount = nullptr;
    int newAccId = rand() * 1000;


    switch( type ){
        case SAVING:
            newAccount = new SavingsAccount();
            break;
        
        case CHECKING:
            newAccount = new CheckingAccount();
            break;

        default:
        cout << "Invalid Account Type" << endl;
        return;
    }



    if (newAccount != nullptr){
        targetCustomer -> addAccount(newAccount);
        cout << "account created successfully!!" << endl;
    }
}