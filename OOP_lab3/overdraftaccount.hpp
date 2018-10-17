#ifndef _OVERDRAFTACCOUNT_HPP_
#define _OVERDRAFTACCOUNT_HPP_
#include "account.hpp"

class OverdraftAccount : public Account
{
public:
	OverdraftAccount(int, std::string, double, double);

	void withdraw(double) override;
	double getLimitToWithdraw() const override;
	void onPeriodFinished() override;

private:
	const double limitToWithdraw;

};
#endif // _OVERDRAFTACCOUNT_HPP_
