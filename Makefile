SHELL = /bin/sh

####### 0) Common definition
# DISCOS Type is the different type of DISCoS operating mode
# EGSE_DISCOS is for the DISCoS at EGSE level
DISCOS_TYPE = EGSE_DISCOS
# EGSE_TE is for the DISCoS at TE level
#DISCOS_TYPE = TE_DISCOS
####### 1) Directories for the installation

# Prefix for each installed program. Only ABSOLUTE PATH
prefix=$(PWD)
exec_prefix=$(prefix)
# The directory to install the binary files in.
bindir=$(exec_prefix)/bin
# The directory to install the local configuration file.
datadir=$(exec_prefix)/share
# The directory to install the libraries in.
libdir=$(exec_prefix)/lib
# The directory to install the info files in.
infodir=$(exec_prefix)/info
# The directory to install the include files in.
includedir=$(exec_prefix)/include

####### 2) Directories
PRJ_DIR=Projects

INSTALL_SUBDIR=

export LIBPIL_INCLUDE=$(PWD)/Projects/pil_lib/include 
export LIBPIL_LIB=$(PWD)/Projects/pil_lib/lib 
export CFITSIO_INCLUDE=$(PWD)/Projects/cfitsio_lib/
export CFITSIO_LIB=$(PWD)/Projects/cfitsio_lib/
export CFITSIOLIB=$(PWD)/Projects/cfitsio_lib/libcfitsio.a 

####### 3) Compiler, tools and options

#Insert the optional parameter to the compiler. The CFLAGS could be changed externally by the user
CFLAGS   =
AR       = ar cqs
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY) -p
COPY_DIR = $(COPY) -pR
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rm -rf
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p
CVS = cvs -d${CVSROOT} checkout

BUILD = -r BUILD00_STD
#BUILD =

####### 4) Build rules
all:
	cd ./$(PRJ_DIR)/cfitsio_lib	        &&	./configure	 --enable-ssse3
	cd ./$(PRJ_DIR)/cfitsio_lib	        &&	$(MAKE) CFLAGS=$(CFLAGS) prefix=$(prefix) 
	cd ./$(PRJ_DIR)/srt_repository	&&	$(MAKE) CFLAGS=$(CFLAGS) prefix=$(prefix) install


	
exe:

	cd ./$(PRJ_DIR)/cfitsio_lib	        &&	./configure	 --enable-ssse3	
	cd ./$(PRJ_DIR)/cfitsio_lib        	&&	$(MAKE) CFLAGS=$(CFLAGS) prefix=$(prefix) all
	cd ./$(PRJ_DIR)/srt_repository	&&	$(MAKE) CFLAGS=$(CFLAGS) prefix=$(prefix) exe

#clean: delete all files from the current directory that are normally created by building the program.
clean:
	cd ./$(PRJ_DIR)/cfitsio_lib	        &&	$(MAKE) CFLAGS=$(CFLAGS) prefix=$(prefix) clean
	cd ./$(PRJ_DIR)/srt_repository	&&	$(MAKE) CFLAGS=$(CFLAGS) prefix=$(prefix) clean
nstall: compile the program and copy the executables, libraries,
#and so on to the file names where they should reside for actual use.
install: 
	chmod 777 ./$(PRJ_DIR)/cfitsio_lib/configure
	cd ./$(PRJ_DIR)/cfitsio_lib	        &&	./configure	 --enable-ssse3
	cd ./$(PRJ_DIR)/cfitsio_lib	        &&	$(MAKE) CFLAGS=$(CFLAGS) prefix=$(prefix) 
	cd ./$(PRJ_DIR)/srt_repository	&&	$(MAKE) CFLAGS=$(CFLAGS) prefix=$(prefix) install


