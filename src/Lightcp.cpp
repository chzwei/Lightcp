/*
 *==========================================================================
 *       Filename:  Lightcp.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月09日 19时20分39秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#include <stdio.h>
#include <iostream>
#include "Server.h"
using namespace std;

int main(int argc, char **argv){
	bool child = false;
	int child_num = srv.config.work_num;

	Server srv;
	srv.Init();

	int sockfd;
	if( (sockfd = srv.SocketListen()) < 0 ){
		perror("SocketListen\n");
		return -1;
	}

	Epoll epl;
	epl.Init();
	epl.Addfd(sockfd);
 
	if(child_num > 0){
		while(!child && !srv.shutdown){
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
						if(handle_sig_hup){
							handle_sig_hup = 0;
							kill(0, SIGHUP);
						}
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
	
	while(!srv.shutdown){
		if(srv.handle_sig_hup){
		}

		if(srv.handle_sig_alarm){

		}
		
		int event_count;
		epoll_event *events;
		if( (event_count = epl.EpollWait(events)) > 0 ){
			for(int i = 0; i < event_count; ++i){
				if(events[i].fd == sockfd){

				}else{
					
				}
			}
		}
	}
}
