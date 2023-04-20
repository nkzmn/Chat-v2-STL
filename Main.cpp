#include "Chat.h"

int main()
{
	setlocale (LC_ALL, "");

	Chat chat;

	chat.startChat(); //����������� ��� ������ � true

	while (chat.isChatWork()) //���� ��� ������ = true
	{
		chat.showLoginMenu();
		
		while (chat.getCurrentUser())
		{
			chat.showUserMenu();
		}
	}
	
	return 0;
}