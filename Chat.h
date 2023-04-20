#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include"Message.h"
#include "User.h"


struct UserLoginExp: public std::exception
{
	const char* what() const noexcept override { return "error: Login is busy"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "error: Name is busy"; }
};

class Chat
{
public:
	void startChat();
	bool isChatWork() const { return _isChatWork; }
	std::shared_ptr<User> getCurrentUser() const { return _currentUser; }
	void showLoginMenu();
	void showUserMenu();

private:
	bool _isChatWork = false;
	std::vector<User> _users;
	std::vector<Message> _messages;
	std::shared_ptr<User> _currentUser = nullptr;

	void login();
	void singUp();
	void showChat() const;
	void showAllUsersName() const;
	void addMessage();
	void deleteLastMessage();
	std::vector<User>& getAllUsers() { return _users; }
	std::vector<Message>& getAllmessages() { return _messages; }
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	std::shared_ptr<User> getUserByName(const std::string& name) const;

};
