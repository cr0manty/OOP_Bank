#include "bank.hpp"

Bank::Bank(std::string  const & _name) : name(_name), id(123)
{
}

Bank::~Bank()
{
	for (auto i : bills)
		delete i;
}

void Bank::deposit(int _id, double _amount)
{
	if (_amount < 1)
		throw std::logic_error(Messages::NonPositiveDeposit);

	for (auto i : bills)
		if (i->getId() == _id)
			i->deposit(_amount);
}

void Bank::withdraw(int _id, double _amount)
{
	for (auto i : bills)
		if (i->getId() == _id)
			i->withdraw(_amount);
}

int Bank::createAccount(std::string const & _ownerName, double _initialBalance)
{
	hasClientName(_ownerName);

	static int id = 0;
	Account *newAcc = new Account(id, _ownerName, _initialBalance);

	bills.push_back(newAcc);
	return id++;
}

int Bank::createOverdraftAccount(std::string const & _ownerName, double _initialBalance, double _overdraftLimit)
{
	hasClientName(_ownerName);

	static int id = 0;
	Account *overNewAcc = new OverdraftAccount(id, _ownerName, _initialBalance, _overdraftLimit);
	
	bills.push_back(overNewAcc);
	return id++;
}

void Bank::makeTransfer(int _sourceAccountID, int _targetAccountID, double _amount)
{
	if (_amount < 1)
		throw std::logic_error(Messages::NonPositiveTransfer);

	if (moreThenCanWithdrow(_sourceAccountID, _amount))
		throw std::logic_error(Messages::WithdrawalLimitExceeded);

	withdraw(_sourceAccountID, _amount);
	deposit(_targetAccountID, _amount);
	
}

bool Bank::isOverdraftAllowedFor(int _id) const
{
	for (auto i : bills)
		if (i->getId() == _id)
			return i->getLimitToWithdraw() > 0;
}

void Bank::hasClientName(std::string const & _name)
{
	for (auto i : bills)
		if (i->getName() == _name)
			throw std::logic_error(Messages::OwnerNameNotUnique);
}

bool Bank::findId(int _id) const
{
	for (auto i : bills)
		if (i->getId() == _id)
			return true;
	return false;
}

bool Bank::moreThenCanWithdrow(int _id, double _amount)
{
	for (auto i : bills)
		if (i->getId() == _id)
			return i->getBalance() + i->getLimitToWithdraw() < _amount;
				//return true;
}

std::string const Bank::getBillOwnerName(int _id) const
{
	for (auto i : bills)
		if (i->getId() == _id)
			return i->getName();
}

double Bank::getAccountBalance(int _id) const
{
	for (auto i : bills)
		if (i->getId() == _id)
			return i->getBalance();
}

double Bank::getTotalBankBalance() const
{
	double balance = 0;

	for (auto i : bills)
		balance += i->getBalance();

	return balance;
}

double Bank::getTotalBankDeposit() const
{
	double totalDep = 0;

	for (auto i : bills) {
		if (i->getBalance() > 0)
			totalDep += i->getBalance();
	}
	return totalDep;
}

double Bank::getBanksOverdrafts() const
{
	double balance = 0;

	for (auto i : bills)
		if (i->getBalance() < 0)
			balance += abs(i->getBalance());

	return balance;
}

double Bank::getOverdraftLimit(int _id) const
{
	for (auto i : bills)
		if (i->getId() == _id)
			return i->getLimitToWithdraw();
}

