#include "http_server.hh"
#include <vector>
#include <sys/stat.h>
#include <fstream>
#include <sstream>

vector<string> split(const string &s, char delim) {
  vector<string> elems;

  stringstream ss(s);
  string item;

  while (getline(ss, item, delim)) {
    if (!item.empty())
      elems.push_back(item);
  }

  return elems;
}

HTTP_Request::HTTP_Request(string request) {
  vector<string> lines = split(request, '\n');
  vector<string> first_line = split(lines[0], ' ');

  this->HTTP_version = "1.0"; 
  this->method = first_line[0];

  this->url = first_line[1];


  if (this->method != "GET") {
    cerr << "Method '" << this->method << "' not supported" << endl;
    exit(1);
  }

}

HTTP_Response *handle_request(string req) {
  HTTP_Request *request = new HTTP_Request(req);

  HTTP_Response *response = new HTTP_Response();

  string url = string("html_files") + request->url;

  response->HTTP_version = "1.0";

  response->connection = "Closed";
  struct stat sb;
  if (stat(url.c_str(), &sb) == 0) 
  {
    response->status_code = "200";
    response->status_text = "OK";
    response->content_type = "text/html";

    string body;

    if (S_ISDIR(sb.st_mode)) {
        url.append("/index.html");
    }

   
    ifstream file;
    file.open(url);

    body = string(istreambuf_iterator<char>(file),istreambuf_iterator<char>());

    response->body = body;
    response->content_length = to_string(body.length());
  }

  else {
    response->status_code = "404";
    response->status_text = "Not Found";
    response->content_type = "text/html";

    //HTML template for Not found page
    string body ="<!DOCTYPE HTML> <html> <head> <title>404 Not Found</title> </head> <body> <h1>Not Found</h1> <p>The requested URL was not found on this server.</p> </body> </html>";

    response->body=body;
    response->content_length = to_string(body.length());

  }

  delete request;

  return response;
}

string HTTP_Response::get_string() {
    string res = "";
    res = "HTTP/"+this->HTTP_version+" "+this->status_code+" "+this->status_text+"\r\n";
    res.append("Content-Length: "+this->content_length+"\r\n");
    res.append("Connection"+this->connection+"\r\n");
    res.append("Content-Type: "+this->content_type+"\r\n");
    res.append("\r\n");
    res.append(this->body);
    res.append("\r\n");
 return res;
}
