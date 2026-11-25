# Single line comment

# Target: provide all dependency object files (.o)
mypreprocessor: main.o comment_removal.o file_inclusion.o macro_handler.o
	cc main.o comment_removal.o file_inclusion.o macro_handler.o -o mypreprocessor

# Individual object file dependencies

main.o: main.c comment_removal.h file_inclusion.h macro_handler.h
	cc -c main.c

comment_removal.o: comment_removal.c comment_removal.h
	cc -c comment_removal.c

file_inclusion.o: file_inclusion.c file_inclusion.h
	cc -c file_inclusion.c

macro_handler.o: macro_handler.c macro_handler.h
	cc -c macro_handler.c

# To remove object files
clean:
	@echo "Cleaning up..."
	@rm -f *.o mypreprocessor
