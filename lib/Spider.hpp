#ifndef SPIDER_H
#define SPIDER_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string.h>

class Spider
{
public:
	Spider(std::string);

	bool                                         valido;
	std::string 																 root;
	std::string 																 host;
	std::set<std::string> 											 urlsVisitadas;
	std::map<std::string, std::string> 					 htmls;
	std::map<std::string, std::string>           dicionario;
	std::map<std::string, std::string>           nomes;
	std::map<std::string, std::set<std::string>> par;

	bool        avaliaUrl(std::string url);
	std::string parseUrl(std::string url);
	std::string urlNomeArquivo(std::string url);
	void        geraArvore(int);
	void        printArvore(int);
	void        dump(int);
};
#endif
