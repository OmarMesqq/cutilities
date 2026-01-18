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

  // 1. No filePath
  assert(get_basename(filePath, maxBaseNameLength) == NULL);

  // 2. No max length is zero
  filePath = "/some/path";
  maxBaseNameLength = 0;
  assert(get_basename(filePath, maxBaseNameLength) == NULL);

  // 3. Path starting with /
  filePath = "/I/start/with/a/slash";
  maxBaseNameLength = MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "slash") == 0);
  free(actualBaseName);

  // 4. Path NOT starting with /
  filePath = "I/do/not/start/with/a/slash";
  maxBaseNameLength = MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "slash") == 0);
  free(actualBaseName);

  // 5. Path  starting with .
  filePath = "./I/start/with/a/dot";
  maxBaseNameLength = MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "dot") == 0);
  free(actualBaseName);

  // 6. Path  starting with ..
  filePath = "../I/start/with/..";
  maxBaseNameLength = MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "..") == 0);
  free(actualBaseName);

  // 7. File in current directory (No slashes)
  filePath = "simple_file.txt";
  actualBaseName = get_basename(filePath, MAX_FILE_BASENAME_LEN);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "simple_file.txt") == 0);
  free(actualBaseName);

  // 8. Trailing slashes (should strip trailing slashes)
  filePath = "/path/to/folder/"; 
  actualBaseName = get_basename(filePath, MAX_FILE_BASENAME_LEN);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "folder") == 0);
  free(actualBaseName);

  // 9. Root path
  filePath = "/";
  actualBaseName = get_basename(filePath, MAX_FILE_BASENAME_LEN);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "/") == 0); 
  free(actualBaseName);

  // 10. Multiple/Redundant Slashes
  filePath = "/path//to///file";
  actualBaseName = get_basename(filePath, MAX_FILE_BASENAME_LEN);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "file") == 0);
  free(actualBaseName);

  // 11. Truncation / Buffer Limit Logic
  filePath = "/path/to/very_long_filename.txt";
  maxBaseNameLength = SMALL_MAX_FILE_BASENAME_LEN; 
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(actualBaseName != NULL);
  assert(strlen(actualBaseName) < SMALL_MAX_FILE_BASENAME_LEN);
  assert(strcmp(actualBaseName, "very") == 0); // 4 chars + NULL terminator
  free(actualBaseName);

  // 12. Empty String
  filePath = "";
  actualBaseName = get_basename(filePath, MAX_FILE_BASENAME_LEN);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "") == 0);
  free(actualBaseName);

  // 13. Root with multiple slashes
  filePath = "///";
  actualBaseName = get_basename(filePath, MAX_FILE_BASENAME_LEN);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "/") == 0);
  free(actualBaseName);

  // 14. Premature Truncation
  // Scenario: The directory name is longer than the buffer, but the filename is short.
  filePath = "/very_long_directory_name/file.txt";
  maxBaseNameLength = SMALL_MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "file") == 0); 
  free(actualBaseName);

  // 15. Trailing and Leading Slashes
  filePath = "///path/to/folder///"; 
  maxBaseNameLength = MAX_FILE_BASENAME_LEN;
  actualBaseName = get_basename(filePath, maxBaseNameLength);
  assert(actualBaseName != NULL);
  assert(strcmp(actualBaseName, "folder") == 0);
  free(actualBaseName);


  /** odd_ones tests */
  unsigned int x = 0;
  assert(odd_ones(x) == 0);
  
  x = 1;
  assert(odd_ones(x) == 1);

  x = 8;
  assert(odd_ones(x) == 1);

  x = 15;
  assert(odd_ones(x) == 0);

  /** dump_string tests */
  char str[8];
  str[0] = '\n';
  str[1] = '\t';
  str[2] = '\r';
  str[3] = '\b';
  str[4] = ' ';
  str[5] = 'H';
  str[6] = '!';
  str[7] = '\0';
  dump_string(str); 

  printf("All Cutilities tests passed!\n");
  return 0;
}
