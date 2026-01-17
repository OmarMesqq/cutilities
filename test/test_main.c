#include "../cutilities.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_BASENAME 200

int main(void) {
  char* fullFilePath = "/some/file/path/with/basename/at/end";
  char* bn = get_basename(fullFilePath, MAX_FILE_BASENAME);
  assert(strcmp(bn, "end") == 0);
  
  free(bn);
  return 0;
}
