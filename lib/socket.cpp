#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <ctime>
#include <list>
using namespace std;

struct Server_Socket{
	int sockfd;
	bool isclose;
	clock_t last_time;
};

list<Server_Socket> sock_list;

const char* IP = "127.0.0.1";
const int PORT = 12345;
const int BACKLOG = 5;
const int BUF_SIZE = 1024;
const int MAX_EVENT_NUMBER = 5;
const long OUT_TIME = 30000;

int setnonblocking(int fd){
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

int addfd(int epollfd, int fd){
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
    return ret;
}

int delfd(int epollfd, int fd){
	return epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
}

int main() {
	int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket\n");
        return -1;
    }

	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, IP, &address.sin_addr);
	address.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("bind\n");
        return -1;
    }

	if(listen(sockfd, BACKLOG) < 0){
        perror("listen\n");
        return -1;
    }

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd;
    if((epollfd= epoll_create(MAX_EVENT_NUMBER)) < 0){
        perror("epoll_create");
        return -1;    
    }

    if(addfd(epollfd, sockfd) < 0){
        perror("addfd");
        return -1;
    }

    char buffer[BUF_SIZE];
    int ret;
    while(true){
        if((ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1)) < 0){
            perror("epoll wait\n");
            return -1;
        }else{
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
                    }
                    
                    if(addfd(epollfd, acceptfd) < 0){
                        perror("epoll ctl\n");
                        return -1;
                    }
					
					Server_Socket tmpsock;
					tmpsock.sockfd = acceptfd;
					tmpsock.isclose = false;
					tmpsock.last_time = clock();
					cout <<  tmpsock.last_time << endl;
					sock_list.push_back(tmpsock);

                }else if(events[i].events & EPOLLIN){
                    printf("case two\n");
                    memset(buffer, '\0', sizeof(buffer));
                    if(recv(tmpfd, buffer, BUF_SIZE-1, 0) <= 0){
                        close(tmpfd);
                        perror("close");
                        continue;
                    }
                    printf("%s\n", buffer);
                }else{
                    printf("case three\n");
                }
            }
        }

		list<Server_Socket>::iterator it = sock_list.begin();
        clock_t now = clock();
        cout << now << endl;
        while(it != sock_list.end()){
            if(it->isclose || (it->last_time < now - OUT_TIME)){
                if(delfd(epollfd, it->sockfd) < 0){
                    perror("delfd");
                }
                close(it->sockfd);
                it = sock_list.erase(it);
            }else{
                it++;
            }
        }

    }
    close(sockfd);
    return 0;
}
