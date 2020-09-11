if [[ $OSTYPE == "msys" ]]; then #for Mingw
	LDFLAGS="-lws2_32"
else
	LDFLAGS=""
fi

g++ -std=c++11 -I./include ./src/*.cpp ./examples/server/main.cpp -o ./posix_server $LDFLAGS
if [ $? == 0 ]
then
	echo "server executable file was created."
else
	echo "server executable file was NOT created!"
fi
 
g++ -std=c++11 -I./include ./src/*.cpp ./examples/client/main.cpp -o ./posix_client $LDFLAGS
if [ $? == 0 ] 
then 
	echo "client executable file was created."
else
	echo "client executable file was NOT created!"
fi

read a