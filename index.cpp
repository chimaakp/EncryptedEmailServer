#include <iostream>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <sqlite3.h>
#include <cstring>

using namespace std;
using namespace cgicc;
   //Ceasar Cypher
   void encryptDecrypt(char inpString[], string key){ 
    string xorKey = key; 
    int len = strlen(inpString); 
    for (int i = 0; i < len; i++){ 
        inpString[i] = inpString[i] ^ key.c_str()[0]; 
        //printf("%c",inpString[i]); 
    }
   }
   
   static int messagecallback(void *NotUsed, int argc, char **argv, char **azColName){
      return 0;
   }
   
   int sendmessage(string j, string i){
    sqlite3* db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("email.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    
    string  que = "INSERT INTO MESSAGES(SENDER,RECIEVER, TEXT) VALUES ( \"admin\",\""+i+"\", \""+j+"\");";
    cout<<que<<endl;
    char sql[1024];
    strcpy(sql, que.c_str());
    
    rc = sqlite3_exec(db, sql, messagecallback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }else{
    }    
    sqlite3_close(db);
    return 0;
}

int main(){
   cout << HTTPHTMLHeader() << endl;

      // Set up the HTML document
      cout << html() << cout << "<!doctype html><html><head><meta http-equiv=\"refresh\" content=\"1; URL='read.cgi'\" /></head>" << endl;
      cout << body() << endl;

   Cgicc cgi;
   string dat = cgi("message");
   char tmp[1024];
   strcpy(tmp, dat.c_str());
  
    // Encrypt the string 
    printf("Encrypted String: "); 
    encryptDecrypt(tmp, cgi("key"));
    cout<<dat;
    printf("\n");
    sendmessage(string(tmp), cgi("recip"));
  
    //Decrypt the string 
   //  printf("Decrypted String: "); 
   //  encryptDecrypt(tmp,cgi("key")); 
  
    cout << "</body></html>" << endl;
 
} 
