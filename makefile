objects = libjson.o libjson_qual.o libjson_write.o libjson_read.o libjson_print.o libjson_free.o libjson_array.o libjson_parse.o libjson_memory.o
objects_messaging = messaging.o libjson.o libjson_qual.o libjson_write.o libjson_read.o libjson_print.o libjson_free.o libjson_array.o libjson_parse.o libjson_memory.o
objects_msgscript = msg_script.o libjson.o libjson_qual.o libjson_write.o libjson_read.o libjson_print.o libjson_free.o libjson_array.o libjson_parse.o libjson_memory.o
app_objects = libjson_app.o libjson_qual.o libjson_write.o libjson_read.o libjson_print.o libjson_free.o libjson_array.o libjson_parse.o libjson_memory.o


all: jsqlib.a jsqlib_app

messaging: $(objects_messaging)
	gcc -o messaging  $(objects_messaging)

msg_script: $(objects_msgscript)
	gcc -o msg_script  $(objects_msgscript)

jsqlib.a: $(objects)
	ar -r -o jsqlib.a $(objects)

jsqlib_app: $(app_objects)
	gcc -o jsqlib_app $(objects)

libjson.o: libjson.c libjson.h libjson_qual.h libjson_write.h libjson_read.h
	gcc -D WITH_MAIN=0 -c libjson.c

libjson_app.o: libjson.c libjson.h libjson_qual.h libjson_write.h libjson_read.h
	gcc -D WITH_MAIN=1 -c libjson.c

libjson_qual.o: libjson_qual.c libjson_qual.h libjson.h
	gcc -c libjson_qual.c

libjson_write.o: libjson_write.c libjson_write.h libjson_read.h libjson.h
	gcc -c libjson_write.c

libjson_read.o: libjson_read.c libjson_read.h libjson.h
	gcc -c libjson_read.c

libjson_array.o: libjson_array.c libjson_array.h libjson.h
	gcc -c libjson_array.c

libjson_print.o: libjson_print.c libjson_print.h libjson.h
	gcc -c libjson_print.c

libjson_free.o: libjson_free.c libjson_free.h libjson.h
	gcc -c libjson_free.c

libjson_parse.o: libjson_parse.c libjson_parse.h libjson.h
	gcc -c libjson_parse.c

libjson_memory.o: libjson_memory.c libjson_memory.h libjson.h
	gcc -c libjson_memory.c

messaging.o: messaging.c libjson.h
	gcc -c messaging.c

msg_script.o: msg_script.c libjson.h
	gcc -c msg_script.c

clean:
	rm $(objects)


