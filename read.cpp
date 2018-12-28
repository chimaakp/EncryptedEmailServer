#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <hash_map>
#include <sqlite3.h>
using namespace std;
using namespace cgicc;

// int register(std::string uname, std::int hash);
int getmessages(string i);


string user="nouser";

static int callback(void *NotUsed, int argc, char **argv, char **azColName);

int main(){
    //Variables
    Cgicc cgi;

    user=getenv("QUERY_STRING");
    
    string mycppstr(getenv("QUERY_STRING"));
   cout << "Content-type: text/html" << endl;
   cout << endl;
    cout << "<html><body>" << endl;
  
   getmessages(user);
//   hash<string> hasher;
//   size_t hash = hasher(cgi("psw")+salt);
// //   cout << cgi("uname") << endl;
// //   cout << cgi("psw") << endl;
//   cout << "hash is: "<<to_string(hash) << endl;
//   cout <<getenv("QUERY_STRING") <<endl;
   cout << "</body></html>" << endl;
}





int getmessages(string i){
    sqlite3* db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("email.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    
    string  que = "SELECT * FROM MESSAGES WHERE RECIEVER=\""+i+"\" ;";
    //cout<<que<<endl;
    char sql[1024];
    strcpy(sql, que.c_str());
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }else{
    }    
    sqlite3_close(db);
    return 0;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    cout<<argv[1]<<"\n";
    cout<<"<form action=\"m.cgi\" method=\"post\"><textarea name=\"message\" rows=\"10\" cols=\"70\">"+string(argv[3])+"</textarea><label for=\"key\"><b>Key</b></label><input maxlength=\"1\" placeholder=\"Secret Key \"name=\"key\" required><input type=\"submit\"></form>";
    cout<<"<hr>";
    return 0;
}
//cout<<"<form action=\"m.cgi\" method=\"post\"><div class=\"container\"><label for=\"uname\"><b>Username</b></label><input type=\"text\" pattern=\"[a-z]{1,15}\" placeholder=\"Enter Username\" name=\"uname\" required><label for=\"psw\"><b>Password</b></label><input type=\"password\" pattern=\"[a-z]{1,15}\"placeholder=\"Enter Password\" name=\"psw\" required><button type=\"submit\">Login</button></div></form>";
  