# EncryptedEmailServer
Encrypted Email server built using c++

__What is your project?__
My project is an email server that encrypts email messages between users. I created it using cgi, cgicc and sqlite3. When you register your account, your password is salted and hashed, and the hash is stored on the server. the inbox.cgi page shows a list of other users. and also has a form for sending messages to other users. You must input a 1 character key and share that privately with another user.

__How do I run the program?__
This project uses cgi, so you need to configure apache to run with cgi. It also uses sqlite3 and cgicc (apt install libcgicc5 libcgicc5-dev). I created a Makefile, so everything is compiled correctly by running "make" from the terminal.
