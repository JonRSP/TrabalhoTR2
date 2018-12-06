#include "HTML_Parser.hpp"
#include "Spider.hpp"
#include "Proxy_Server.hpp"
#include "HTTP_Request.hpp"
#include "HTTP_Response.hpp"
#include "String_Functions.hpp"
using namespace std;


Spider::Spider(string url)
{
	string internal       = url;
	vector<string> result = String_Functions::split(internal, "//");

	if(result.size() == 2)
	{
		if(result[0] != "http:")
		{
		 valido = false;
		 return;
		}

		internal = result[1];
	}
	if(result.size() > 2)
	{
	 	valido = false;
	 	return;
	}

	if(internal.find('/')!=0 && internal.find('/') < internal.length())
	{
		vector<string> result2 = String_Functions::splitPrimeiro(internal, "/");
		if(host.length() == 0)
		{
			host = result2[0];
		}else
		{
			valido = false;
			return;
		}
		root = "/";
		root.append(result2[1]);
	}else if(internal.find('/') > internal.length())
	{
		root = "/";
		host = internal;
	}else
	{
		valido = false;
		return;
	}
	valido = true;
};

bool Spider::avaliaUrl(string url)
{
	if(url.size() == 0)
		return false;

	string internal       = url;
	vector<string> result = String_Functions::split(internal, "//");

	if(result.size() == 2)
	{
		if(result[0] != "http:")
			return false;
		internal = result[1];
	}

	if(result.size() > 2)
		return false;


	if(internal.find('/') != 0)
	{
		vector<string> result2 = String_Functions::split(internal, "/");

		if(host.length() == 0)
		{
			return false;
		}else
		{
			if(host != result2[0])
				return false;
		}
	}
	return true;
}

string Spider::parseUrl(string url)
{
	string parsed("");
	string internal       = url;
	vector<string> result = String_Functions::split(internal, "//");

	if(result.size() == 2)
		internal = result[1];

	if(internal.find('/') != 0)
	{
		vector<string> result2 = String_Functions::splitPrimeiro(internal, "/");
		parsed                 = "/";
		parsed.append(result2[1]);
	}else
	{
		parsed = internal;
	}

	if(parsed.find("?") < parsed.length())
	{
		int ask = parsed.find("?");
		parsed  = parsed.substr(0,ask);
	}

	if(parsed != url)
		nomes[parsed] = url;

	return parsed;
}

void Spider::geraArvore(int niveis)
{
	int i = niveis;
	urlsVisitadas.clear();
	par.clear();
	htmls.clear();

	if(!valido)
		return;


	Proxy_Server proxy   = Proxy_Server();
	HTTP_Request request = HTTP_Request();
	request.tratarConexao();
	set<string> requestTo;
	requestTo.insert(root);

	do
	{
		set<string> nextRequest;

		for (std::set<string>::iterator url=requestTo.begin(); url != requestTo.end(); ++url)
		{
			if(urlsVisitadas.find(*url) == urlsVisitadas.end())
			{
				urlsVisitadas.insert(*url);
				request.url             = *url;
				request.campos["Host:"] = host;


				string reply           = proxy.make_request(request.montaRequest());
				HTTP_Response response = HTTP_Response(reply);

				if(response.codigoStatus == "200 OK")
				{
					htmls[*url]           = response.dado;
					set<string> todosUrl = HTML_Parser::getUrl(response.dado.c_str());
					set<string> urlLocal;

					for (std::set<string>::iterator it = todosUrl.begin(); it != todosUrl.end(); ++it)
					{
				        if(this->avaliaUrl(*it))
				        	urlLocal.insert(this->parseUrl(*it));

		     		}
				    par[*url] = urlLocal;
				    for (std::set<string>::iterator it=urlLocal.begin(); it != urlLocal.end(); ++it)
				        nextRequest.insert(*it);
				}
			}
		}
		requestTo = nextRequest;
	 	i--;
	}while(i>=0);
}

std::string Spider::urlNomeArquivo(std::string url_in)
{

	string nomeArquivo("");
	string url = url_in;
	string slash("-");
	vector<string> splitted = String_Functions::split(url, "/");
	if(splitted.size()==1 && splitted[0].length()==0)
	{
		nomeArquivo = "root.html";
		return nomeArquivo;
	}
	for(int i = 0; i < splitted.size(); i++)
			nomeArquivo.append(splitted[i]);

	if(nomeArquivo.find(".") > nomeArquivo.length())
		nomeArquivo.append(".html");
	else if(nomeArquivo.find("?") < nomeArquivo.length()){
		int ask  = nomeArquivo.find("?");
		nomeArquivo = nomeArquivo.substr(0,ask);
	}
	return nomeArquivo;
}

void Spider::dump(int niveis)
{
	this->geraArvore(niveis);
	set<string> traduzir = urlsVisitadas;

	dicionario[root] = "index.html";
	traduzir.erase(root);

	for(set<string>::iterator it = traduzir.begin(); it != traduzir.end(); ++it)
		dicionario[*it]=Spider::urlNomeArquivo(*it);

	for(std::map<string,string>::iterator it = htmls.begin(); it != htmls.end(); ++it)
    	for(std::map<string,string>::iterator dt = dicionario.begin(); dt != dicionario.end(); ++dt)
			{
    		it->second = String_Functions::replace(it->second,"\'","\"");
    		string from("\"");from.append(dt->first.c_str());from.append("\"");
    		string to("\"");to.append(dt->second.c_str());to.append("\"");
    		it->second = String_Functions::replace(it->second,from.c_str(),to.c_str());

    		if(nomes.find(dt->second) != nomes.end())
				{
    			string from("\"");from.append(nomes[dt->second].c_str());from.append("\"");
    			string to("\"");to.append(dt->second.c_str());to.append("\"");
    			it->second = String_Functions::replace(it->second,from.c_str(),to.c_str());
    		}
    }

  string command("rm -rf ");
  command.append(host);
	system(command.c_str());
  command.assign("mkdir ");
  command.append(host);
	system(command.c_str());

   for(std::map<string,string>::iterator it = htmls.begin(); it != htmls.end(); ++it)
	{
		cout << "Saving file: " << dicionario[it->first] << endl;
    String_Functions::stringParaArquivo(it->second, host.c_str(), dicionario[it->first].c_str());
  }
  cout << "Saved files in a new directory named " << host << endl;
  cout << "File \"index.html\" is the root." << endl;
}

void Spider::printArvore(int niveis)
{

	if(niveis==0)
	{
		cout << "TREE OF URLS:"<<endl<<endl;
		cout << root << "---> ";

		int numSpacos     = root.size()+5;
		set<string> filhos = par[root];
		for(set<string>::iterator it = filhos.begin(); it != filhos.end(); ++it)
		{
			cout << *it << endl;
			for(int s =0; s < numSpacos; s++)
				cout << " ";

		}
		cout << endl;
	}
	else if(niveis == 1)
	{
		cout << "TREE OF URLS:"<<endl<<endl;
		cout << root << "---> ";

		int numSpacos     = root.size()+5;
		set<string> filhos = par[root];
		set<string> visitado;

		visitado.insert(root);

		for(set<string>::iterator it = filhos.begin(); it != filhos.end(); ++it){
			if(visitado.find(*it) == visitado.end())
			{
				visitado.insert(*it);
				cout << *it << "---> ";

				int numSpacos2        = numSpacos + (*it).size()+5;
				set<string> granfilhos = par[*it];

				for(set<string>::iterator it2 = granfilhos.begin(); it2!=granfilhos.end(); ++it2)
				{
					cout << *it2 << endl;
					for(int k =0; k<numSpacos2; k++)
						cout << " ";
				}
			}
			cout << endl;
			for(int k =0; k < numSpacos; k++) cout << " ";
		}
		cout << endl;
	}else
	{
		cout << "Sorry, this program only print 1 or 2 niveis" << endl;
	}
}
