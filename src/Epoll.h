/*
 *==========================================================================
 *       Filename:  Epoll.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月19日 09时48分01秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#ifndef EPOLL_H
#define EPOLL_H
#include <sys/epoll.h>

class Epoll{
public:
	static Epoll* GetInstance(){
		if(epoll_instance == NULL){
			epoll_instance = new Epoll;
			epoll_instance->Init();
		}
	    return epoll_instance;
	}

	int EpollAddRfd(int fd){
	    epoll_event event;
	    event.data.fd = fd;
	    event.events = EPOLLIN;
	    int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	    SetNoBlocking(fd);
	    return ret;
	}

	int EpollAddRptr(int fd, void *ptr){
	    epoll_event event;
	    event.data.ptr = ptr;
	    event.events = EPOLLIN;
	    int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	    SetNoBlocking(fd);
	    return ret;
	}

	int EpollAddWptr(int fd, void *ptr){
	    epoll_event event;
	    event.data.ptr = ptr;
	    event.events = EPOLLOUT;
	    int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	    SetNoBlocking(fd);
	    return ret;
	}

	int EpollDel(int fd){
	    return epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
	}

	int EpollWait(struct epoll_event *events, int maxevents, int timeout){
		return epoll_wait(epollfd, events, maxevents, timeout);
	}
private:
	int epollfd;

	void Init(){
		epollfd = epoll_create(MAX_EVENT_NUMBER);
	}

private:
	Epoll(){}
	static Epoll *epoll_instance;
	class CG
	{
	public:
		~CG(){
			if(Epoll::epoll_instance){
				delete epoll_instance;
			}
		}
	};
	static CG cg;
};

Epoll* Epoll::epoll_instance = NULL;

#endif

