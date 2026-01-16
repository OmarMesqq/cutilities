# 1. Detect the Operating System
UNAME_S := $(shell uname -s)

# 2. Set defaults (Linux)
# On Linux, we use -shared and usually set the soname (optional but good practice)
SHARED_FLAGS := -shared -Wl,-soname,libcutilities.so

# 3. macOS Overrides
ifeq ($(UNAME_S),Darwin)
  # macOS needs -install_name for @rpath support
  SHARED_FLAGS := -shared -install_name @rpath/libcutilities.so
endif

release:
	gcc -c -fPIC cutilities.c -o cutilities.o
	gcc $(SHARED_FLAGS) -o libcutilities.so cutilities.o
