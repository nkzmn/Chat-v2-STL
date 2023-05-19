#include <stdlib.h>
#include "Chat.h"

void Chat::startChat()
{
	_isChatWork = true;
}

void Chat::showLoginMenu()
{
	_currentUser = nullptr;
	char operation;
	std::cout << "\033[32m\t\tChat 3.0 (Ubuntu) is run.\a\033[m";
	do
	{
		std::cout << "\033[33m\n(1)SignUp\t\033[32m(2)Login\t\033[31m(0)ShutDown\n\033[m";

		std::cin >> operation;

		switch (operation)
		{
		case '1':
			try
			{  singUp();  }
			catch (const std::exception& e)
			{  std::cout << e.what() << std::endl;  }
			break;

		case '2':
			login();
			break;

		case'0':
			_isChatWork = false;
			break;

		default:
			std::cout << "1 or 2..." << std::endl;
			break;
		}
	} while (!_currentUser && _isChatWork);
}

void Chat::showUserMenu()
{
	char operation;
	std::cout << "\033[36m\nHi, \033[33m" << _currentUser->getUserName()<<".\033[0m\n";

	while (_currentUser)
	{
		std::cout << "\033[36mMenu:\033[32m(1)Show chat | (2)Add message | (3)Users | (4)Delete last message |\033[31m (0)Logout\033[0m" << "\n>> ";
		std::cin >> operation;
		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case '4':
			deleteLastMessage();
			break;
		case '0':
			_currentUser = nullptr;
			break;
		default:
			std::cout << "Unknown choice.." << std::endl;
			break;
		}
	}
}

void Chat::showAllUsersName() const
{
	std::cout << "--- Users ---" << std::endl;
	for (auto& user : _users)
	{
		std::locale::global(std::locale("en_US.UTF-8"));
		uint32_t Spades = 0x2642;
		uint32_t Spades1 = 0x2640;
		if (user.getUserGender()=="m")
		{
			std::wcout << (wchar_t)Spades << " ";
		}
		else
		{
			std::wcout << (wchar_t)Spades1 << " ";
		}
		std::cout <<user.getUserName();

		if (_currentUser->getUserLogin() == user.getUserLogin())
			std::cout << "(me)";

		std::cout << std::endl;
	}
	std::cout << "----------" << std::endl;
}

void Chat::singUp()
{
	//  std::string c;
	std::string login, name, gender;
	std::string password;
	//  std::vector<std::string> password;
	std::cout << "Login: ";
	std::cin >> login;
	std::cout << "Password: ";
	std::cin >> password;
	/*
	while ((c = _getch()) != "\r")
	{
		password.push_back(c);
		_putch('*');
	}
	*/

	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "Gender:";
	
	do
	{
		std::cout << "\n(Male(m),Female(f)) ";
		std::cin >> gender;
		if (!(gender == "m" || gender == "f"))
			std::cout << "Enter m or f";
	} while (!(gender == "m" || gender == "f"));


	if (getUserByLogin(login) || login == "All")
	{
		throw UserLoginExp();
	}
	if (getUserByName(name) || name == "All")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name, gender);
	_users.push_back(user);
	_currentUser = std::make_shared<User>(user);

}

void Chat::login()
{
	
	std::string login;
	std::string password;
	//  std::vector <std::string> password;
	char operation;
	//  std::string с;
	do
	{
		std::cout << "Login: ";
		std::cin >> login;
		_currentUser = getUserByLogin(login);
		std::cout << "Password: ";
		std::cin >> password;
		/*
		while ((с = _getch()) != "\r")
		{
			password.push_back(с);
			_putch('*');
		}
		*/

		std::cout << "\n";
		if (_currentUser == nullptr || (password != _currentUser->getUserPassword()))
		{
			_currentUser=nullptr;

				std::cout << "Login invalid."<<std::endl;
				std::cout << "(0)exit or any key to return menu: ";
				std::cin >> operation;

				if(operation=='0')
					break;
		}
	} while (!_currentUser);
}

void Chat::showChat() const
{
	std::string from,to;

	std::cout << "Chat 1.0 "<<std::endl;

	for (auto &mess:_messages)
	{
		if(_currentUser->getUserLogin()==mess.getFrom()|| _currentUser->getUserLogin() == mess.getTo()||mess.getTo() == "All")
		{
			from = (_currentUser->getUserLogin() == mess.getFrom()) ? "Me" : getUserByLogin(mess.getFrom())->getUserName();
			if (mess.getTo() == "All")
			{
				to = "All";
			}
			else
			{
				to = (_currentUser->getUserLogin() == mess.getTo()) ? "Me" : getUserByLogin(mess.getTo())->getUserName();
			}

			std::cout << "Message from " << from << " to " << to << std::endl;
			std::cout << "Text: "<<mess.getText() << std::endl;
		}
	}
	std::cout << "____END____ " << std::endl;
}

void Chat::addMessage()
{
	std::string to, text;

	std::cout << "To (name or All): ";
	std::cin >> to;
	std::cout << "Text: ";
	std::cin.ignore();
	std::getline(std::cin, text);

	if (!(to == "all" || to == "All" || to == "ALL" || getUserByName(to)))
	{
		std::cout << "error send message: can't find " << to << std::endl;
		return;
	}

	if (to == "All" || to == "all" || to == "ALL")
		_messages.emplace_back(Message{ _currentUser->getUserLogin(), "All", text });
		
	else
		_messages.emplace_back(Message{ _currentUser->getUserLogin(), getUserByName(to)->getUserLogin(), text });
}

void Chat::deleteLastMessage()
{
	if (!(_messages.empty()))
	{
		Message s = _messages.back();

		if ((_currentUser->getUserName() == "Admin") || (s.getFrom() == _currentUser->getUserLogin()))
		{
			_messages.pop_back();
			std::cout << std::endl << "Message was deleted." << std::endl;
		}
		else
		{
			std::cout << "Not enough rights to delete." << std::endl;
		}
	}
	std::cout << "Chat is empty!" << std::endl;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : _users)
	{
		if (login == user.getUserLogin())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
{
	for (auto& user : _users)
	{
		if (name == user.getUserName())
			return std::make_shared<User>(user);
	}
	return nullptr;
}


