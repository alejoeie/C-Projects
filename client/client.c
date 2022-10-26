#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv){
  
  int sockfd;
  int len;
  struct sockaddr_un address;
  int result;
  char ch = 'A';
  
  // Create a socket for the client.
  sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  // Name the socket as agreed with the server.
  address.sun_family = AF_UNIX;
  strcpy(address.sun_path, "server_socket");
  len = sizeof(address);

  // Connect the socket to the server socket.
  result = connect(sockfd, (struct sockaddr *)&address, len);

  if (result == -1){
    perror("Errors");
    exit(1);
  }
  // Read and write via sockfd.
  write(sockfd, &ch, 1);
  read(sockfd, &ch, 1);
  printf("Char from server = %c\n", ch);
  close(sockfd);
  exit(0);
  return 0;
}
