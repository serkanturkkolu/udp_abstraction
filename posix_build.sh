g++ -std=c++11 -I./include ./src/udpposix.cpp ./posix/server/main.cpp -o ./posix_server
g++ -std=c++11 -I./include ./src/udpposix.cpp ./posix/client/main.cpp -o ./posix_client
