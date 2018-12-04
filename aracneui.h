#ifndef ARACNEUI_H
#define ARACNEUI_H

#include <QMainWindow>
#include "Proxy_Server.hpp"

namespace Ui {
class AracneUI;
}

class AracneUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit AracneUI(QWidget *parent = 0);
    ~AracneUI();

private slots:
    void on_pb_spidergo_clicked();

    void on_pb_start_clicked();

    void on_pb_dump_clicked();

    void on_pb_request_clicked();

    void on_pb_response_clicked();

private:
    Ui::AracneUI *ui;
    void startInsp(int);
    void spider(char*);
    Proxy_Server server;
    std::string           req;
    std::string           reply;
};

#endif // ARACNEUI_H
