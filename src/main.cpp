#include <iostream>

#include "../lib/HTML_Parser.hpp"
#include "../lib/Spider.hpp"
#include "../lib/Proxy_Server.hpp"
#include "../lib/HTTP_Request.hpp"
#include "../lib/HTTP_Response.hpp"
#include "../lib/String_Functions.hpp"

using namespace std;

int porta;

void argumentoProcessos(int argc, char **argv){
	porta = 8228;
	if(argc == 2)
	{
		string arg(argv[1]);
		if(arg.find("-p") == 0)
		{
			arg = arg.substr(2,arg.length());
		 	if(atoi(arg.c_str()) > 0 && atoi(arg.c_str()) < 100000)
				porta = atoi(arg.c_str());
		}
	}
	if(argc == 3){
		string arg(argv[1]);
		if(arg == "-p")
			if(atoi(argv[2]) > 0 && atoi(argv[2]) < 100000)
				porta = atoi(argv[2]);
	}
}

int printTrafego()
{
	string opcao;
	cout << "Inspecao de resquest replay: 1" << endl;
	cout << "Aperte qualquer tecla para voltar ao menu" << endl;
	cout << "Sua opcao  : ";
	cin >> opcao;
	return atoi(opcao.c_str());
}

void inspetorTrafego(){
	int opt            = 1;
	Proxy_Server proxy = Proxy_Server();

	proxy.init(porta);
	system("clear");
	cout << "inspertor de trafego esta na porta " << porta << endl;
	cout << "Esperando algum Requst" << endl;
	while(opt == 1)
	{
		system("clear");
		cout << "inspetor de trafego esta na  porta " << porta << endl;
		cout << "Esperando request" << endl;

		string           req = proxy.get_client_request();
		HTTP_Request request = HTTP_Request(req);
		cout << "Request recebido Host: " << request.campos["Host:"] << " URL: " << request.url << endl;
		if(request.avaliaMetodo())
		{
			String_Functions::stringParaArquivo(req, ".", "request.txt");
			system("request.txt");

			req                    = String_Functions::stringDoArquivo("request.txt");
			string reply           = proxy.make_request(req);
			HTTP_Response response = HTTP_Response(reply);

			String_Functions::stringParaArquivo(reply, ".", "response.txt");
			system("response.txt");

			reply = String_Functions::stringDoArquivo("response.txt");

			proxy.reply_client(reply);
			system("clear");
			opt = printTrafego();
			cout << "Insetor de trafego na porta " << porta << endl;
			cout << "Eserando request" << endl;
		}else
		{
			cout <<endl<< "Rejeitado apenas get/http " << endl;
		}
	}
}

int print_main_menu()
{
	string opcao;
	cout << "Para Inspetor de trafego tecle 1" << endl;
	cout << "Geracao da arvore de URL's tecle 2" << endl;
	cout << "Dump tecle 3" << endl;
	cout << "Para sair tecle 4" << endl;
	cout << "Selecione sua opcao:  ";
	cin >> opcao;
	return atoi(opcao.c_str());
}

void gerarArvore()
{
	string url;
	system("clear");
	cout << "Gerar Arvore" << endl;
	cout << "Aperte a Url que deseja gerar ";
	cin >> url;
	Spider spider = Spider(url);

	while(!spider.valido)
	{
		system("clear");
		cout << "You have typed an invalido url!" << endl;
		cout << "Generate Tree" << endl;
		cout << "Type the url you want to inspect: ";
		cin >> url;
		spider = Spider(url);
	}
	int lev = 0;
	while(lev < 1 || lev > 4)
	{
		system(" clear");
		string levels;
		cout << "Type the number of levels you want to inspect [1 OR  2]= " ;
		cin >> levels;
		lev = atoi(levels.c_str());
	}
	spider.geraArvore(lev-1);
	spider.printArvore(lev-1);
	string temp;
	cout << "Press any key to go back to main menu...";
	cin >> temp;
}

void dump()
{

	string url;
	system("clear");
	cout << "Dump website" << endl;
	cout << "Type the url you want to dump: ";
	cin >> url;
	Spider spider = Spider(url);

	while(!spider.valido)
	{
		system("clear");
		cout << "You have typed an invalido url!" << endl;
		cout << "Dump website" << endl;
		cout << "Type the url you want to dump= ";
		cin >> url;
		spider = Spider(url);
	}
	int lev = 0;
	while(lev < 1 || lev > 2)
	{
		system("clear");
		string levels;
		cout << "Type the number of levels you want to inspect [0 < l < 4]= " ;
		cin >> levels;
		lev = atoi(levels.c_str());
	}
	spider.dump(lev-1);

	string temp;
	cout << "Press any key to go back to main menu...";
	cin >> temp;

}

int main(int argc, char **argv)
{

	argumentoProcessos(argc, argv);
	cout <<"Aracne started using porta: "<< porta << endl;

	int opt = 1;
	while(opt != 4){
		system("clear");
		if(opt < 1 || opt > 4) cout << "Opção inválida!" << endl;
		opt = print_main_menu();
		if(opt > 0 && opt < 5){
			if(opt == 1){
				inspetorTrafego();
			}
			if(opt == 2) gerarArvore();
			if(opt == 3) dump();
		}
	}




	return 0;
}
