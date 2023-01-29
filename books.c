#include "defs.h"


//forward reference for a helper function being used in this file. It is not
//forward referenced in defs.h as it would be used there at all, saves time and memory
char *statusToString(BookStatusType);


/*
Function: initList()
Purpose: initializes the starting contents if the link list being used
Input/Paramater: a BookListType structure which contains a head and tail
Output/returned: nothing it is a void function however since a pointer is
being passed in, the contents that are being changed will carry over to the next function
*/
void initList(BookListType *list){
	list->head = NULL;
	list->tail=NULL;
}


/*
Function: initBook
Purpose: intialize all of the data of the book being passed in
Input/Paramater: all of the data needed to intialized one book in the collection
Output/returned: does not return anything however the data that is used to intialize a book
will be carried over as it is being store in a pointer
*/
void initBook(int i, char *t, char *a, int y, BookStatusType st, BookType **book){
  BookType *newBook = malloc(sizeof(BookType));
  newBook->id = i;
  strcpy(newBook->title,t);
  strcpy(newBook->author,a);
  newBook->year = y;
  newBook->status = st;
  *book = newBook;
}


/*
Function: addBook()
Purpose: add a book into the books collection, ordered alphabetically by name
Input/Paramater: a BookListType(linked-list/books collection) and a bookType (individual book behing added)
Output/returned: nothing is outputted/returned as it is a void function, however the content of the
linked-list is being modified and will stay modified becaue the collection is being passed in as a pointer
*/
void addBook(BookListType *list, BookType *b) {
  NodeType *newNode = malloc(sizeof(NodeType));
  NodeType *currentNode = list->head;
  NodeType *previousNode = NULL;
  newNode->data = b;
  newNode->next = NULL;

  //if this the linked list is empty, add to the beginning
  if (list->head == NULL){
    list->head = newNode;
    list->tail = newNode;
    return;
  }


  while(currentNode != list->tail){
    if (strcmp(b->title, currentNode->data->title) < 0){

      if (currentNode == list->head){
        list->head = newNode;
        newNode->next = currentNode;
        return;
      } else {
        newNode->next = currentNode;
        previousNode->next = newNode;
        return;
      }
    }

    previousNode = currentNode;
    currentNode = currentNode->next;
  }

  if (strcmp(b->title, currentNode->data->title) < 0){
    if (currentNode == list->head){
      list->head = newNode;
      newNode->next = currentNode;
      return;
    }
    previousNode->next = newNode;
    newNode->next = currentNode;
  } else{

    currentNode->next = newNode;
    list->tail = newNode;
  }

}


/*
Function: findbook()
Purpose: traverse the book collection and tries to find a book with the matching id
Input/Paramater: book collection, the desired id to look for and a booktype whos data will be
modified to the found book, if the id is matched correctly
Output/returned: returns a success flag based off of if the the book was found or not
*/
int findBook(BookListType *list, int id, BookType **b) {
  NodeType *currentNode = list->head;
	if (currentNode == NULL){
		return C_BOOK_NOT_FOUND;
	}
  while (currentNode != list->tail){
    if (currentNode->data->id == id){
      *b = currentNode->data;
      return C_OK;
    }
    currentNode = currentNode->next;
  }

  if (currentNode->data->id == id){
    *b = currentNode->data;
    return C_OK;
  }

  return C_BOOK_NOT_FOUND;

}


/*
Function:formatBook
Purpose: formats the information of a singular book into a well formatted line
Input/Paramater: a book and a char * that hold all of this info into one big string
Output/returned: returns the char *(all of the books data)
*/
void formatBook(BookType *b, char *outStr) {
  sprintf(outStr, "%-10d %-40s %-20s %-10d %-10s\n", b->id, b->title, b->author, b->year, statusToString(b->status));
}


/*
Function: statusToString()
Purpose: helper function used to convert the enum values into a string, therefore it can be outputted onto the screeen
Input/Paramater: the books current status
Output/returned: string version of the books status
*/
char *statusToString(BookStatusType status){
  switch (status){
    case CHECKED_IN:
      return "Checked In";
      break;

    case CHECKED_OUT:
      return "Checked Out";
      break;

    case UNDER_REPAIR:
      return "Under Repair";
      break;

    case LOST:
      return "Lost";
      break;

  }
  return "Unknown status type";
}


/*
Function: formatBooks()
Purpose: goes through the whole book collection and prints the data of each book present in the book
collection linked list.
Input/Paramater: BookListType (linked list) and a output String
Output/returned: prints out concatenated version of the whole book collection inside one char * variable.
reason why every book in the concatenated string is seperated is because in formatBook, i added a \n
*/
void formatBooks(BookListType *list, char *outStr) {
  strcpy(outStr,"");
  NodeType *currentNode = list->head;

  char outStrBook[MAX_BUFF];
  if (currentNode == NULL){
    return;
  }
  while(currentNode != list->tail){
    formatBook(currentNode->data, outStrBook);
    strcat(outStr, outStrBook);
    currentNode = currentNode->next;
  }
  formatBook(currentNode->data,outStrBook);
  strcat(outStr,outStrBook);
	formatBook(list->head->data, outStrBook);
	strcat(outStr, "--HEAD: ");
	strcat(outStr,outStrBook);
	formatBook(list->tail->data, outStrBook);
	strcat(outStr, "--TAIL: ");
	strcat(outStr, outStrBook);
}


/*
Function: cleanupList()
Purpose: deallocates all of the memory in the book collection. All the data
of each book will be deallocated from the heap.
Input/Paramater: a BookListType type (book collection/linked list)
Output/returned: nothing is outputted, all of the memory is just deallocated
*/
void cleanupList(BookListType *list) {
  NodeType *currentNode = list->head;
  NodeType *tempNode;
  if (currentNode == NULL){
    return;
  }
  while(currentNode!=list->tail){
    tempNode = currentNode->next;
    free(currentNode->data);
    free(currentNode);
    currentNode = tempNode ;

  }
}
