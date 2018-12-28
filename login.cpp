#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
string uname;
string pword;
void parseQuery(char *a);


int main () {
    
   cout << "Content-type:text/html\r\n\r\n";
   cout << "<html>\n";
   cout << "<head>\n";
   cout << "<title>C-mail Login Page</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";
   cout<<"<form action=\"loginlogic.cgi?login\" method=\"post\"><div class=\"container\"><label for=\"uname\"><b>Username</b></label><input type=\"text\" pattern=\"[a-z]{1,15}\" placeholder=\"Enter Username\" name=\"uname\" required><label for=\"psw\"><b>Password</b></label><input type=\"password\" pattern=\"[a-z]{1,15}\"placeholder=\"Enter Password\" name=\"psw\" required><button type=\"submit\">Login</button></div></form>";
   // char *value = getenv("QUERY_STRING");
   // cout << "<p>QUERY_STRING: " << value << "</p>" << endl;
   cout<< "<a href=\"register.cgi\"><button>Create Account</button></a>\n";
   cout << "</body>\n";
   cout << "</html>\n";
   
   return 0;
}
