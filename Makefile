release:
	gcc -c -fPIC cutilities.c -o cutilities.o
	gcc -shared -o libcutilities.so cutilities.o
