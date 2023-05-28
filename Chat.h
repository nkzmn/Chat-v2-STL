#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
//  #include <conio.h>


#include "Message.h"
#include "User.h"

#if defined(_WIN32) 
#define PLATFORM_NAME "windows 32-bit" // Windows 32-bit
#elif defined(_WIN64)
#define PLATFORM_NAME "windows 64-bit" // Windows 64-bit
#elif defined(__ANDROID__)
#define PLATFORM_NAME "android"   // Android 
#elif defined(__linux__)
#define PLATFORM_NAME "linux"     // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos и другие
#elif TARGET_OS_IPHONE == 1
#define PLATFORM_NAME "ios"       // Apple iOS
#elif TARGET_OS_MAC == 1
#define PLATFORM_NAME "osx"       // Apple OSX
#else
#define PLATFORM_NAME  "OS not detected" // ОС не распознана
#endif

// constexpr auto usersFile = "/tmp/users.txt";

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
	
	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::app);
	std::fstream msg_file = std::fstream("messages.txt", std::ios::in | std::ios::out | std::ios::app);

	void login();
	void signUp();
	void showChat() const;
	void showAllUsersName() const;
	void addMessage();
	void deleteLastMessage();
	
	std::vector<User>& getAllUsers() { return _users; }
	std::vector<Message>& getAllmessages() { return _messages; }
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	std::shared_ptr<User> getUserByName(const std::string& name) const;
	
	// void writeUser(std::string& login, std::string& password, std::string& name, std::string& gender) const;
};
