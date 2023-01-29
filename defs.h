#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 60002

#define C_OK                 0
#define C_NOK               -1
#define C_BOOK_NOT_FOUND    -2
#define C_BAD_STATUS        -3

#define MAX_BUFF   2048
#define MAX_ARR     128
#define MAX_STR      64

typedef enum {CHECKED_IN, CHECKED_OUT, UNDER_REPAIR, LOST
} BookStatusType;

typedef enum {REQ_RET_BOOKS, REQ_CHECK_IN,
              REQ_CHECK_OUT, REQ_CLOSE
} RequestType;

typedef struct {
  int id;
  char title[MAX_STR];
  char author[MAX_STR];
  int  year;
  BookStatusType status;
} BookType;

typedef struct Node {
  BookType    *data;
  struct Node *next;
} NodeType;

typedef struct {
  NodeType *head;
  NodeType *tail;
} BookListType;

typedef struct {
  char            name[MAX_STR];
  BookListType    books;
} LibraryType;


void setupServerSocket(int*);
void acceptConnection(int, int*);
void setupClientSocket(int*);
void rcvData(int, char*);
void sendData(int, char*);

void clientMenu(int*);
void initList(BookListType *);
void initBook(int , char *, char *, int , BookStatusType ,BookType **);
void addBook(BookListType *, BookType *);
int findBook(BookListType *, int , BookType **);
void formatBook(BookType *, char *);
void formatBooks(BookListType *, char *);
void cleanupList(BookListType *);
void loadBooks(BookListType *);
void initLibrary(LibraryType **, char *);
int checkOutBook(LibraryType *, int);
int checkInBook(LibraryType *, int);
void cleanupLibrary(LibraryType *);
void serveOneClient(int, LibraryType *);
void closeAll(LibraryType *);
