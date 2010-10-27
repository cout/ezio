# === global variables ===

TOPLEVEL_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

OBJEXT = o
SOEXT = so

OBJECTS =
TARGETS =

CXXFLAGS += -I$(TOPLEVEL_DIR)

CXXFLAGS += -g -ggdb

# === conventional rules ===

all:

clean:
	$(RM) $(OBJECTS) $(TARGETS)

.PHONY: all clean

# === target rules ===

link_so = $(CXX) $(1) $(LDFLAGS) -shared $^ -o $@
compile_cpp = $(CXX) $(CPPFLAGS) $(1) $(CXXFLAGS) -c $< -o $@
link_bin = $(CXX) $(1) $(LDFLAGS) $^ -o $@

# === libezio.so ===

EZIO_SOURCES = \
			 ezio/Addrinfo \
			 ezio/File \
			 ezio/Shared_Object \
			 ezio/Socket \
			 ezio/TCP_Socket \
			 ezio/UDP_Socket \
			 ezio/TCP_Server \
			 ezio/Reactor \
			 ezio/Libev_Reactor \
			 ezio/cxx_demangle \
			 ezio/Backtrace \
			 ezio/Regex \
			 ezio/File_Event \
			 ezio/exceptions/Exception \
			 ezio/exceptions/Runtime_Error \
			 ezio/exceptions/Connection_Failure \
			 ezio/exceptions/Getaddrinfo_Exception \
			 ezio/exceptions/System_Exception \
			 ezio/exceptions/Bind_Failure \
			 ezio/Time_Value \
			 ezio/PID \
			 ezio/File_Mode \
			 ezio/File_Offset \
			 ezio/Whence \

EZIO_OBJS = $(addsuffix .$(OBJEXT), $(EZIO_SOURCES))
OBJECTS += $(EZIO_OBJS)

EZIO_LDFLAGS += -lev

libezio.$(SOEXT): $(EZIO_OBJS)
	$(call link_so, $(EZIO_LDFLAGS))

TARGETS += libezio.$(SOEXT)

all: libezio.$(SOEXT)

# === sample rules ===

SAMPLE_LDFLAGS += -L$(TOPLEVEL_DIR) -lezio

sample/%.$(OBJEXT): sample/%.cpp
	$(call compile_cpp, $(SAMPLE_CXXFLAGS))

# === sample/test ===

sample/test: sample/test.$(OBJEXT) libezio.so
	$(call link_bin, $(SAMPLE_LDFLAGS))

OBJECTS += sample/test.$(OBJEXT)

TARGETS += sample/test

all: sample/test

# === sample/server ===

sample/server: sample/server.$(OBJEXT) libezio.so
	$(call link_bin, $(SAMPLE_LDFLAGS))

OBJECTS += sample/server.$(OBJEXT)

TARGETS += sample/server

all: sample/server

# === dependencies ===

CXXFLAGS += -MMD -MP
DEP_FILES = $(OBJECTS:%.$(OBJEXT)=%.d)
-include $(DEP_FILES)

