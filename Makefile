LIB_OBJECT_FILE := cutilities.o
SHARED_LIBRARY_FILE := libcutilities.so
TEST_SOURCE_FILEPATH := test/test_main.c
TEST_BINARY := test_runner
LIB_PATH := $(shell pwd)
INCLUDES := -I$(LIB_PATH)
LDFLAGS  := -L$(LIB_PATH) -lcutilities -Wl,-rpath,$(LIB_PATH)

# Detect the Operating System
UNAME_S := $(shell uname -s)

# Default to Linux
SHARED_FLAGS := -shared -Wl,-soname,$(SHARED_LIBRARY_FILE)

# Overrides for macOS: it needs -install_name for @rpath support
ifeq ($(UNAME_S),Darwin)
  SHARED_FLAGS := -shared -install_name @rpath/$(SHARED_LIBRARY_FILE)
endif

release:
	gcc -c -fPIC cutilities.c -o $(LIB_OBJECT_FILE)
	gcc $(SHARED_FLAGS) -o $(SHARED_LIBRARY_FILE) $(LIB_OBJECT_FILE)


test: release
	gcc -g -O3 -Wall -Wextra -Winline $(TEST_SOURCE_FILEPATH) $(INCLUDES) $(LDFLAGS) -o $(TEST_BINARY)

#TODO: leaks test

clean:
	rm -f $(LIB_OBJECT_FILE) $(SHARED_LIBRARY_FILE)
