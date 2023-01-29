#include "defs.h"



int main()
{
  int  choice = -1;

  int cSock;
  int bookId;
  int status;
  setupClientSocket(&cSock);
  char buffer[MAX_BUFF];
  char command[MAX_BUFF];
  while (1) {

   clientMenu(&choice);

   switch(choice) {

      case 1:   // Print books
        sendData(cSock, "1");
        rcvData(cSock, buffer);
        printf("%s", buffer);
        break;

      case 2:   // Check out a book
        printf("Enter bookID for book you want to check out: ");
        scanf("%d", &bookId);
        sprintf(command, "%d %d", 2, bookId);
        sendData(cSock, command);
        rcvData(cSock, buffer);
        sscanf(buffer, "%d", &status);
        if (status == C_OK) {
          printf("Book successfully checked out.\n");
        } else if (status == C_BOOK_NOT_FOUND) {
          printf("Book with id %d does not exist.\n", bookId);
        } else {
          printf("Book with id %d cannot be checked out at this time.\n", bookId);
        }
        break;

      case 3:   // Check in a book
      printf("Enter bookID for book you want to check out: ");
      scanf("%d", &bookId);
      sprintf(command, "%d %d", 3, bookId);
      sendData(cSock, command);
      rcvData(cSock, buffer);
      sscanf(buffer, "%d", &status);
      if (status == C_OK) {
        printf("Book successfully checked in.\n");
      } else if (status == C_BOOK_NOT_FOUND) {
        printf("Book with id %d does not exist.\n", bookId);
      } else {
        printf("Book with id %d cannot be checked in at this time.\n", bookId);
      }


        break;

      case 0:   // Close everything
        sendData(cSock, "0");
        close(cSock);
        exit(0);
        break;

      default:
        printf("ERROR:  invalid option\n");
    }
  }

  return 0;
}

void clientMenu(int* choice)
{
  int c = -1;
  int numOptions = 3;
  char str[MAX_STR];

  printf("\nMAIN MENU\n");
  printf("  (1) Print books\n");
  printf("  (2) Check out a book\n");
  printf("  (3) Check in a book\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = 0;
  sscanf(str, "%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &c);
  }

  *choice = c;
}
