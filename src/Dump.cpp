#include "Dump.hpp"

Dump::Dump() = default;
Dump::~Dump() = default;

void Dump::DumpHtml(std::string corpo){
	unsigned int start = static_cast<unsigned int>(corpo.find("<"));
	if(start == 0){
		FILE *fp = fopen("dump/dump.html", "a+");
		if(fp == nullptr)
			printf("Arquivo Nao existe \n");
		else{
			fprintf(fp,"%s", corpo.c_str());
			printf("%s\n", corpo.c_str());
			fclose(fp);
			printf("Dump Criado\n");
		}
	}

}
