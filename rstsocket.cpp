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
using namespace std;

const char* IP = "127.0.0.1";
const int PORT = 12345;
const int BACKLOG = 5;
const int BUF_SIZE = 1024;
const int MAX_EVENT_NUMBER = 5;

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

	int confd;
	struct sockaddr_in addr;
	socklen_t len;
	if((confd = accept(sockfd, (struct sockaddr*)&addr, &len)) < 0){
		perror("accept");
		return -1;
	}
	close(confd);
	int abc;
	scanf("%d", &abc);
	perror("test");
    close(sockfd);
    return 0;
}
