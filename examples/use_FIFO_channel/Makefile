SYSTEMC_ARCH=linux64
LIB_DIRS=$(SYSTEMC_HOME)/lib-$(SYSTEMC_ARCH)

# Include directories
INCLUDE_DIRS = -I. -I$(SYSTEMC_HOME)/include 

# header files used. for dependency checking
HEADERS = $(shell find . -iname "*.h")

# source files used. for dependency checking
SOURCES = $(shell find . -iname "*.cc")

DEPENDENCIES = \
	Makefile \
	$(HEADERS) \
	$(SOURCES)

LIBS= -lsystemc -lstdc++ -lm

BIN= main

run: $(BIN)
	./$(BIN)

$(BIN): $(DEPENDENCIES)
	gcc -o $@ $(SOURCES) $(INCLUDE_DIRS) -L. -L$(LIB_DIRS) $(LIBS) -Wl,-rpath=$(LIB_DIRS)

clean:
	rm -f $(BIN) 

.PHONY: clean
