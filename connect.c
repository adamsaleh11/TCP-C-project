#include "defs.h"

void setupServerSocket(int *s)
{
  struct sockaddr_in serverAddr;
  int i;

  // Create listen socket
  *s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (*s < 0) {
    printf("Could not open socket\n");
    exit(-1);
  }

  // Setup server address
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons((unsigned short) SERVER_PORT);

  // Bind listen socket 

  i = bind(*s, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if (i < 0) {
    printf("Could not bind socket\n");
    exit(-1);
  }

  // Listen on socket 
  i = listen(*s, 5);
  if (i < 0) {
    printf("Could not setup listening on socket\n");
    exit(-1);
  }
}

void acceptConnection(int lSock, int *cSock)
{
  struct sockaddr_in clientAddr;
  socklen_t addrSize;

  // Wait for connection request 
  addrSize = sizeof(clientAddr);

  *cSock = accept(lSock, (struct sockaddr *) &clientAddr, &addrSize);
  if (*cSock < 0) {
    printf("Could not accept the connection\n");
    exit(-1);
  }
}

void setupClientSocket(int *s)
{
  struct sockaddr_in addr;
  int i;

  // Create socket 
  *s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (*s < 0) {
    printf("Could not open socket\n");
    exit(-1);
  }

  // Setup address
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  addr.sin_port = htons((unsigned short) SERVER_PORT);

  // Connect to server

  i = connect(*s, (struct sockaddr *) &addr, sizeof(addr));
  if (i<0) {
    printf("Client could not connect\n");
    exit(-1);
  }
}

void sendData(int s, char *buffer)
{
  send(s, buffer, strlen(buffer), 0);
}

void rcvData(int s, char *buffer)
{
  char tmpBuff[MAX_BUFF];
  int bytesRcv;

  // Read message from client
  bytesRcv = recv(s, tmpBuff, sizeof(tmpBuff), 0);
  tmpBuff[bytesRcv] = 0;
  strcpy(buffer, tmpBuff);
}


