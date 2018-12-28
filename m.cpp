#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

using namespace std;
using namespace cgicc;

   void encryptDecrypt(char inpString[], string key){ 
    string xorKey = key; 
    int len = strlen(inpString); 
    for (int i = 0; i < len; i++){ 
        inpString[i] = inpString[i] ^ key.c_str()[0]; 
        printf("%c",inpString[i]); 
    }
   } 
main(int argc, 
     char **argv)
{
   try {
      Cgicc cgi;
      

      // Send HTTP header
      cout << HTTPHTMLHeader() << endl;

      // Set up the HTML document
      cout << html() << head(title("Private Message")) << endl;
      cout << body() << endl;
        string dat = cgi("message");
   char tmp[1024];
   strcpy(tmp, dat.c_str());
      encryptDecrypt(tmp,cgi("key"));


      // Close the HTML document
      cout << body() << html();
   }
   catch(exception& e) {
      // handle any errors - omitted for brevity
   }
}