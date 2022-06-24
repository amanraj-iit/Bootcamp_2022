#ifndef _HTTP_SERVER_HH_
#define _HTTP_SERVER_HH_
#include <iostream>
using namespace std;

struct HTTP_Request {
  string HTTP_version;

  string method;
  string url;


  HTTP_Request(string request);
};

struct HTTP_Response {
  string HTTP_version; 

  string status_code;
  string status_text; 

  string content_type;
  string content_length;

  string body;
  string connection;


  string get_string(); 
};

HTTP_Response *handle_request(string request);

#endif
