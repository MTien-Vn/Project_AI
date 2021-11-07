#include <stdio.h>
#include "reader.h"

FILE *inputStream;
int lineNo, colNo;
int currentChar;

int readChar(void) {
  currentChar = getc(inputStream);
  colNo ++;
  if (currentChar == '\n') {
    lineNo ++;
    colNo = -1;
  }
  return currentChar;
}

int openInputStream(char *fileName) {
  inputStream = fopen(fileName, "rt");
  if (inputStream == NULL)
    return IO_ERROR;
  lineNo = 0;
  colNo = -1;
  readChar();
  return IO_SUCCESS;
}

void closeInputStream() {
  fclose(inputStream);
}
