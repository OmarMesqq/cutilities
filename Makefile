LIB_OBJECT_FILE := cutilities.o
SHARED_LIBRARY_FILE := libcutilities.so
TEST_SOURCE_FILEPATH := test/test_main.c
TEST_BINARY := test_runner
LIB_PATH := $(shell pwd)
INCLUDES := -I$(LIB_PATH)
LDFLAGS  := -L$(LIB_PATH) -lcutilities -Wl,-rpath,$(LIB_PATH)
WARNINGS := -Wall -Wextra -Winline -pedantic
DEBUG_FLAGS := -O0 -g -fsanitize=address

# Detect the Operating System
UNAME_S := $(shell uname -s)

# Default to Linux
SHARED_FLAGS := -shared -Wl,-soname,$(SHARED_LIBRARY_FILE)
LEAKS_CMD := ./$(TEST_BINARY)

# Override some flags on macOS
ifeq ($(UNAME_S),Darwin)
  SHARED_FLAGS := -shared -install_name @rpath/$(SHARED_LIBRARY_FILE)
	LEAKS_CMD := MallocStackLogging=1 leaks --atExit -- ./$(TEST_BINARY)
endif

release:
	gcc -O3 $(WARNINGS) -c -fPIC cutilities.c -o $(LIB_OBJECT_FILE)
	gcc -O3 $(SHARED_FLAGS) -o $(SHARED_LIBRARY_FILE) $(LIB_OBJECT_FILE)

debug:
	gcc $(DEBUG_FLAGS) $(WARNINGS) -c -fPIC cutilities.c -o $(LIB_OBJECT_FILE)
	gcc $(DEBUG_FLAGS) $(SHARED_FLAGS) -o $(SHARED_LIBRARY_FILE) $(LIB_OBJECT_FILE)

test: debug
	gcc $(DEBUG_FLAGS) $(WARNINGS) $(TEST_SOURCE_FILEPATH) $(INCLUDES) $(LDFLAGS) -o $(TEST_BINARY)

leaks: test
	$(LEAKS_CMD)

clean:
	rm -rf $(LIB_OBJECT_FILE) $(SHARED_LIBRARY_FILE) $(TEST_BINARY) $(TEST_BINARY).dSYM
