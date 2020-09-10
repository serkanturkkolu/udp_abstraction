g++ -std=c++11 -I./include ./src/*.cpp ./posix/server/main.cpp -o ./posix_server
if [ $? == 0 ]
then
	echo "server executable file was created."
else
	echo "server executable file was NOT created!"
fi
 
g++ -std=c++11 -I./include ./src/*.cpp ./posix/client/main.cpp -o ./posix_client
if [ $? == 0 ] 
then 
	echo "client executable file was created."
else
	echo "client executable file was NOT created!"
fi
