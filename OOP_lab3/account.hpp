#ifndef _ACCOUNT_HPP_
#define _ACCOUNT_HPP_

#include <string>
#include "messages.hpp"

class Account
{
public:
	Account(int, std::string const &, double);
	virtual double getLimitToWithdraw() const;
	virtual void withdraw(double);
	virtual void onPeriodFinished();

	void deposit(double);
	void minBalance(double);

	std::string getName() const;
	int getId() const;
	double getBalance() const;	

private:
	int personId;
	std::string name;
	double balance;
};

#endif // _ACCOUNT_HPP_
