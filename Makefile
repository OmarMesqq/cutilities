release:
	gcc -c -fPIC cutilities.c -o cutilities.o
	gcc -shared -install_name @rpath/libcutilities.so -o libcutilities.so cutilities.o
