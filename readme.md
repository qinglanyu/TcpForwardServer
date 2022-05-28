# TCP Message Forward Server

This is a tcp server written in Qt 5.12.8

The server instance just listens(at port 8888 or the specified port) for new connections, and saves the connected sockets into groups(groupA or groupB).

Then it forwards messages received from connections in groupA to connections in groupB.

Every new connections should firstly tell which group it belongs to, by a "group" value in json doc.
