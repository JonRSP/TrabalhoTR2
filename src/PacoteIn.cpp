#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include<netdb.h>

#include "PacoteIn.hpp"

int inSocket = -1;
int numeroPorta;
struct sockaddr_in serverEnd;
struct addrinfo SEnd;
struct addrinfo *lSEnd;
socklen_t size;

PacoteIn::PacoteIn(int porta){
	numeroPorta = porta;
	inSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(inSocket < 0){
		printf("Erro no socket\n");
		exit(1);
	}
	printf("Server socket criado\n");
	serverEnd.sin_family = AF_UNSPEC;
	serverEnd.sin_addr.s_addr = htons(INADDR_ANY);
	serverEnd.sin_port = htons(static_cast<uint16_t>(porta));
	if(bind(inSocket, (struct sockaddr*)&serverEnd, sizeof(serverEnd))<0){
		printf("erro no bind\n");
		exit(1);
	}

	printf("socket binded\n");
	size = sizeof(serverEnd);
	listen(inSocket, 10);
}

PacoteIn::~PacoteIn() = default;

void PacoteIn::accConexao(){
	socketIn = accept(inSocket, nullptr, nullptr);
	if(socketIn < 0){
		printf("erro na conexao\n");
		exit(1);
	}
}

void PacoteIn::getRequests(){
	int valRead = 0;
	std::string mensagem;

	do{
		char buffer[1024];
		valRead = static_cast<int>(read(socketIn, buffer, sizeof(buffer)));
		mensagem += std::string(buffer, static_cast<unsigned long>(valRead));
		printf("%s",mensagem.c_str());
	}while(valRead == 1024);
	if(valRead > 0){
		//std::cout << "ok " << HTTP::Header(mensagem).to_string() << '\n';
		requestsRecebidos.push_back(HTTP::Header(mensagem));
		
	}else if(0==valRead){
		printf("não tem requests \n");
	}else{
		printf("falha na leitura");
	}
}

ssize_t PacoteIn::Send(HTTP::Header msg){
	//std::cout << msg.to_string().c_str() << '\n';
	ssize_t enviado = send(socketIn, msg.to_string().c_str(), msg.to_string().length(),0);
	if(enviado < 0){
		printf("nao foi possivel enviar dado");
		exit(1);
	}else{
		return enviado;
	}

}
