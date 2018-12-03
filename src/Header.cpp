#include "Header.hpp"
#include <string.h>
namespace HTTP{
	Header::Header(std::string& msg){
		if(msg.size()!=0){
			std::size_t found = msg.find("Host: ");
			host = msg.substr(found+6);
			host = host.substr(0,host.find("\n")-1);
			std::string aux = std::string("http://",strlen("http://"))+host;
			std::size_t found2 = msg.find("\n");
			destino = msg.substr(0, found2);
			std::size_t found3 =destino.find(' ',0);
			destino = destino.erase(found3, (found3+strlen(aux.c_str())-2));
			destino = destino.insert(found3,1,' ');
			corpo = msg.substr(found+6+host.size());
			found = msg.find("Port: ");
				porta = "80";


	}
}

	std::string Header::to_string(bool include){
		std::string msg("");
		//memset(&msg, 0,sizeof(std::string));


		msg += destino + "\n";
		msg += "Host: ";
		msg+= host;
	//	msg += ":";
	//	msg += porta;

		//std::cout << " message " <<  host.c_str();Dump::DumpHtml(Header::Header(i).corpo.to_string());
		//msg += "Host: " +host+':'+porta;
		msg += include? corpo : "";
		
		return msg;

	}

}
