#include "HTML_Parser.hpp"
#include "Spider.hpp"
#include "Proxy_Server.hpp"
#include "HTTP_Request.hpp"
#include "HTTP_Response.hpp"
#include "String_Functions.hpp"
#include "aracneui.h"
#include <QApplication>

using namespace std;

int porta;

int main(int argc, char *argv[])
{
    porta = 8228;
    if(argc == 3 and (std::string)argv[1] == "-p")
    {
        porta = atoi(argv[2]);
        if(porta < 0 or porta > 100000)
        {
            exit(1);
        }
    }
    QApplication a(argc, argv);
    AracneUI w;
    w.show();

    return a.exec();
}
