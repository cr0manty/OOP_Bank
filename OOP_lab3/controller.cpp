#include "controller.hpp"
#include "messages.hpp"

Controller::Controller()
{
	bank = new Bank;
}

Controller::~Controller()
{
	delete bank;
}

int Controller::createAccount(std::string const & _ownerName, double _initialBalance)
{
	return bank->createAccount(_ownerName, _initialBalance);
}

int Controller::createOverdraftAccount(std::string const & _ownerName, double _initialBalance, double _overdraftLimit)
{
	return bank->createOverdraftAccount(_ownerName, _initialBalance, _overdraftLimit);
}

std::string const Controller::getAccountOwnerName(int _accountID) const
{
	if (!bank->findId(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	return bank->getBillOwnerName(_accountID);
}

double Controller::getAccountBalance(int _accountID) const
{
	if (!bank->findId(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	return bank->getAccountBalance(_accountID);
}

bool Controller::isOverdraftAllowed(int _accountID) const
{
	if (!bank->findId(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	return bank->isOverdraftAllowedFor(_accountID);
}

double Controller::getOverdraftLimit(int _accountID) const
{
	if (!bank->findId(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	return bank->getOverdraftLimit(_accountID);
}

void Controller::deposit(int _accountID, double _amount)
{
	if (!bank->findId(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	bank->deposit(_accountID,_amount);
}

void Controller::withdraw(int _accountID, double _amount)
{
	if (!bank->findId(_accountID))
		throw std::logic_error(Messages::UnknownAccountID);

	if (!bank->isOverdraftAllowedFor(_accountID) &&_amount < 1)
		throw std::logic_error(Messages::NonPositiveWithdrawal);

	bank->withdraw(_accountID, _amount);
		
}

void Controller::transfer(int _sourceAccountID, int _targetAccountID, double _amount)
{
	if(!bank->findId(_sourceAccountID) || !bank->findId(_targetAccountID))
		throw std::logic_error(Messages::UnknownAccountID);

	bank->makeTransfer(_sourceAccountID, _targetAccountID, _amount);
}

double Controller::getTotalBankBalance() const
{
	return bank->getTotalBankBalance();
}

double Controller::getTotalBankDeposits() const
{
	return bank->getTotalBankDeposit();
}

double Controller::getTotalBankOverdrafts() const
{
	return bank->getBanksOverdrafts();
}
