//  #include <stdlib.h>
#include "Chat.h"

#include <filesystem>
	#include <fstream>

void Chat::startChat()
{
	_isChatWork = true;
}

void Chat::showLoginMenu()
{
	_currentUser = nullptr;
	char operation;
	std::cout << "\033[32m\t\tChat 3.0 (Ubuntu) is run.\t\a\033[m";
	std::cout << "\033[32m\tCurrent platform is: \a\033[m" << PLATFORM_NAME;
	
	do
	{
		std::cout << "\033[33m\n(1)SignUp\t\033[32m(2)Login\t\033[31m(0)ShutDown\n\033[m";

		std::cin >> operation;

		switch (operation)
		{
		case '1':
			try
			{  signUp();  }
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
	std::locale::global(std::locale("en_US.UTF-8"));
	uint32_t Spades = 0x2642;
	uint32_t Spades1 = 0x2640;

	std::cout << "--- Users ---" << std::endl;

	std::ifstream user_file("users.txt");

	std::string login;
	std::string password;
	std::string name;
	std::string gender;

	while (user_file >> login >> password >> name >> gender)
	{
		User user(login, password, name, gender);

		if (user.getUserGender() == "Male")
			std::wcout << (wchar_t)Spades << " ";
		else if (user.getUserGender() == "Female")
			std::wcout << (wchar_t)Spades1 << " ";

		std::cout << user.getUserName();

		if (login == _currentUser->getUserLogin())
			std::cout << "(me)";

		std::cout << std::endl;
	}

	std::cout << "----------" << std::endl;
}

void Chat::signUp() 
{

	std::string login, name, gender, password;

	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "Gender:";

	do
	{
		std::cout << "\n(Male(m),Female(f)) ";
		std::cin >> gender;
		if (!(gender == "m" || gender == "f"))
			std::cout << "Enter m or f";
	} 
	while (!(gender == "m" || gender == "f"));
	
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

		if (getUserByLogin(login) || login == "All")
			throw UserLoginExp();
		if (getUserByName(name) || name == "All")
			throw UserNameExp();
	
	User user (login, password, name, gender);
	_users.push_back(user);
	_currentUser = std::make_shared<User>(user);

	//	writeUser(login, password, name, gender);
	if (!user_file)
		user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);

	if (user_file)
	{
		User obj(login, password, name, gender);
		user_file << obj << std::endl;
	}

	else
		std::cout << "Could not open file users.txt!" << std::endl;
}

void Chat::login()
{
	
	std::string login;
	std::string password;
	//  std::vector <std::string> password;
	char operation;
	//  std::string ñ;
	do
	{
		std::cout << "Login: ";
		std::cin >> login;
		_currentUser = getUserByLogin(login);
		std::cout << "Password: ";
		std::cin >> password;
		/*
		while ((ñ = _getch()) != "\r")
		{
			password.push_back(ñ);
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
	std::string from,to, text;

	std::cout << "Chat 2.0 "<< std::endl;

	std::ifstream messagesFile("messages.txt");
	if (!messagesFile.is_open())
	{
		std::cout << "Error opening file!" << std::endl;
		return;
	}


	//	for (auto &mess:_messages)
	while (getline(messagesFile, from, ' ') && getline(messagesFile, to, ' ') && getline(messagesFile, text))
	{
		//	if(_currentUser->getUserLogin()==mess.getFrom()|| _currentUser->getUserLogin() == mess.getTo()||mess.getTo() == "All")
		if (_currentUser->getUserLogin() == from || _currentUser->getUserLogin() == to || to == "All")
		{
			//from = (_currentUser->getUserLogin() == mess.getFrom()) ? "Me" : getUserByLogin(mess.getFrom())->getUserName();
			from = (_currentUser->getUserLogin() == from) ? "Me" : getUserByLogin(from)->getUserName();

			//if (mess.getTo() == "All")
			if (to == "All")	to = "All";
			else  to = (_currentUser->getUserLogin() == to) ? "Me" : getUserByLogin(to)->getUserName();
				//to = (_currentUser->getUserLogin() == mess.getTo()) ? "Me" : getUserByLogin(mess.getTo())->getUserName();
			

			std::cout << "Message from " << from << " to " << to << std::endl;
			// std::cout << "Text: "<<mess.getText() << std::endl;
			std::cout << "Text: " << text << std::endl;
		}
	}
	messagesFile.close();
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

	if (to == "All" || to == "all" || to == "ALL")
		//_messages.emplace_back(Message{ _currentUser->getUserLogin(), "All", text });

	{
	Message message(_currentUser->getUserLogin(), "All", text);
	_messages.push_back(message);

	msg_file << message << std::endl;
	msg_file.close();
	}
	else
		// _messages.emplace_back(Message{ _currentUser->getUserLogin(), getUserByName(to)->getUserLogin(), text });
	{
		std::ifstream users_file("users.txt");
		std::string login, password, name, gender;

		bool found = false;
		while (users_file >> login >> password >> name >> gender)
		{
			if (name == to)
			{
				found = true;
				Message message(_currentUser->getUserLogin(), login, text);
				_messages.push_back(message);

				msg_file << message << std::endl;
				msg_file.close();

				break;
			}
		}
		users_file.close();

		if (!found)
		{
			std::cout << "Error: user not found\n";
			return;
		}
	}
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
	std::ifstream user_file("users.txt");
	if (!user_file.is_open())
	{
		std::cout << "Error opening users file." << std::endl;
		return nullptr;
	}

	std::string userLogin;
	std::string userPassword;
	std::string userName;
	std::string userGender;

	while (user_file >> userLogin >> userPassword >> userName >> userGender)
	{
		if (userLogin == login)
		{
			return std::make_shared<User>(userLogin, userPassword, userName, userGender);
		}
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

std::fstream& operator >>(std::fstream& is, User& obj)
{
	is >> obj._name;
	is >> obj._login;
	is >> obj._password;
	is >> obj._gender;
	return is;
}
std::ostream& operator <<(std::ostream& os, const User& obj)
{
	os << obj._login;
	os << ' ';
	os << obj._password;
	os << ' ';
	os << obj._name;
	os << ' ';
	os << obj._gender;
	return os;
}

std::ostream& operator <<(std::ostream& os, const Message& msg)
{
	os << msg._from;;
	os << ' ';
	os << msg._to;
	os << ' ';
	os << msg._text;
	return os;
}


