#include <cstdlib>
#include <cstdio>
#include <memory>

#include "Servidor.hpp"
#include "Header.hpp"


Servidor::Servidor(int numPorta) : requests(pIn.requestsRecebidos)
							, responses(pOut.responsesRecebidos)
							, pIn( numPorta )
							, pOut() {}



Servidor::~Servidor() = default;

void Servidor::Inicia(){
	while(true){
	pIn.accConexao();
	pIn.getRequests();
	if(!requests.empty())
		std::swap( requests, sendRequest );

	if(!sendRequest.empty()) {
		printf("\nEnviando %d request(s)...\n", (int) sendRequest.size());

		for (auto &i : sendRequest) {
			//std::cout << i.to_string() << '\n';
			//std::cout << "\nEnviando request para " << i.host.c_str()<<i.porta.c_str();

			
			if(pOut.Send(i) == -1){

				printf("\nNão foi possível enviar request\n");
				exit(1);
			}
		}
		sendRequest.clear();
	}

	pOut.responseRecebido();
	if(!responses.empty()){
		std::swap(responses, sendResponse);
	}

	if(!sendResponse.empty()) {
		printf("\nEnviando %d response(s)...\n", (int) sendResponse.size());

		for(auto &i : sendResponse) { //TÁ COM PROBLEMA AQUI
			printf("\nResponse: \n%s\n", i.host.c_str());
			if(pIn.Send(i) == -1){
				printf("\nNão foi possível enviar response\n");
				exit(1);
			}
		}

		sendResponse.clear();
	}
 }
}
