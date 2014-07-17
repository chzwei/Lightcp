/*
 *==========================================================================
 *       Filename:  Epoll.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月07日 21时02分19秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#ifndef EPOLL_H
#define EPOLL_H
#include <fcntl.h>
#include <errno.h>
#include <sys/epoll.h>

class Epoll{
public:	
	Epoll():epollfd(-1){
		events = new epoll_event[MAX_EVENT_NUMBER];
	}

	~Epoll(){
		delete [] events;
	}

	int Init(){
		if((epollfd= epoll_create(MAX_EVENT_NUMBER)) < 0){
			perror("epoll_create");
	        return -1;    
		}
		return 0;
	}

	int SetNoBlocking(int fd){
	    int old_option = fcntl(fd, F_GETFL);
		int new_option = old_option | O_NONBLOCK;
	    fcntl(fd, F_SETFL, new_option);
		return old_option;
	}

	int Addfd(int epollfd, int fd){
	    epoll_event event;
		event.data.fd = fd;
	    event.events = EPOLLIN | EPOLLET;
		int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	    SetNoBlocking(fd);
		return ret;
	}

	int EpollWait(epoll_event *p_events){
		p_events = events;
		return epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
	}

private:
	static const int MAX_EVENT_NUMBER = 5;
	int epollfd;	
    epoll_event *events;
};

#endif

