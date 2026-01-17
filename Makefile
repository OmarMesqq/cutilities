SRC := cutilities.c
LIB_OBJECT_FILE := cutilities.o
SHARED_LIBRARY_FILE := libcutilities.so

TEST_SRC := test/test_main.c
TEST_BINARY := test_runner
LIB_PATH := $(shell pwd)
TEST_INCLUDES := -I$(LIB_PATH)
TEST_LDFLAGS  := -L$(LIB_PATH) -lcutilities -Wl,-rpath,$(LIB_PATH)

WARNINGS := -Wall -Wextra -Winline -pedantic
RELEASE_FLAGS := -O3
DEBUG_FLAGS := -O0 -g

# Detect the Operating System
UNAME_S := $(shell uname -s)

# Default to Linux
SHARED_FLAGS := -shared -Wl,-soname,$(SHARED_LIBRARY_FILE)
VALGRIND_FLAGS := -s --leak-check=full --track-origins=yes --show-leak-kinds=all
LEAKS_CMD := valgrind $(VALGRIND_FLAGS) ./$(TEST_BINARY)

# Override some flags on macOS
ifeq ($(UNAME_S),Darwin)
  SHARED_FLAGS := -shared -install_name @rpath/$(SHARED_LIBRARY_FILE)
	LEAKS_CMD := MallocNanoZone=0 leaks --atExit -- ./$(TEST_BINARY)
endif

release:
	gcc $(WARNINGS) $(RELEASE_FLAGS) -c -fPIC $(SRC) -o $(LIB_OBJECT_FILE)
	gcc $(WARNINGS) $(RELEASE_FLAGS) $(SHARED_FLAGS) -o $(SHARED_LIBRARY_FILE) $(LIB_OBJECT_FILE)

debug:
	gcc $(WARNINGS) $(DEBUG_FLAGS) -c -fPIC $(SRC) -o $(LIB_OBJECT_FILE)
	gcc $(WARNINGS) $(DEBUG_FLAGS) $(SHARED_FLAGS) -o $(SHARED_LIBRARY_FILE) $(LIB_OBJECT_FILE)

test: debug
	gcc $(WARNINGS) $(DEBUG_FLAGS) $(TEST_SRC) $(TEST_INCLUDES) $(TEST_LDFLAGS) -o $(TEST_BINARY)
	./$(TEST_BINARY)

leaks: test
	$(LEAKS_CMD)

clean:
	rm -rf $(LIB_OBJECT_FILE) $(SHARED_LIBRARY_FILE) $(TEST_BINARY) $(TEST_BINARY).dSYM
