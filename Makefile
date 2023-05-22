TARGET = Chat
PREFIX = ~/chat


chat:   
	g++ -o Chat Main.cpp Chat.cpp


clean:
	rm -rf *.o *.a

install:
	install $(TARGET) $(PREFIX)
	


