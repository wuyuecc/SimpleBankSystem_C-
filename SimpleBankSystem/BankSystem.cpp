#include"BankSystem.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<iomanip>
#include<conio.h>

using namespace std;

BankSystem::BankSystem()
{
}

BankSystem::~BankSystem()
{
}

void BankSystem::readFile(const string filepath)
{
	ifstream infile(filepath);

	if (!infile)
	{
		cerr << "Failed to open file: " << filepath << endl;
		exit(-1);
	}

	m_account.clear();
	AccountInfo account;
	string line;

	while (getline(infile,line))
	{
		stringstream word(line);
		word >> account.number;
		word >> account.password;
		word >> account.balance;
		m_account.push_back(account);
	}

	infile.close();
}

void BankSystem::writeFile(const string filepath)
{
	ofstream outfile(filepath);

	if (!outfile)
	{
		cerr << "Failed to open file: " << filepath << endl;
		exit(-1);
	}

	vector<AccountInfo>::iterator it = m_account.begin();

	while (it != m_account.end())
	{
		outfile << it->number << " ";
		outfile << it->password << " ";
		outfile << it->balance << endl;
		it++;
	}

	outfile.close();
}

string BankSystem::inputPassword()
{
    string password;
    char c;

    while (true)
    {
        c = _getch();
        if (c == '\r')
        {
            break;
        }
        else
        {
            password.append(1,c);
            cout << "*";
        }
    }
    cout << endl;

    return password;
}

void BankSystem::startup()
{
	cout << "Welcome to Simple Bank System." << endl;

	while (true)
	{
		cout << endl;
		cout << "Please choose to login as user or administrator:" << endl;
		cout << "1.user 2.administrator 0.exit" << endl;

		int serviceNum;
		cin >> serviceNum;
		
        if (0 == serviceNum)
		{
			break;
		}

		switch (serviceNum)
		{
		case 1:
			loginAsUser();
			break;
		case 2:
			loginAsAdmin();
			break;
		default:
			cout << "Invalid service number!" << endl;
			break;
		}
	}
}

void BankSystem::loginAsUser()
{
    readFile();

    AccountInfo account;

    cout << endl;
    cout << "Please input account number:" << endl;
    cin >> account.number;
    cout << "Please input password:" << endl;
    //cin >> account.password;
    account.password = inputPassword();

    m_it = m_account.begin();

    while (m_it != m_account.end())
    {
        if ((m_it->number == account.number) && (m_it->password == account.password))
        {
            break;
        }
        m_it++;
    }

    if (m_it == m_account.end())
    {
        cout << "Login failed!" << endl;
        return;
    }

    cout << "Login succeeded!" << endl;

    while (true)
    {
        cout << endl;
        cout << "Please choose service number:" << endl;
        cout << "1.deposit 2.withdraw 3.query 4.change password 0.return" << endl;

        int serviceNum;
        cin >> serviceNum;

        if (0 == serviceNum)
        {
            break;
        }

        switch (serviceNum)
        {
        case 1:
            depositMoney();
            break;
        case 2:
            withdrawMoney();
            break;
        case 3:
            queryBalance();
            break;
        case 4:
            changePassword();
            break;
        default:
            cout << "Invalid service number!" << endl;
            break;
        }
    }

    writeFile();
}

void BankSystem::loginAsAdmin()
{
    readFile();

    AccountInfo account;

    cout << endl;
    cout << "Please input administrator account:" << endl;
    cin >> account.number;
    cout << "Please input administrator password:" << endl;
    //cin >> account.password;
    account.password = inputPassword();

    if (!(account.number == "admin" && account.password == "admin"))
    {
        cout << "Login failed!" << endl;
        return;
    }
    cout << "Login succeeded!" << endl;

    while (true)
    {
        cout << endl;
        cout << "Please choose service number:" << endl;
        cout << "1.add account 2.show all accounts 0.return" << endl;

        int serviceNum;
        cin >> serviceNum;

        if (0 == serviceNum)
        {
            break;
        }

        switch (serviceNum)
        {
        case 1:
            addAccount();
            break;
        case 2:
            showAllAccounts();
            break;
        default:
            cout << "Invalid service number!" << endl;
            break;
        }
    }

    writeFile();
}

void BankSystem::depositMoney()
{
	double moneyAdded;

	cout << "Input amount of money:" << endl;
	cin >> moneyAdded;
	
    m_it->balance += moneyAdded;
}

void BankSystem::withdrawMoney()
{
	double moneyReduced;

	cout << "Input amount of money:" << endl;
	cin >> moneyReduced;

	if (moneyReduced > m_it->balance)
	{
		cout << "Not enough money!" << endl;
		return;
	}

	m_it->balance -= moneyReduced;
}

void BankSystem::queryBalance()
{
	cout << setw(15) << "CARD_NUMBER"<< setw(15) << "PASSWORD" << setw(15) << "BALANCE" << endl;
	cout << setw(15) << m_it->number << setw(15) << m_it->password << setw(15) << m_it->balance << endl;
}

void BankSystem::changePassword()
{
	string newPasswdOnce;
    string newPasswdTwice;

    while (true)
    {
        cout << "Please input new password:" << endl;
        //cin >> newPasswdOnce;
        newPasswdOnce = inputPassword();
        cout << "Please input new password again:" << endl;
        //cin >> newPasswdTwice;
        newPasswdTwice = inputPassword();
        if(newPasswdOnce == newPasswdTwice)
        {
            cout << "Password is changed successfully." << endl;
            break;
        }
        else
        {
            cout << "Two passwords differ, please type again." << endl;
        }
    }

	m_it->password = newPasswdOnce;
}

void BankSystem::addAccount()
{
    AccountInfo account;

    cout << "Input account number:" << endl;
    cin >> account.number;
    cout << "Input account password:" << endl;
    cin >> account.password;
    cout << "Input account money:" << endl;
    cin >> account.balance;

    m_account.push_back(account);
}

void BankSystem::showAllAccounts()
{
	cout << setw(15) << "CARD_NUMBER" << setw(15) << "PASSWORD" << setw(15) << "BALANCE" << endl;

    m_it = m_account.begin();

	while (m_it != m_account.end())
	{
		cout << setw(15) << m_it->number << setw(15) << m_it->password << setw(15) << m_it->balance << endl;
		m_it++;
	}
}
