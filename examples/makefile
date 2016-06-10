# CN_Vec examples makefile
# For more information on this library, please visit the following URL:
# http://web.eecs.utk.edu/~ssmit285/lib/cn_vec/index.html

# Specify Variables
CC        = gcc
CFLAGS    = --std=gnu89
SRC_PATH  = .
LIB_PATH  = ..
LIB_FILES = $(LIB_PATH)/cn_vec.c

SOURCE    = $(wildcard $(SRC_PATH)/*.c)
EXE       = $(patsubst $(SRC_PATH)/%.c, $(SRC_PATH)/%, $(SOURCE))

#Perform awesomeness
all: $(EXE)
	@echo "Compiled successfully."
%:
ifeq ($<, )
	$(CC) $(CFLAGS) -o $@ $@.c $(LIB_FILES)
endif

clean:
	rm -f $(EXE)
