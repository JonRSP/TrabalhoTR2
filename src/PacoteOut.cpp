#include<cstdlib>
#include<cstdio>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include <iostream>
#include <sstream>
#include<string.h>

#include "PacoteOut.hpp"


PacoteOut::PacoteOut() = default;
PacoteOut::~PacoteOut() = default;

int socketOut = -1;
struct addrinfo clienteEnd;
struct addrinfo *cEnd;

ssize_t PacoteOut::Send(HTTP::Header msg){
	memset(&clienteEnd, 0, sizeof(clienteEnd));
	clienteEnd.ai_family = AF_UNSPEC;
	clienteEnd.ai_socktype = 0;
	clienteEnd.ai_flags = 0;
	clienteEnd.ai_protocol =IPPROTO_TCP;
		int info = getaddrinfo(msg.host.c_str(), msg.porta.c_str(), &clienteEnd, &cEnd);
		//printf("info=%d", info);
	 if(info == 0){
		socketOut = socket(AF_INET, SOCK_STREAM, 0);
		if(socketOut < 0){
			printf("error ao criar socket");
			exit(1);
		}
		int aux = connect(socketOut, cEnd->ai_addr, cEnd->ai_addrlen);
		//printf("%d\n", errno);
		//printf("\naux = %d\n",aux);
		//printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d",EADDRNOTAVAIL,EAFNOSUPPORT,EALREADY,EBADF,ECONNREFUSED,EINPROGRESS,EINTR,EISCONN,ENETUNREACH,ENOTSOCK,EPROTOTYPE,ETIMEDOUT,EIO,ELOOP,ENAMETOOLONG,ENOENT,ENOTDIR,EACCES,EADDRINUSE,ECONNRESET,EHOSTUNREACH,EINVAL,ELOOP,ENAMETOOLONG,ENETDOWN,ENOBUFS,EOPNOTSUPP);
		if( aux < 0){
			printf("erro no socket\n");
			exit(1);
		}
	 }
	 std::cout << msg.to_string() << '\n';
	ssize_t enviado = send(socketOut, msg.to_string().c_str(), msg.to_string().length(), 0);
//printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d",EAGAIN,EWOULDBLOCK,EBADF,ECONNRESET,EDESTADDRREQ,EINTR,EMSGSIZE,ENOTCONN,ENOTSOCK,EOPNOTSUPP,EPIPE,EACCES,EIO,ENETDOWN,ENETUNREACH,ENOBUFS);
/*
EADDRNOTAVAIL,EAFNOSUPPORT,EALREADY,EBADF,ECONNREFUSED,EINPROGRESS,EINTR,EISCONN,ENETUNREACH,ENOTSOCK,EPROTOTYPE,ETIMEDOUT,EIO,ELOOP,ENAMETOOLONG,ENOENT,ENOTDIR,EACCES,EADDRINUSE,ECONNRESET,EHOSTUNREACH,EINVAL,ELOOP,ENAMETOOLONG,ENETDOWN,ENOBUFS,EOPNOTSUPP
*/



	if(enviado < 0){
		printf("nao foi possivel enviar dado\n");
		exit(1);
	}else{
		return enviado;
	}
	return -1;
}

void PacoteOut::responseRecebido(){
	int valread = 0;
	std::string mensagem("");
	memset(&responsesRecebidos, 0, sizeof(responsesRecebidos));

	do{
		char buffer[1024];
		valread = static_cast<int>(read(socketOut, buffer, sizeof(buffer)));
		mensagem += std::string(buffer, static_cast<unsigned long>(valread));
	}while(valread == 1024);
	printf("Response:\n%s\n",mensagem.c_str());
	if(valread > 0){
		responsesRecebidos.push_back(HTTP::Header(mensagem));
	}else{
		printf("falha na leitura");
		exit(1);
	}
}
