#ifndef PACKOUT_H
#define PACKOUT_H

#include <string>
#include <vector>
#include <memory>

#include <unistd.h>

#include "Header.hpp"
#include "Dado.hpp"

class PacoteOut{
	public:
		PacoteOut();
		~PacoteOut();
		ssize_t Send(HTTP::Header msg);
		void responseRecebido();
		std::vector<HTTP::Header> responsesRecebidos;
};

#endif
