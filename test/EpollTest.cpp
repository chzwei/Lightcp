/*
 *==========================================================================
 *       Filename:  EpollTest.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月05日 10时59分59秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include "Test.h"
using namespace std;

extern int SocketServer();
extern int SetNoBlocking(int fd);
extern int Addfd(int epollfd, int fd);
int main()
{
	int sockfd; 
	if( (sockfd = SocketServer()) < 0 )
		return -1;

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd;
    if((epollfd= epoll_create(MAX_EVENT_NUMBER)) < 0){
        perror("epoll_create");
        return -1;    
    }

    if(Addfd(epollfd, sockfd) < 0){
        perror("addfd");
        return -1;
    }
	
	int buf_size = 10;
	char *buf = new char[buf_size];
	int ret;
	while(true){
		if((ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1)) < 0){
			perror("epoll wait\n");
			continue;
		}else{
			cout << "wait" << endl;
			for(int i = 0; i < ret; ++i){
				int tmpfd = events[i].data.fd;
				if(tmpfd == sockfd){
					printf("case one\n");
					struct sockaddr_in client;
	                socklen_t client_addrlength = sizeof(client);
	                int acceptfd;
		            if((acceptfd = accept(sockfd, (struct sockaddr*)&client, &client_addrlength)) < 0){
			            perror("accept\n");
				        return -1;
					}else{
						Addfd(epollfd, acceptfd);
					}				
				}else{
					printf("case two\n");
					recv(tmpfd, buf, 1, 0);
					printf("%s\n", buf);
				}
			}
		}
	}

	return 0;
}

