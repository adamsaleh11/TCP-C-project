#include "defs.h"


//helper function used to read the next line in the file using fgets()
char* readLine(char *line, int size, FILE *fp) {
  char* ret = fgets(line, MAX_STR, fp);
  if (ret == NULL) {
    return NULL;
  }

  int len = strlen(ret);
  if (len > 0 && ret[len-1] == '\n') {
    ret[len-1] = 0;
  }

  return ret;
}


//helper function used to convert the book status as an int given in the txt file into
//the corresponding string enum status
BookStatusType intTotStatus (int status){
  switch (status){
    case 0:
      return CHECKED_IN;
    case 1:
      return CHECKED_OUT;
    case 2:
      return UNDER_REPAIR;
    case 3:
      return LOST;
  }
  return CHECKED_IN;
}


/*
Function: loadBooks()
Purpose: Load all of the the books being presented in the txt file and adds them
the book collection
Input/Paramater: A BookListType structure (book collection)
Output/returned: returns a concatenated string of all of the books that have been loaded from the txt file.
Although is it a void function, the functions within loadbooks() allow for something to be outputted in the screen whenever we
run this function.
*/
void loadBooks(BookListType *books) {
  char title[MAX_STR];
  char author[MAX_STR];
  int year;
  int counter = 1001;
  int status ;
  BookType *book;

  FILE *fp = fopen("booksData.txt", "r");
  if (fp != NULL) {
    char line [MAX_STR];
    while(readLine(title,MAX_STR,fp)!= NULL){
      readLine(author,MAX_STR,fp);
      readLine(line,MAX_STR,fp); //reads the next line, does not store line into any variable yet
      sscanf(line, "%d", &year);
      readLine(line,MAX_STR,fp);
      sscanf(line,"%d", &status);
      initBook(counter,title,author,year,intTotStatus(status),&book);
      addBook(books,book);
      counter++;
    }
    fclose(fp);
  }
}


/*
Function: initLibrary()
Purpose: load all of the book data, intialize its content and store into the library collection
Input/Paramater: Take a Library structure time and a char * (also known as a string) which represents the name of the library
Output/returned: returns an initialized librabry into the double pointer being passed in
*/
void initLibrary(LibraryType **library, char *n){
  LibraryType *newLibrary = malloc(sizeof(LibraryType));
  char output[MAX_BUFF];
  strcpy(newLibrary->name,n);
  initList(&newLibrary->books);
  loadBooks(&newLibrary->books);
  formatBooks(&newLibrary->books, output);
  *library = newLibrary;
}


/*
Function: checkOutBook()
Purpose: change the status of a book to CHECKED_OUT if the book is currently CHECKED_IN
if not, return a bad status flag or C_BOOK_NOT_FOUND indicating that the book was not checked in
Input/Paramater: a librabry collection and the specific book ID that you are looking for
Output: success flag or unsuccesful flag
*/
int checkOutBook(LibraryType *lib, int bookId) {
  BookType *book;
  if (findBook(&lib->books, bookId, &book) == C_OK){
    if (book->status == CHECKED_IN){
      book->status = CHECKED_OUT;
      return C_OK;
    } else {
      return C_BAD_STATUS;
    }
  }
  return C_BOOK_NOT_FOUND;
}


/*
Function: checkInBook()
Purpose: change the status of a book to CHECKED_IN if the book is currently CHECKED_OUT
if not, return a bad status flag or C_BOOK_NOT_FOUND indicating that the book was not checked out to begin with
Input/Paramater: a librabry collection and the specific book ID that you are looking for
Output: success flag or unsuccesful flag
*/
int checkInBook(LibraryType *lib, int bookId) {
  BookType *book;
  if (findBook(&lib->books, bookId, &book) == C_OK){
    if (book->status == CHECKED_OUT){
      book->status = CHECKED_IN;
      return C_OK;
    } else {
      return C_BAD_STATUS;
    }
  }
  return C_BOOK_NOT_FOUND;
}


/*
Function: cleanupLibrary()
Purpose: deallocates all of the memory on the heap provided to the library collection
Input/Paramater: a library collection
Output: nothing its a void function that simply deallocates memory and thats it
*/
void cleanupLibrary(LibraryType *lib) {
  cleanupList(&lib->books);
  free(lib);
}
