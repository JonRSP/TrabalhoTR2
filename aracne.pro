#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T23:41:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aracne
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        aracneui.cpp \
    HTML_Parser.cpp \
    HTTP_Request.cpp \
    HTTP_Response.cpp \
    Proxy_Server.cpp \
    Spider.cpp \
    String_Functions.cpp

HEADERS  += aracneui.h \
    HTTP_Request.hpp \
    HTTP_Response.hpp \
    Proxy_Server.hpp \
    String_Functions.hpp \
    Spider.hpp \
    HTML_Parser.hpp

FORMS    += aracneui.ui
