#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include<fstream>
using namespace std;


void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[512];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, 
			(struct sockaddr *) &cli_addr, 
			&clilen);
	if (newsockfd < 0) 
		error("ERROR on accept");

	FILE *fp;
	int ch = 0;
	fp = fopen("glad_receive.txt","a");            
	int words;
	read(newsockfd, &words, sizeof(int));

	while(ch != words)
	{
		read(newsockfd , buffer , 255); 
		fprintf(fp , "%s " , buffer);   
		ch++;
	}
//	cout<<"\n";
//	cout<<"FIle Received from Client Successfully";
//	cout<<"\n";
//	cout<<"The Content of File is Reversed";
	char ch1;
	ifstream in ("glad_receive.txt");
	in.seekg(0,ios::end);
	int size=in.tellg();

	for (int j=1; j<=size; j++)
	{ in.seekg(-j, ios::end);
		ch1=in.get();
		cout <<ch1;
	}

	in.close();
	close(newsockfd);
	close(sockfd);
	return 0; 
}
