
# this is a qt webserver project

QT += core network

QT -= gui

TARGET = ../bin/jserver

TEMPLATE = app

SOURCES += main.cpp\
   ./udpserver/udpserver.cpp\
   ./tcpserver/tcpserver.cpp

HEADERS += ./udpserver/udpserver.h\
   ./tcpserver/tcpserver.h

CONFIG += c++11 console

