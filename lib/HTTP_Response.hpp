#ifndef HTTP_RESP_H
#define HTTP_RESP_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string.h>

class HTTP_Response
{
public:
	HTTP_Response(std::string);
	HTTP_Response();

	std::string                        codigoStatus;
	std::string                        versao;
	std::map<std::string, std::string> campos;
	std::string                        dado;

	void print();
	std::string montaResponse();
};
#endif
