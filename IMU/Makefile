
INCDIR := include
SRCDIR := src
BUILDDIR := build
BINDIR := bin
GLOBPATH := /home/greensight/nasa_adesssa/cycle_compress/CVersion
CXX := gcc
CFLAGS :=	-c \
			-g \
			-fPIC 

ifeq ($(OS),Windows_NT)
	IS_WIN := 1
endif

.PHONY: all
all: 	dirs \
		ZipCycles \
		ZipSamples.so

force: 	clean \
		dirs \
		ZipCycles \
		ZipSamples.so

test: 	clean \
		dirs \
		ZipSamplesTest


.PHONY: dirs
dirs:
ifeq ($(IS_WIN),1)
	if not exist $(BINDIR) mkdir $(BINDIR)
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
else
	mkdir -p $(BINDIR)
	mkdir -p $(BUILDDIR)
endif


ZipSamplesTest: dirs ZipSamples.o FileZip.o
	$(CXX) -o $(BINDIR)/ZipSamplesTest $(BUILDDIR)/ZipSamples.o $(BUILDDIR)/FileZip.o

ZipSamples.o: dirs $(SRCDIR)/ZipSamples.c
	$(CXX) $(CFLAGS) -o $(BUILDDIR)/ZipSamples.o $(SRCDIR)/ZipSamples.c 


FileZip.o: dirs $(SRCDIR)/FileZip.c
	$(CXX) $(CFLAGS) -o $(BUILDDIR)/FileZip.o $(SRCDIR)/FileZip.c 

.PHONY: clean
clean : 
	rm -fr $(BUILDDIR) $(BINDIR)

