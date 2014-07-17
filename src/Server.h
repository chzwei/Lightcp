/*
 *==========================================================================
 *       Filename:  Server.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2014年07月06日 14时00分59秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  chzwei, chzwei3@gmail.com
 *   Organization:  sysu
 *==========================================================================
 */
#ifndef SERVER_H
#define SERVER_H

#include "Config.h"

class Server{
public:
	Config config;

	bool shutdown;
	bool handle_sig_alarm;
	bool handle_sig_hup;

	Server();
	~Server();
	void Init();
	void Close();
	void SetSignal();
	void SignalHandler(int sig);
	int SocketListen();
private:
};

#endif //SERVER_H

