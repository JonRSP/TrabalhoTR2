#include "../lib/HTTP_Request.hpp"
#include "../lib/String_Functions.hpp"

using namespace std;


HTTP_Request::HTTP_Request(std::string requestString)
{
    vector<string> requestSeparado = String_Functions::split(requestString, "\r\n\r\n");
    string         header          = requestSeparado[0];

    if(requestSeparado.size()>1)
        corpo = requestSeparado[1];

    vector<string> linhas        = String_Functions::split(header, "\r\n");
    string         primeiraLinha = linhas[0];
    vector<string> fl_tokens     = String_Functions::split(primeiraLinha, " ");

    metodo = fl_tokens[0];
    url    = fl_tokens[1];
    versao = fl_tokens[2];

    vector<string> temp;

    for( int i = 1; i<linhas.size(); i++)
    {
         temp            = String_Functions::splitPrimeiro(linhas[i], " ");
         campos[temp[0]] = temp[1];
    }
};

HTTP_Request::HTTP_Request()
{
    metodo = "GET";
    versao = "HTTP/1.1";
    url    = "";
    corpo  = "";
};

std::string HTTP_Request::montaRequest()
{
    using namespace std;
    string Request("");

    Request.append(metodo);
    Request.append(" ");
    Request.append(url);
    Request.append(" ");
    Request.append(versao);
    Request.append("\r\n");

    for (std::map<string,string>::iterator it=campos.begin(); it!=campos.end(); ++it)
    {
        Request.append(it->first);
        Request.append(" ");
        Request.append(it->second);
        Request.append("\r\n");
    }
    Request.append("\r\n");
    Request.append(corpo);

    return Request;
}

void HTTP_Request::print()
{
    cout << "metodo: " << metodo << endl;
    cout << "versao: " << versao << endl;
    cout << "url: " << url << endl;

    for(map<string, string>::iterator it = campos.begin(); it!=campos.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }
    cout << "corpo: " << corpo << endl<<endl;

}

void HTTP_Request::tratarConexao()
{
    campos["Connection:"]      = "close";
    campos["Accept-Encoding:"] = "identity";
}

bool HTTP_Request::avaliaMetodo()
{
    if( metodo != "GET") return false;
    return true;
}
