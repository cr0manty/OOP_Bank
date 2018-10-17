#ifndef _BANK_HPP_
#define _BANK_HPP_

#include <string>
#include <vector>
#include "overdraftaccount.hpp"

class Bank
{
public:
	Bank(std::string  const & = "Privat");
	~Bank();

	int createAccount(std::string const &, double);
	int createOverdraftAccount(std::string const &, double, double);
	void deposit(int, double);
	void withdraw(int, double);
	void makeTransfer(int, int, double);

	bool isOverdraftAllowedFor(int) const;
	void hasClientName(std::string const &);
	bool findId(int) const;
	bool moreThenCanWithdrow(int, double);

	double getAccountBalance(int) const;
	double getTotalBankBalance() const;
	double getTotalBankDeposit() const;
	double getBanksOverdrafts() const;
	double getOverdraftLimit(int) const;
	std::string const getBillOwnerName(int) const;

private:
	std::string name;
	std::vector<Account*> bills;
	int id;
};

#endif // _BANK_HPP_
