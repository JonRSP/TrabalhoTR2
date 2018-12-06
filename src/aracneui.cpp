#include "aracneui.h"
#include "ui_aracneui.h"
#include "Proxy_Server.hpp"
#include "HTTP_Request.hpp"
#include "HTTP_Response.hpp"
#include "String_Functions.hpp"
#include "Spider.hpp"


using namespace std;
AracneUI::AracneUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AracneUI)
{
    ui->setupUi(this);
}

AracneUI::~AracneUI()
{
    delete ui;
}
void AracneUI::startInsp(int porta)
{
    int opt            = 1;
    server = Proxy_Server();

    server.init(porta);
        req = server.get_client_request();
        ui->te_request->setPlainText(req.c_str());
        HTTP_Request request = HTTP_Request(req);

            String_Functions::stringParaArquivo(req, ".", "request.txt");
            req                    = String_Functions::stringDoArquivo("request.txt");
}

void AracneUI::spider(char* url)
{
    Spider spider = Spider(url);
    if(spider.valido)
    {
        string aux;
        spider.geraArvore(2);
        aux = "TREE OF URLS:";
        aux += spider.root ;

        int numSpacos     = spider.root.size()+5;
        set<string> filhos = spider.par[spider.root];
        set<string> visitado;

        visitado.insert(spider.root);

        for(set<string>::iterator it = filhos.begin(); it != filhos.end(); ++it){
            if(visitado.find(*it) == visitado.end())
            {
                visitado.insert(*it);
                aux+= *it +"---> ";

                int numSpacos2        = numSpacos + (*it).size()+5;
                set<string> granfilhos = spider.par[*it];

                for(set<string>::iterator it2 = granfilhos.begin(); it2!=granfilhos.end(); ++it2)
                {
                    aux += *it2 + "\n";
                    for(int k =0; k<numSpacos2; k++)
                        aux =+ " ";
                }
            }
            aux += "\n";
            for(int k =0; k < numSpacos; k++) aux+= " ";
        }
        aux+= "\n";
        ui->te_spider->setPlainText(aux.c_str());
    }
}

void AracneUI::on_pb_spidergo_clicked()
{
    QByteArray ba = ui->le_spider->text().toLocal8Bit();
    char *c_str = (char*)ba.data();
    spider(c_str);
}

void AracneUI::on_pb_start_clicked()
{
    startInsp(ui->le_port->text().toInt());
}

void AracneUI::on_pb_dump_clicked()
{
    QByteArray ba = ui->le_dump->text().toLocal8Bit();
    char *c_str = (char*)ba.data();
    Spider x = Spider(c_str);
    x.dump(2);
}

void AracneUI::on_pb_request_clicked()
{
    string           req = server.get_client_request();
    ui->te_request->setPlainText(req.c_str());
    HTTP_Request request = HTTP_Request(req);
}

void AracneUI::on_pb_response_clicked()
{
    reply           = server.make_request(req);
    HTTP_Response response = HTTP_Response(reply);

    String_Functions::stringParaArquivo(reply, ".", "response.txt");
    reply = String_Functions::stringDoArquivo("response.txt");
    ui->te_response->setPlainText(reply.c_str());
    server.reply_client(reply);
}
