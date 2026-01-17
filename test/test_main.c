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
  filePath = "/i/start/with/a/slash";
  maxBaseNameLength = MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(strcmp(actualBaseName, "slash") == 0);
  free(actualBaseName);
  
  return 0;
}
