FILES = Makefile \
        ex12.h \
        checker12.c

ex12.tar.gz: $(FILES)
	tar czf $@ $^

checker12: solution.so
checker12: checker12.c
	$(CC) -o $@ -g -O1 -fno-omit-frame-pointer -fno-inline -Wall -Werror $^ -ldl

solution%.so: solution%.S
	$(CC) -o $@ -fpic -shared $^

.PHONY: clean

clean:
	rm -f checker12
	rm -f *.so
	rm -f *.tar.gz
