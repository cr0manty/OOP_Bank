#include "overdraftaccount.hpp"
#include <cmath>

OverdraftAccount::OverdraftAccount(int _id, std::string _name, double _balance, double _maxWith) : limitToWithdraw(_maxWith), Account(_id,_name,_balance)
{
	if (_balance < 0)
		throw std::logic_error(Messages::NegativeInitialBalance);

	if (_maxWith < 1)
		throw std::logic_error(Messages::NegativeOverdraft);

	if (_name.empty())
		throw std::logic_error(Messages::OwnerNameIsEmpty);

}

void OverdraftAccount::withdraw(double _amount)
{
	if (_amount > getBalance() + limitToWithdraw) 
		throw std::logic_error(Messages::WithdrawalLimitExceeded);

	minBalance(_amount);
}

void OverdraftAccount::onPeriodFinished()
{
	double balance = getBalance();

	if (balance < 0)
		minBalance(balance * 0.05);
}

double OverdraftAccount::getLimitToWithdraw() const
{
	return limitToWithdraw;
}

