/*
 *==========================================================================
 *       Filename:  Server.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月06日 10时50分21秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "Config.h"
#include "Server.h"
#include "Epoll.h"
using namespace std;

Server::Server(){
	shutdown = false;
	handle_sig_alarm = false;
	handle_sig_hup = false;
}

void Server::Init(){
	SetSignal();
}

void Server::SignalHandler(int sig) {
	switch (sig) {
	case SIGTERM:
		shutdown = 1; 
		break;
	case SIGINT:
	     break;
	case SIGALRM: 
		 handle_sig_alarm = 1; 
		 break;
	case SIGHUP:  
		 handle_sig_hup = 1; 
		 break;
	case SIGCHLD:  
		 break;
	}
}

void Server::SetSignal(){
	signal(SIGPIPE, SIG_IGN);
	signal(SIGUSR1, SIG_IGN);
	signal(SIGALRM, SignalHandler);
	signal(SIGTERM, SignalHandler);	//kill发出的终止信号
	signal(SIGHUP,  SignalHandler);	//重启
	signal(SIGCHLD, SignalHandler);
	signal(SIGINT,  SignalHandler);	//终端中断符
}

int Server::SocketListen(){
	int sockfd;
    if( (sockfd = socket(AF_INET, config.SOCK_TREAM, 0)) < 0){
        perror("socket\n");
        return -1;
    }

	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, config.ip, &address.sin_addr);
	address.sin_port = htons(config.port);

    if( bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("bind\n");
        return -1;
    }

	if(listen(sockfd, BACKLOG) < 0){
        perror("listen\n");
        return -1;
	}
	return sockfd;
}