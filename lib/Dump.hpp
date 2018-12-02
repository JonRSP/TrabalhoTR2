#ifndef DUMP_H
#define DUMP_H

#include <fstream>
#include <string>
#include <iostream>

class Dump{
	public:
		Dump();
		~Dump();
		static void DumpHtml(std::string corpo);
};
#endif

