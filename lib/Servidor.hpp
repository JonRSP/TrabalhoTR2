#ifndef SERVER_H
#define SERVER_H

#include <vector>

#include "PacoteOut.hpp"
#include "PacoteIn.hpp"
#include "Header.hpp"
#include "Dado.hpp"

class Servidor{
	public:
		explicit Servidor(int porta);
		~Servidor();
		void Inicia();
		std::vector< HTTP::Header > &requests;
		std::vector< HTTP::Header > sendRequest;
		std::vector< HTTP::Header > &responses;
		std::vector< HTTP::Header > sendResponse;
	private:
		PacoteIn pIn;
		PacoteOut pOut;

};
#endif
