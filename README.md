# Bank Management System (OOP Design)

A robust, console-based banking application designed using C++ to demonstrate core **Object-Oriented Programming (OOP)** principles. This system manages customers, multiple account types, and transaction histories with a focus on **Encapsulation**, **Polymorphism**, and **Memory Management**.

## Key Features

- **Customer Management:** Create and manage customer identities.
- **Multiple Account Types:**
  - **Savings Account:** Earns interest; strictly prevents overdrafts.
  - **Checking Account:** Supports overdraft limits for flexible withdrawals.
- **Transaction History:** Every deposit/withdrawal is logged immutably (date, type, amount).
- **Polymorphic Behavior:** Unified interface (`Account`) for different account behaviors.
- **Factory Logic:** Centralized account creation logic within the Bank class.

## System Architecture

The project follows a modular design emphasizing the **SOLID** principles.

### Class Overview

| Class               | Responsibility                                                                           |
| :------------------ | :--------------------------------------------------------------------------------------- |
| **Bank**            | Acts as the entry point and Factory for creating accounts.                               |
| **Customer**        | Holds personal details and a list of `Account` pointers.                                 |
| **Account**         | **Abstract Base Class**. Defines the interface and holds shared data (Balance, History). |
| **SavingsAccount**  | Implements specific rules for interest and safe withdrawals.                             |
| **CheckingAccount** | Implements specific rules for overdrafts.                                                |
| **Transaction**     | Represents an immutable record of a financial event.                                     |

### UML Relationship Simplified

- **Bank** _has-many_ **Customers**
- **Customer** _has-many_ **Accounts** (Polymorphic List)
- **Account** _has-many_ **Transactions**
- **Savings/Checking** _is-an_ **Account**

## Technical Implementation Details

- **Language:** C++ (Standard 11/14+)
- **Polymorphism:** Usage of `virtual` functions for `withdraw()` logic and `virtual` destructors for safe memory cleanup.
- **Encapsulation:** Protected members (`balance`) allow derived classes access while hiding data from the public scope.
- **Design Pattern:** Uses the **Factory Design Pattern** in `Bank::openAccount` to decouple object creation from client code.

## Todo List & Roadmap

Completed Phase 1 (Core Logic)

-- [x] Design Class Hierarchy (Bank, Customer, Account)

- [x] Implement Inheritance for Account Types (Savings/Checking)

- [x] Implement Polymorphism for withdraw logic

- [x] Create Transaction logging system

- [x] Implement Factory Logic for Account creation

Phase 2 (Upcoming Features)

- [ ] Transfer Feature: Implement transfer(Account\* to, double amount)

- [ ] Input Validation: Prevent negative inputs for deposit/withdraw

- [ ] Search: Implement findCustomerById or findAccountById

- [ ] Persistence: Save Customer and Account data to a text file/database

- [ ] Refactoring: Replace raw pointers with std::unique_ptr or std::shared_ptr

### Designed by [Your Name] as a study in Advanced OOP Architecture.
