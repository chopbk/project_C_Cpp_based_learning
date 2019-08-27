SOURCE_FILE=sqlite.c
OBJECT_FILE=sqlite.o
OUTPUT=build/sqlite
sqlite: $(OBJECT_FILE)
	gcc -o $(OUTPUT) $(OBJECT_FILE)
$(OBJECT_FILE): $(SOURCE_FILE)
	gcc -c $(SOURCE_FILE)
clean:
	rm -rf $(OUTPUT) $(OBJECT_FILE)