CC=gcc
ODIR = gen
IDIR = include

lib_objects = libjson.o libjson_qual.o libjson_write.o libjson_read.o libjson_print.o libjson_free.o libjson_array.o libjson_parse.o libjson_memory.o
headers = libjson.h libjson_qual.h libjson_write.h libjson_read.h libjson_free.h libjson_array.h libjson_memory.h libjson_parse.h libjson_print.h

LIB_OBJECTS = $(patsubst %,$(ODIR)/%,$(lib_objects))
HEADERS = $(patsubst %,$(IDIR)/%,$(headers))

all: jsqlib.a jsqlib_app

jsqlib.a: $(LIB_OBJECTS)
	ar -r -o $(ODIR)/jsqlib.a $(LIB_OBJECTS)

jsqlib_app: $(ODIR)/jsqlib_app.o $(LIB_OBJECTS)
	$(CC) -o $(ODIR)/jsqlib_app $(ODIR)/jsqlib_app.o $(LIB_OBJECTS)

$(ODIR)/%.o: %.c $(headers)
	$(CC) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf $(ODIR)/*
