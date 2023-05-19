#pragma once
// #include <string>

class User
{
	const std::string _login;
	std::string _password;
	//  std::vector<std::string> _password;
	std::string _name;
	std::string _gender;

public:
	User(const std::string& login, const std::string& password, const std::string& name) :_login(login), _password(password), _name(name) {}
	User(const std::string& login, const std::string& password, const std::string& name, const std::string& gender) :_login(login), _password(password), _name(name), _gender(gender) {}
	//  User(const std::string& login, const std::vector<std::string>& password, const std::string &name):_login(login),_password(password),_name(name){}
	//  User(const std::string& login, const std::vector<std::string>& password, const std::string &name, const std::string &gender) :_login(login), _password(password), _name(name),_gender(gender) {}
	
	const std::string& getUserLogin() const { return _login;}
	
	const std::string getUserPassword() const { return _password; }
	//  const std::vector<std::string> getUserPassword() const { return _password; }
//	void setUserPassword(const std::vector<std::string> &password) { _password=password; }
	const std::string& getUserName() const { return _name; }
//	void setUserName(const std::string& name) { _name = name; }
	const std::string& getUserGender() const { return _gender; }
//	void setUserGender(int gender) { _gender=gender; }
};

