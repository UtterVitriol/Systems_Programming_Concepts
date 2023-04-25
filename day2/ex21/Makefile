FILES = Makefile \
        mmu.h \
        checker21 \
        libsolution.so

ex21.tar.gz: $(FILES)
	tar czf $@ $^

checker21: checker21.c mmu.h
	$(CC) -o $@ -g -O1 -fno-omit-frame-pointer -fno-inline -Wall -Werror $^ -ldl

libsolution.so: solution.c solution.h mmu.h
	$(CC) -o $@ -fpic -shared $^

.PHONY: clean

clean:
	rm -f checker21
	rm -f *.so
	rm -f *.tar.gz
