#ifndef MSGDATA_H
#define MSGDATA_H

#include <string>
#include <vector>
#include <memory>

#include <unistd.h>


typedef struct{
	std::string menssagem;
	std::string addrFrom;
	int portFrom;
	std::string addrTo;
	int portTo;
	int host;
	int porta;
}msg;


#endif
