export CC = g++
INCPATH = -I$(CURDIR)/include
LIBS = 
#-lpthread 
export DEFINES = 
export FLAGS = -std=c++0x -o3 $(INCPATH) $(LIBS) $(DEFINES)
export TOP = $(CURDIR)
export OBJ_DIR = $(TOP)/obj

export LIB = libmonitoring
export STATIC = $(LIB).a
export SHARED = $(LIB).so

SRC = $(wildcard *.c*)
OBJ = $(SRC:.cpp=.o) $(SRC:*.cpp=.o)

SUBDIRS = src obj

export EXEC = monitoring-test


CLEANDIRS = $(SUBDIRS:%=clean-%)

.PHONY: subdirs $(SUBDIRS)
.PHONY: subdirs $(CLEANDIRS)


static : src
	$(MAKE) static -C obj

shared :
	$(MAKE) -C src FLAGS="$(FLAGS) -fPIC"
	$(MAKE) shared -C obj

install :
	cp -f $(STATIC) /usr/local/lib/$(STATIC)
	cp -f $(SHARED) /usr/local/lib/$(SHARED)
	cp -rf include/Monitoring /usr/local/include/Monitoring

uninstall:
	rm -f /usr/local/lib/$(STATIC)
	rm -f /usr/local/lib/$(SHARED)
	rm -rf /usr/local/include/Monitoring

all: $(OBJ) subdirs
	$(MAKE) -C $@


doc : doc/html 

doc/html :
	cd doc && doxygen

subdirs: $(SUBDIRS)
     
$(SUBDIRS):
	$(MAKE) all -C $@


.cpp.o:
	$(CC) $(FLAGS) -o $@ -c $^;
	@mv $@ "$(OBJ_DIR)"

.c.o :
	$(CC) $(FLAGS) -o $@ -c $^;
	@mv $@ "$(OBJ_DIR)"


clean: $(CLEANDIRS)

$(CLEANDIRS): 
	$(MAKE) -C $(@:clean-%=%) clean
	@rm -f *.o
	@rm -f $(EXEC)
