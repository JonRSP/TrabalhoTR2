#include "HTTP_Response.hpp"
#include "String_Functions.hpp"
using namespace std;

HTTP_Response::HTTP_Response(std::string stringResponse)
{
    vector<string> stringDividida = String_Functions::split(stringResponse, "\r\n\r\n");

    if(stringDividida.size() < 2)
        stringDividida = String_Functions::splitPrimeiro(stringResponse, "\n\n");

    string header               = stringDividida[0];
	  dado                        = stringDividida[1];
	  vector<string> hd_lines     = String_Functions::split(header, "\r\n");
	  string primeiraLinha        = hd_lines[0];
	  vector<string> fl_tokens    = String_Functions::splitPrimeiro(primeiraLinha, " ");
    versao                      = fl_tokens[0];
    codigoStatus                = fl_tokens[1];
    vector<string> temp;

    for(int i = 1; i < hd_lines.size(); i++)
    {
         temp            = String_Functions::splitPrimeiro(hd_lines[i], " ");
         campos[temp[0]] = temp[1];
    }
};

HTTP_Response::HTTP_Response(){};

std::string HTTP_Response::montaResponse()
{
    using  namespace std;
    string Response("");

    Response.append(versao);
    Response.append(" ");
    Response.append(codigoStatus);
    Response.append("\r\n");

    campos["Content-Length:"] = to_string(dado.length());

    for (std::map<string,string>::iterator it=campos.begin(); it != campos.end(); ++it)
    {
        Response.append(it->first);
        Response.append(" ");
        Response.append(it->second);
        Response.append("\r\n");
    }
    Response.append("\r\n");
    Response.append(dado);
    Response.append("\r\n");
    return Response;
}


void HTTP_Response::print()
{
    cout << "status code: " << codigoStatus << endl;
    cout << "versao: " << versao << endl;

    for(map<string, string>::iterator it = campos.begin(); it != campos.end(); ++it){
        cout << it->first << " " << it->second << endl;
    }
    cout << "dado: " << endl << dado <<endl;
}
