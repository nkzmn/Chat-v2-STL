#include "Chat.h"

int main()
{
	setlocale (LC_ALL, "");

	Chat chat;

	chat.startChat(); //переключает чат статус в true

	while (chat.isChatWork()) //пока чат статус = true
	{
		chat.showLoginMenu();
		
		while (chat.getCurrentUser())
		{
			chat.showUserMenu();
		}
	}
	
	return 0;
}
