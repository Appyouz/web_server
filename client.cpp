#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // Sending connection request
  connect(clientSocket, (struct sockaddr *)&serverAddress,
          sizeof(serverAddress));

  // Send message
  // const char *message = "Hello, Server. Send me secret password.";
  const char *message = "GET / HTTP/1.1\n Host: localhost:8080";
  send(clientSocket, message, strlen(message), 0);

  char buffer[1024] = {0};
  recv(clientSocket, buffer, sizeof(buffer), 0);
  std::cout << "Message from the server: " << buffer << '\n';

  close(clientSocket);
  return 0;
}
