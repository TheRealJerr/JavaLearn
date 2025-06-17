all : client server

client : UdpClient.cpp
	g++ -o $@ $^ -std=c++11
server : UdpServer.cpp
	g++ -o $@ $^ -std=c++11
.PHONY : clean
clean : 
	rm -rf client server
