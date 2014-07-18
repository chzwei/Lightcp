/*
 *==========================================================================
 *       Filename:  Connection.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月14日 22时10分57秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#ifndef CONNECTION_H
#define CONNECTION_H

#include <sys/socket.h>
#include <stdlib.h>

enum ConnectionState{
	CONNET,
	READ_HEAD,
	READ_DATA,
	READ_END,
	HANDLE,
	WRITE_HEAD,
	WRITE_DATA,
	WRITE_END,
	CLOSE,
	ERR
};

struct ConnectionHead{
	int type;
	int len;
};

class Connection{
public:
	void SetState(ConnectionState state){
		conn_stat = state;
	}

	int ConnectionStateMachine(){
		int done = 0;
		while(done == 0){
			switch(conn_stat){
			case CONNET:
			case READ_HEAD:
				int recv_size = recv(fd, head_buf+8-head_left_size, head_left_size, 0);
				if(recv_size > 0){
					head_left_size -= recv_size;
					if(head_left_size == 0){
						memcpy(&conn_head.type, head_buf, 4);
						memcpy(&conn_head.len, head_buf+4, 4);
						data_offset = 0;
						data_left_size = conn_head.len;
						SetState(READ_DATA);
					}else{
						SetState(READ_HEAD);
					}
				}else if(recv_size == 0){
					SetState(READ_END);
				}else{
					if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN){
						SetState(READ_HEAD);
					}else{
						SetState(ERR);
					}
				}
				break;	
			case READ_DATA:
				int recv_size = recv(fd, data_buf+data_offset, data_left_size, 0);
				if(recv_size > 0){
					data_left_size -= recv_size;
					data_offset += recv_size;
					if(data_left_size == 0){
						SetState(READ_END);
					}else{
						SetState(READ_DATA);
					}
				}else if(recv_size == 0){
					SetState(READ_END);
				}else{
					if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN){
						SetState(READ_DATA);
					}else{
						SetState(ERR);
					}
				}
				break;
			case READ_END:
				SetState(HANDLE);
				break;
			case HANDLE:
				memcpy(head_buf, &conn_head.type, 4);
				memcpy(head_buf+4, &conn_head.len, 4);
				data_left_size = conn_head.len;
				data_offset = 0;
				SetState(WRITE_HEAD);
				break;
			case WRITE_HEAD:
				int send_size = sendto(fd, head_buf+8-head_left_size, head_left_size, 0);
				if(send_size >= 0){
					head_left_size -= send_size;
					if(head_left_size == 0){
						SetState(WRITE_DATA);
					}else{
						SetState(WRITE_HEAD);
					}
				}else{
					if(errno == EINTR || errno == EAGAIN){
						SetState(WRITE_HEAD);
					}else{
						SetState(ERR);
					}
				}
				break;
			case WRITE_DATA:
				int send_size = sendto(fd, data_buf+data_offset, data_left_size, 0);
				if(send_size >= 0){
					data_left_size -= send_size;
					if(data_left_size == 0){
						SetState(WRITE_END);
					}else{
						SetState(WRITE_DATA);
					}
				}else{
					if(errno == EINTR || errno == EAGAIN){
						SetState(WRITE_DATA);
					}else{
						SetState(ERR);
					}
				}
				break;
			case WRITE_END:
				SetState(CLOSE);
				break;
			case CLOSE:
				close(fd);
				break;
			case ERR:
				break;
			default:
				break;
			}
		}
	}

private:
	ConnectionState conn_stat;
	ConnectionHead conn_head;
	char head_buf[8];
	int head_left_size;
	char data_buf[4096];
	int data_offset;
	int data_left_size;
	int fd;
};

#endif

