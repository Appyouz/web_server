make:
	g++ -std=c++17 server.cpp -o server && g++ client.cpp -o client

clean:
	rm -rf *.o
