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
int signup( string j, string i);
int login( string j, string i);

string user="nouser";
string salt ="Cisc";
static int signupcallback(void *NotUsed, int argc, char **argv, char **azColName);
static int logincallback(void *NotUsed, int argc, char **argv, char **azColName);

int main(){
    //Variables
    Cgicc cgi;
    hash<string> hasher;
    size_t hash = hasher(cgi("psw")+salt);
    string pword = to_string(hash);
    user="nouser";
    
    string mycppstr(getenv("QUERY_STRING"));
   cout << "Content-type: text/html" << endl;
   cout << endl;
  if(!mycppstr.compare("login")){
      login(cgi("uname"),pword);
      if(!user.compare("nouser")){
          cout<<"Incorrect Information. Try Again"<<endl;
          cout << "<!doctype html><html><head><meta http-equiv=\"refresh\" content=\"1; URL='login.cgi'\" /></head><body>"<<endl;
      }
      else{
  cout << "<!doctype html><html><head><meta http-equiv=\"refresh\" content=\"3; URL='inbox.cgi'\" /></head><body>"<<endl;
  
  cout<<"Login Successful. Redirecting to Inbox";
  }
  }
  else if(!mycppstr.compare("register")){
      signup(cgi("uname"),pword);
      string uname="poopppppp";
      cout << "<!doctype html><html><head><meta http-equiv=\"refresh\" content=\"3; URL='inbox.cgi?poop"+uname+"'\" /></head><body>"<<endl;
      //cout<<"Your Account Has Been Created. Redirecting to Inbox.";
       
  }
  else{
      cout<<"Login Information Incorrect. Try Again";
      cout << "<!doctype html><html><head><meta http-equiv=\"refresh\" content=\"3; URL='login.cgi'\" /></head><body>"<<endl;
       
  }
   
//   hash<string> hasher;
//   size_t hash = hasher(cgi("psw")+salt);
// //   cout << cgi("uname") << endl;
// //   cout << cgi("psw") << endl;
//   cout << "hash is: "<<to_string(hash) << endl;
//   cout <<getenv("QUERY_STRING") <<endl;
   cout << "</body></html>" << endl;
}


int signup(string j, string i){
    sqlite3* db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("email.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    
    string  que = "INSERT INTO USERS (UNAME, PASSHASH) VALUES ( \""+j+"\", "+i+");";
    cout<<que<<endl;
    char sql[1024];
    strcpy(sql, que.c_str());
    
    rc = sqlite3_exec(db, sql, signupcallback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }else{
      fprintf(stdout, "Account Created\n");
    }    
    sqlite3_close(db);
    return 0;
}


static int signupcallback(void *NotUsed, int argc, char **argv, char **azColName){
    printf(" Great\n");
    return 0;
} 

int login(string j, string i){
    sqlite3* db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("email.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    
    string  que = "SELECT * FROM USERS WHERE UNAME= \""+j+"\" AND PASSHASH="+i+";";
    //cout<<que<<endl;
    char sql[1024];
    strcpy(sql, que.c_str());
    
    rc = sqlite3_exec(db, sql, logincallback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }else{
      //fprintf(stdout, "Logging IN\n");
    }    
    sqlite3_close(db);
    return 0;
}

static int logincallback(void *NotUsed, int argc, char **argv, char **azColName){
    user= string (argv[1]);
    cout<<"d"<<user<<"d";
    return 0;
}