FILES = Makefile \
        checker13.c

ex13.tar.gz: $(FILES)
	tar czf $@ $^

checker13: checker13.c
	$(CC) -o $@ -g -O1 -fno-omit-frame-pointer -fno-inline -Wall -Werror $^ -ldl

libsolution%.so: solution%.S
	$(CC) -o $@ -nostdlib -fpic -shared $^

.PHONY: clean

clean:
	rm -f checker13
	rm -f *.so
	rm -f *.tar.gz
