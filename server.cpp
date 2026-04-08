#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /// Create a socker
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  // Defining server address
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // Binding socket
  // Without this socket exists but has no address or port
  bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

  // Listen for incoming connection
  listen(serverSocket, 5);

  // Accept the client  connection
  // nullptr means here just give me the client socket to communicate with,
  // don't bother telling me who they are
  int clientSocket = accept(serverSocket, nullptr, nullptr);

  // Receive date from the client
  char buffer[1024] = {0};
  recv(clientSocket, buffer, sizeof(buffer), 0);
  std::cout << "Message from the client: " << buffer << '\n';

  // Send response
  const char *message = {
      " HTTP/1.1 200 OK \nContent-Type: text/plain\n Hello World "};
  send(clientSocket, message, strlen(message), 0);
  std::cout << "message: " << message << '\n';

  close(serverSocket);
  close(clientSocket);
  return 0;
}
