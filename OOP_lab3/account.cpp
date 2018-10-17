#include "account.hpp"
#include "overdraftaccount.hpp"

Account::Account(int _id, std::string const & _name, double _balance) : personId(_id),name(_name),balance(_balance)
{
	if (_name.empty())
		throw std::logic_error(Messages::OwnerNameIsEmpty);

	if (_balance < 0)
		throw std::logic_error(Messages::NegativeInitialBalance);
}

void Account::deposit(double _amount)
{
	balance += _amount;
}

void Account::withdraw(double _amount)
{
	if (_amount > balance) 
		throw std::logic_error(Messages::WithdrawalLimitExceeded);;
		
	minBalance(_amount);
}

void Account::minBalance(double _amount)
{
	balance -= _amount;
}

void Account::onPeriodFinished()
{
	balance *= 1.01;
}

int Account::getId() const
{
	return personId;
}

std::string Account::getName() const
{
	return name;
}

double Account::getBalance() const
{
	return balance;
}

double Account::getLimitToWithdraw() const
{
	return 0.0;
}
