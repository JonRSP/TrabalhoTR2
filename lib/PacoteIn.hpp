#ifndef PACKIN_H
#define PACKIN_H

#include <string>
#include <vector>
#include <memory>

#include <unistd.h>

#include "Header.hpp"
#include "Dado.hpp"

class PacoteIn{
	public:
		int socketIn = -1;
		explicit PacoteIn(int porta);
		~PacoteIn();
		void accConexao();
		void getRequests();
		ssize_t Send(HTTP::Header msg);
		std::vector<HTTP::Header> requestsRecebidos;
};
#endif
