#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sqlite3.h>
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

using namespace std;
using namespace cgicc;

void usernames ();
static int usercallback(void *NotUsed, int argc, char **argv, char **azColName);

int main(int argc, char **argv){
   try {
      Cgicc cgi;

      // Send HTTP header
      cout << HTTPHTMLHeader() << endl;

      // Set up the HTML document
      cout << html() << head(title("Send")) << endl;
      cout << body() << endl;
      cout<<"<h2>List of Users</h2>\n";
      cout<<"<ul>\n";
      usernames();
      cout<<"</ul>\n<hr>";
      cout<<"<h2>Send an Email</h2>\n";
      // Print out the submitted element
      form_iterator name = cgi.getElement("name");
      cout<<"<form action=\"index.cgi\" method=\"post\" id=\"msgform\"><div class=\"container\"><label for=\"recip\"><b>Recipient</b></label><input type=\"text\" pattern=\"[a-z]{1,15}\" placeholder=\"Enter name from list above\" name=\"recip\" required><label for=\"key\"><b>Key</b></label><input maxlength=\"1\" placeholder=\"Secret Key to decript message\" name=\"key\" required><button type=\"submit\">Send</button></div></form>";
      cout<<"<label for=\"message\"><b>Message</b></label><textarea form=\"msgform\" rows=\"30\" cols=\"50\" placeholder=\"Dear Chima, \" name=\"message\" required></textarea>";  

      // Close the HTML document
      cout << body() << html();
   }
   catch(exception& e) {
      // handle any errors - omitted for brevity
   }
}

void usernames (){
    sqlite3* db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("email.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
    }
    
    string  que = "Select * from USERS;";
    //cout<<que<<endl;
    char sql[1024];
    strcpy(sql, que.c_str());
    
    rc = sqlite3_exec(db, sql, usercallback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }else{
      
    }    
    sqlite3_close(db);
    
}


static int usercallback(void *NotUsed, int argc, char **argv, char **azColName){
    cout<<"<li>"<<argv[1]<<"</li>"<<endl;
    return 0;
} 