#include "defs.h"

int listenSocket;
void handleSig1(int); //forward reference to handle signal function

int main()
{
  int sSock;
  LibraryType *lib;
  char outbuf[MAX_BUFF];

  // initializes the library collecttion and connects server to client
  signal(SIGUSR1, handleSig1);
  initLibrary(&lib,"Library");
  printf("BOOKS: \n");
  formatBooks(&lib->books,outbuf);
  printf("%s", outbuf);
  setupServerSocket(&sSock);
  printf("Waiting for connection request...\n");
  acceptConnection(sSock, &listenSocket);
  printf("connected...\n");

  serveOneClient(listenSocket, lib);

  return 0;
}

//helper function used to handle a closing signal (SIGUSR1)
void handleSig1(int signal) {
  printf("Caught signal %d\n", signal);
  close(listenSocket);
  exit(1);
}
/*
Function: intToRequest()
Purpose: takes integer value from client and returns a requestType enum
Input/Paramater: client side integer (user input)
Output/returned: Request correlating to integer
*/
RequestType intToRequest(int cmd) {
  switch(cmd) {
    case 1:
       return REQ_RET_BOOKS;
    case 2:
       return REQ_CHECK_OUT;
    case 3:
        return REQ_CHECK_IN;
    case 0:
       return REQ_CLOSE;
  }
  return REQ_CLOSE;
}

/*
Function: serverOneClient()
Purpose: handles all of the clients requests relating to the librabry
Input/Paramater: connects to client socket, librabry collection
Output/returned: correlating method associated with what the client requested (view books, check out/in, exit)
*/
void serveOneClient(int clientSocket, LibraryType *lib) {

  int command;
  int bookId;
  int status;
  char outbuf[MAX_BUFF];
  char cmdBuf[MAX_BUFF];
  char statusBuf[MAX_STR];

  while (1) {
    printf("Waiting for request...\n");
    rcvData(listenSocket, cmdBuf);
    printf("received...\n");
    sscanf(cmdBuf, "%d", &command);
    RequestType requestType = intToRequest(command);


    switch(requestType) {
      case REQ_RET_BOOKS:
        formatBooks(&lib->books, outbuf);
        sendData(listenSocket, outbuf);
        break;
      case REQ_CHECK_OUT:
        sscanf(cmdBuf, "%d %d", &command, &bookId);
        status = checkOutBook(lib, bookId);
        sprintf(statusBuf, "%d", status);
        sendData(listenSocket, statusBuf);
        break;
      case REQ_CHECK_IN:
        sscanf(cmdBuf, "%d %d", &command, &bookId);
        status = checkInBook(lib, bookId);
        sprintf(statusBuf, "%d", status);
        sendData(listenSocket, statusBuf);
        break;
      case REQ_CLOSE:
        printf("Received close command\n");
        closeAll(lib);
        break;
    }
  }
}

/*
Function: closeAll
Purpose: deallocates all of the memory and cleans up all of server ressources
Input/Paramater: librabry collection
Output/returned: closes server and socket, nothing is returned
*/
void closeAll(LibraryType *lib) {
  cleanupLibrary(lib);
  close(listenSocket);
  exit(0);
}
