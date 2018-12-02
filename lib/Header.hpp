#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>
#include <tuple>

#include "Dump.hpp"

#define campo std::tuple< std::string, std::string >

namespace HTTP{
	struct Header{
		explicit Header(std::string& str);
		std::string to_string(bool include=true);
		std::string corpo;
		std::string destino;
		std::string host;
		std::string porta;
	};
};
#endif
