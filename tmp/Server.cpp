/*
 *==========================================================================
 *       Filename:  Server.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月14日 19时59分01秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#include <stdio.h>
#include <iostream>
#include "Test.h"
using namespace std;

extern int MAX_EVENT_NUMBER;

extern int SocketServer();
extern int SetNoBlocking(int fd);
extern int Addfd(int epollfd, int fd);

static bool shutdown = false;


int main(){
	int child_num = 10;
	bool child = false;
	

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
	
	int pid;
	if(child_num > 0){
		while(!child && !shutdown){
			if(child_num > 0){
				switch(fork()){
				case -1:
					return -1;
				case 0:
					child = 1;
					break;
				default:
					-- child_num;
					break;
				}
			}else{
				int status;
				if( -1 != wait(&status) ){
					++ child_num;
				}else{
					switch(errno) {
					case EINTR:
						break;
					default:
						break;
					}
				}
			}
		}	

		if(!child){
			return 0;
		}
	}
	
	int ret = 0;
	while(!shutdown){
		if((ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1)) < 0){
			perror("epoll wait\n");
			continue;
		}else{
			for(int i = 0; i < ret; ++i){
				int tmpfd = events[i].data.fd;
				if(tmpfd == sockfd){
					struct sockaddr_in client;
				    socklen_t client_addrlength = sizeof(client);
					int acceptfd;
				    if((acceptfd = accept(sockfd, (struct sockaddr*)&client, &client_addrlength)) < 0){
						perror("accept\n");
					}else{
						Addfd(acceptfd);
					}
				}else{

				}				
			}
		}
	}
	return 0;
}
