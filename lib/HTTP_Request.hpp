#ifndef HTTP_REQ_H
#define HTTP_REQ_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string.h>


class HTTP_Request
{
public:
	HTTP_Request(std::string);
	HTTP_Request();

	std::string                        metodo;
	std::string                        url;
	std::string                        versao;
	std::map<std::string, std::string> campos;
	std::string                        corpo;

	void        print();
	void        tratarConexao();
	bool        avaliaMetodo();
	std::string montaRequest();
};
#endif
