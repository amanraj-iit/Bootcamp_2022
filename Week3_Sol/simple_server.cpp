/* run using /server <port> */

#include "http_server.hh"
#include <bits/stdc++.h>
#include <stdio.h>
#include <unistd.h>

#include <netinet/in.h>

#include <pthread.h>

#define BUFFER_SIZE 2048
using namespace std;

void error(string msg) {
  perror(msg.c_str());
  exit(1);
}


class threadParameters{
    public:
        char* buffer;
        int newsockfd;

        threadParameters(char* passedBuffer, int passedNewsockfd){
            buffer = passedBuffer;
            newsockfd = passedNewsockfd;
        }
};

void* handlingClient(void* parameters){
    threadParameters params = *(threadParameters*) parameters;
    char* buffer =params.buffer;
    int newsockfd = params.newsockfd;

  bzero(buffer, BUFFER_SIZE);
  int n;
  n = read(newsockfd, buffer, BUFFER_SIZE-1);
  if (n < 0)
    error("ERROR reading from socket");
  
  string req (buffer, buffer + n);

  HTTP_Response *response = handle_request(req);


  string res = response->get_string();


  n = write(newsockfd,res.c_str(), res.length()-1);
  if (n < 0)
    error("ERROR writing to socket");

  delete response;

  return 0;
}

int main(int argc, char *argv[]) {
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in serv_addr, cli_addr;

  if (argc < 2) {
    cerr<< "ERROR, no port provided\n";
    exit(1);
  }

 
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  if (sockfd < 0)
    error("ERROR opening socket");

 
  memset((char *)&serv_addr,0, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;

 
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  
  serv_addr.sin_port = htons(portno);

  

  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

 

  listen(sockfd, 5);
  clilen = sizeof(cli_addr);


  cout<< "Server running successfully. Press Ctrl-C to close the server\n";
  while(true){
  
  newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
  if (newsockfd < 0)
    error("ERROR on accept");

  pthread_t thread_id;


  threadParameters params = threadParameters(buffer,newsockfd);
  
  pthread_create(&thread_id , NULL, handlingClient , &params);

}
  return 0;
}
