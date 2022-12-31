
INCDIR := include
SRCDIR := src
BUILDDIR := build
BINDIR := bin
TESTDIR := test
TESTBIN := testbin
CXX := g++
CXXFLAGS :=	-c \
			-g \


#############
## Testing ##
#############
# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR=../../../../GitHub/googletest/googletest

# Where to find user code.
USER_DIR=.

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -Wall -Wextra -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = StringUtilsTest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)


ifeq ($(OS),Windows_NT)
	IS_WIN := 1
endif

.PHONY: all
all: 	dirs \
		LSM6DSOX\

force: 	clean \
		all\

test: 	dirs \
		$(TESTS)


.PHONY: dirs
dirs:
ifeq ($(IS_WIN),1)
	if not exist $(BINDIR) mkdir $(BINDIR)
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	if not exist $(TESTBIN) mkdir $(TESTBIN)
else
	mkdir -p $(BINDIR)
	mkdir -p $(BUILDDIR)
	mkdir -p $(TESTBIN)
endif

LSM6DSOX: dirs LSM6DSOX.o I2CDevice.o I2CBus.o AccelData.o GyroData.o
	$(CXX) -o $(BINDIR)/LSM6DSOX $(BUILDDIR)/LSM6DSOX.o $(BUILDDIR)/I2CDevice.o $(BUILDDIR)/I2CBus.o -li2c

LSM6DSOX.o: dirs $(SRCDIR)/LSM6DSOX.cpp
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)/LSM6DSOX.o $(SRCDIR)/LSM6DSOX.cpp


AccelData.o: dirs $(SRCDIR)/AccelData.cpp
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)/AccelData.o $(SRCDIR)/AccelData.cpp

GyroData.o: dirs $(SRCDIR)/GyroData.cpp
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)/GyroData.o $(SRCDIR)/GyroData.cpp

I2CDevice.o: dirs $(SRCDIR)/I2CDevice.cpp
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)/I2CDevice.o $(SRCDIR)/I2CDevice.cpp

I2CBus.o: dirs $(SRCDIR)/I2CBus.cpp
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)/I2CBus.o $(SRCDIR)/I2CBus.cpp

TestFile: dirs TestFile.o
	$(CXX) -o $(BINDIR)/TestFile $(BUILDDIR)/TestFile.o

TestFile.o: dirs $(SRCDIR)/TestFile.cpp
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)/TestFile.o $(SRCDIR)/TestFile.cpp


# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.

StringUtilsTest: StringUtilsTest.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
StringUtilsTest.o : $(TESTDIR)/StringUtilsTest.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $(TESTBIN)/StringUtilsTest.o -c $(TESTDIR)/StringUtilsTest.cpp

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^



.PHONY: clean
clean : 
	rm -fr $(BUILDDIR) $(BINDIR) $(TESTBIN)

