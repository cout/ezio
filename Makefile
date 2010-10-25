# === global variables ===

TOPLEVEL_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

OBJEXT = o
SOEXT = so

OBJECTS =
TARGETS =

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
	$(call link_so, $(EZIO_LDFLAGS))

TARGETS += libezio.$(SOEXT)

all: libezio.$(SOEXT)

# === sample rules ===

SAMPLE_CXXFLAGS += -I$(TOPLEVEL_DIR)
SAMPLE_LDFLAGS += -L$(TOPLEVEL_DIR) -lezio

sample/%.$(OBJEXT): sample/%.cpp
	$(call compile_cpp, $(SAMPLE_CXXFLAGS))

# === sample/test ===

sample/test: sample/test.$(OBJEXT)
	$(call link_bin, $(SAMPLE_LDFLAGS))

OBJECTS += sample/test.$(OBJEXT)

TARGETS += sample/test

all: sample/test

# === sample/server ===

sample/server: sample/server.$(OBJEXT)
	$(call link_bin, $(SAMPLE_LDFLAGS))

OBJECTS += sample/server.$(OBJEXT)

TARGETS += sample/server

all: sample/server

# === dependencies ===

CXXFLAGS += -MMD -MP
DEP_FILES = $(OBJECTS:%.$(OBJEXT)=%.d)
-include $(DEP_FILES)

