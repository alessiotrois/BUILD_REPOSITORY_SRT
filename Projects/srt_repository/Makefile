#############################################################################
# Makefile for building: standard_analysis
# Last modification: 2007-02-14 20:36 (Andrew Chen)
# Project:  standard_analysis
# Template: lib and exe
# Use make variable_name=' options ' to override the variables or make -e to
# override the file variables with the environment variables
# 		make CFLAGS='-g' or make prefix='/usr'
# Instructions:
# - modify the section 1)
# - if you want, modify the section 2) and 3), but it is not necessary
# - modify the variables of the section 4): CFLAGS INCPATH ALL_CFLAGS CPPFLAGS LIBS
# - in section 10), modify the following action:
#		* all: and or remove exe and lib prerequisite
#		* lib: and or remove staticlib and dynamiclib prerequisite
#		* clean: add or remove the files and directories that should be cleaned
#		* install: add or remove the files and directories that should be installed
#		* uninstall: add or remove the files and directories that should be uninstalled
#############################################################################

SHELL = /bin/sh

####### 1) Project names and system

#SYSTEM: linux or QNX
SYSTEM = linux
PROJECT=std_loggen
EXE_NAME1 = srt_repository_insert
EXE_NAME2 = srt_repository_insert_psr

LIB_NAME =
VER_FILE_NAME = version.h

####### 2) Directories for the installation

# Prefix for each installed program. Only ABSOLUTE PATH


exec_prefix=$(prefix)
# The directory to install the binary files in.
bindir=$(exec_prefix)/bin
# The directory to install the local configuration file.


####### 3) Directories for the compiler
BIN_DIR = bin
OBJECTS_DIR = obj
SOURCE_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
DOC_DIR = doc
UT_DIR = ut
CONF_DIR = conf
DOXY_SOURCE_DIR = code_filtered
EXE_DESTDIR  = $(BIN_DIR)
LIB_DESTDIR = lib
DATA_DIR = data


####### 4) Compiler, tools and options

CC       = gcc
CXX      = g++
#Insert the optional parameter to the compiler. The CFLAGS could be changed externally by the user
CFLAGS   = -Wall

#Set INCPATH to add the inclusion paths
# INCPATH = -I ./include -I$(AGILE_LIBWCS_INCLUDE) -I$(AGILE_LIBPIL_INCLUDE) -I$(AGILE_CFITSIO_INCLUDE)
# LIBPATH = -L$(AGILE_LIBWCS_LIB)  -L$(AGILE_LIBPIL_LIB) -L$(AGILE_CFITSIO_LIB)




INCPATH =  -I../cfitsio_lib/ -I./include
LIBPATH =  -L../cfitsio_lib/

#Insert the implicit parameter to the compiler:
ALL_CFLAGS =  $(INCPATH) $(LIBPATH) $(CFLAGS)

ifeq ($(SYSTEM), QNX)
	ALL_CFLAGS += -Vgcc_ntox86_gpp -lang-c++
endif
#Use CPPFLAGS for the preprocessor
CPPFLAGS =
#Set LIBS for addition library
# LIBS =  -lcfitsio  -L. -lm -lnsl -lpil
LIBS =  -L. -lm -lnsl  -lcfitsio -lmysqlcppconn


ifeq ($(SYSTEM), QNX)
	LIBS += -lsocket
endif
LINK     = g++
#for link
LFLAGS = -shared -Wl,-soname,$(TARGET1) -Wl,-rpath,$(DESTDIR)
AR       = ar cqs
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f -r
COPY_FILE= $(COPY) -p
COPY_DIR = $(COPY) -pR
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rm -rf
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p


####### 5) VPATH

VPATH=$(SOURCE_DIR):$(INCLUDE_DIR):
vpath %.o $(OBJECTS_DIR)

####### 6) Files of the project

INCLUDE=$(foreach dir,$(INCLUDE_DIR), $(wildcard $(dir)/*.h))
SOURCE=$(foreach dir,$(SOURCE_DIR), $(wildcard $(dir)/*.cpp))
SOURCE+=$(foreach dir,$(SOURCE_DIR), $(wildcard $(dir)/*.c))
#Objects to build
OBJECTS=$(addsuffix .o, $(basename $(notdir $(SOURCE))))
#only for documentation generation
DOC_INCLUDE= $(addprefix $(DOXY_SOURCE_DIR)/, $(notdir $(INCLUDE)))
DOC_SOURCE= $(addprefix $(DOXY_SOURCE_DIR)/, $(notdir $(SOURCE)))

####### 9) Pattern rules

%.o : %.cpp
	$(CXX) -Wno-write-strings $(ALL_CFLAGS) -c $< -o $(OBJECTS_DIR)/$@

#only for documentation generation
$(DOXY_SOURCE_DIR)/%.h : %.h
	doxyfilter < $< > $@

$(DOXY_SOURCE_DIR)/%.cpp : %.cpp
	doxyfilter < $< > $@


all: exe 
	
exe: makeobjdir makebindir $(OBJECTS)	
# 		test -d $(EXE_DESTDIR) || mkdir -p $(EXE_DESTDIR)
		$(CXX)  -Wno-write-strings $(ALL_CFLAGS) -o $(EXE_DESTDIR)/$(EXE_NAME1) $(OBJECTS_DIR)/$(EXE_NAME1).o $(LIBS)
		$(CXX)  -Wno-write-strings $(ALL_CFLAGS) -o $(EXE_DESTDIR)/$(EXE_NAME2) $(OBJECTS_DIR)/$(EXE_NAME2).o $(LIBS)		
		
# 		$(CXX)  $(ALL_CFLAGS) -o $(EXE_DESTDIR)/$(EXE_NAME2) $(OBJECTS_DIR)/$(EXE_NAME2).o $(LIBS)

makeobjdir:
	test -d $(OBJECTS_DIR) || mkdir -p $(OBJECTS_DIR)	
	
makebindir:
	test -d $(BIN_DIR) || mkdir -p $(BIN_DIR)

#clean: delete all files from the current directory that are normally created by building the program. 
clean:

	$(DEL_DIR) $(OBJECTS_DIR)
	$(DEL_DIR) $(BIN_DIR)		

#Delete all files from the current directory that are created by configuring or building the program. 
distclean: clean

#install: compile the program and copy the executables, libraries, 
#and so on to the file names where they should reside for actual use. 


#uninstall: delete all the installed files--the copies that the `install' target creates. 
uninstall:
#dist: create a distribution tar file for this program


dist: all


#info: generate any Info files needed.
info:
	test -d $(infodir) || mkdir -p $(infodir)
	$(COPY_DIR) $(DOC_DIR)/*.* $(infodir)


install: all
# For exe installation
	test -d $(bindir) || mkdir -p $(bindir)	

	cp  $(BIN_DIR)/* ~/bin

	



