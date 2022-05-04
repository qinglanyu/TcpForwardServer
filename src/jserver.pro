
# this is a qt webserver project

QT += core network

QT -= gui

TARGET = ../bin/jserver

TEMPLATE = app

SOURCES += main.cpp\
   ./udpserver/udpserver.cpp

HEADERS += ./udpserver/udpserver.h

CONFIG += c++11 console

