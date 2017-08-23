//////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2017, yue.w.wu@oracle.com
//  @file               BankSystem.h
//  @brief              A simple text based bank system
//
//  Change History :
//      <Date>     | <Version> | <Author> | <Description>
//  ----------------------------------------------------------------------
//      2017/08/03 |    1.0    |  Yue Wu  | Create file
//  ----------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////

#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include<string>
#include<vector>

class AccountInfo
{
public:
	std::string number;
	std::string password;
	double balance;
};

class BankSystem
{
public:
	BankSystem();
	~BankSystem();
	void readFile(const std::string filepath = "account.txt");
	void writeFile(const std::string filepath = "account.txt");
    std::string inputPassword();
    void startup();
    void loginAsUser();
	void loginAsAdmin();
	void depositMoney();
	void withdrawMoney();
	void queryBalance();
	void changePassword();
    void addAccount();
	void showAllAccounts();
private:
	std::vector<AccountInfo> m_account;
    std::vector<AccountInfo>::iterator m_it;
};

#endif