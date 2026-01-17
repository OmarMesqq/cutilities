#include "../cutilities.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_BASENAME_LEN 200
#define SMALL_MAX_FILE_BASENAME_LEN 5

int main(void) {
  /** get_basename tests */

  char* filePath = NULL;
  unsigned maxBaseNameLength = 0;
  char* actualBaseName = NULL;

  // 1. no filePath
  assert(get_basename(filePath, maxBaseNameLength) == NULL);

  // 2. no max length is zero
  filePath = "/some/path";
  maxBaseNameLength = 0;
  assert(get_basename(filePath, maxBaseNameLength) == NULL);

  // 3. path starting with /
  filePath = "/I/start/with/a/slash";
  maxBaseNameLength = MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(strcmp(actualBaseName, "slash") == 0);
  free(actualBaseName);

  // 4. path NOT starting with /
  filePath = "I/do/not/start/with/a/slash";
  maxBaseNameLength = MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(strcmp(actualBaseName, "slash") == 0);
  free(actualBaseName);

  // 5. path  starting with .
  filePath = "./I/start/with/a/dot";
  maxBaseNameLength = MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(strcmp(actualBaseName, "dot") == 0);
  free(actualBaseName);

  // 6. path  starting with ..
  filePath = "../I/start/with/..";
  maxBaseNameLength = MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(strcmp(actualBaseName, "..") == 0);
  free(actualBaseName);
  
  printf("All Cutilities tests passed!\n");
  return 0;
}
