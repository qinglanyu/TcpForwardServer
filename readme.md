# TCP Message Forward Server

This is a tcp server written in Qt 5.12.8

The server instance just listens(at port 8888 or the specified port) for new connections, and saves the connected sockets into groups(groupA or groupB).

Every new connections should firstly tell which group it belongs to, by a "group" value in a json doc.

Then the server forwards messages received from connections in group A to connections in group B. And it also forwards messages from connections in group B to connections in group A.

