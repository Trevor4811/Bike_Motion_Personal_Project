
INCDIR := include
SRCDIR := src
BUILDDIR := build
BINDIR := bin
GLOBPATH := /home/greensight/nasa_adesssa/cycle_compress/CVersion
CXX := g++
CFLAGS :=	-c \
			-g \

ifeq ($(OS),Windows_NT)
	IS_WIN := 1
endif

.PHONY: all
all: 	dirs \
		I2CDevice\

force: 	clean \
		all\

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

I2CDevice: dirs I2CDevice.o I2CBus.o
	$(CXX) -o $(BINDIR)/I2CDevice $(BUILDDIR)/I2CDevice.o -li2c

I2CDevice.o: dirs $(SRCDIR)/I2CDevice.cpp
	$(CXX) $(CFLAGS) -o $(BUILDDIR)/I2CDevice.o $(SRCDIR)/I2CDevice.cpp


I2CBus: dirs I2CBus.o
	$(CXX) -o $(BINDIR)/I2CBus $(BUILDDIR)/I2CBus.o

I2CBus.o: dirs $(SRCDIR)/I2CBus.cpp
	$(CXX) $(CFLAGS) -o $(BUILDDIR)/I2CBus.o $(SRCDIR)/I2CBus.cpp

.PHONY: clean
clean : 
	rm -fr $(BUILDDIR) $(BINDIR)

