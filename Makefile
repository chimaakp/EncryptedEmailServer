all:
	g++ login.cpp -o login.cgi
	g++ index.cpp -o index.cgi -lcgicc -lsqlite3
	g++ -std=c++11 loginlogic.cpp -o loginlogic.cgi -lcgicc -lsqlite3
	g++ register.cpp -o register.cgi
	g++ inbox.cpp -o inbox.cgi -lcgicc -lsqlite3
	g++ -std=c++11 read.cpp -o read.cgi -lcgicc -lsqlite3
	g++ m.cpp -o m.cgi -lcgicc