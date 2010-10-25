# === global variables ===

OBJEXT = o
SOEXT = so

TARGETS = libezio.$(SOEXT) sample/test sample/server

TOPLEVEL_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

CXXFLAGS += -g -ggdb

OBJECTS =

# === conventional rules ===

all:

clean:
	$(RM) $(OBJECTS) $(TARGETS)

.PHONY: all clean

# === libezio.so ===

EZIO_SOURCES = \
			 ezio/Addrinfo \
			 ezio/Connection_Failure \
			 ezio/File \
			 ezio/Getaddrinfo_Exception \
			 ezio/Shared_Object \
			 ezio/Socket \
			 ezio/System_Exception \
			 ezio/TCP_Socket \
			 ezio/UDP_Socket \
			 ezio/Bind_Failure \
			 ezio/TCP_Server \
			 ezio/Reactor \
			 ezio/Libev_Reactor \
			 ezio/cxx_demangle \
			 ezio/Backtrace \
			 ezio/Exception \
			 ezio/Regex \
			 ezio/File_Event \
			 ezio/Runtime_Error \

EZIO_OBJS = $(addsuffix .$(OBJEXT), $(EZIO_SOURCES))
OBJECTS += $(EZIO_OBJS)

EZIO_LDFLAGS += -lev

libezio.$(SOEXT): $(EZIO_OBJS)
	$(CXX) $(EZIO_LDFLAGS) $(LDFLAGS) -shared $^ -o $@

TARGETS += libezio.$(SOEXT)

all: libezio.$(SOEXT)

# === sample rules ===

SAMPLE_CXXFLAGS += -I$(TOPLEVEL_DIR)
SAMPLE_LDFLAGS += -L$(TOPLEVEL_DIR) -lezio

sample/%.$(OBJEXT): sample/%.cpp
	$(CXX) $(CPPFLAGS) $(SAMPLE_CXXFLAGS) $(CXXFLAGS) -c $< -o $@

# === sample/test ===

sample/test: sample/test.$(OBJEXT)
	$(CXX) $(SAMPLE_LDFLAGS) $(LDFLAGS) $^ -o $@

OBJECTS += sample/test.$(OBJEXT)

TARGETS += sample/test

all: sample/test

# === sample/server ===

sample/server: sample/server.$(OBJEXT)
	$(CXX) $(SAMPLE_LDFLAGS) $(LDFLAGS) $^ -o $@

OBJECTS += sample/server.$(OBJEXT)

TARGETS += sample/server

all: sample/server

# === dependencies ===

CXXFLAGS += -MMD -MP
DEP_FILES = $(OBJECTS:%.$(OBJEXT)=%.d)
-include $(DEP_FILES)

