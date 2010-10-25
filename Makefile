OBJEXT = o
SOEXT = so

TARGETS = libezio.$(SOEXT) sample/test sample/server

TOPLEVEL_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

all: $(TARGETS)

clean:
	$(RM) $(OBJECTS) $(TARGETS)

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

CXXFLAGS += -g -ggdb

EZIO_LDFLAGS += -lev

CXXFLAGS += -MMD -MP
EZIO_DEP_FILES=$(EZIO_OBJS:%.$(OBJEXT)=%.d)
-include $(EZIO_DEP_FILES)

SAMPLE_CXXFLAGS += -I$(TOPLEVEL_DIR)
SAMPLE_LDFLAGS += -L$(TOPLEVEL_DIR) -lezio

libezio.$(SOEXT): $(EZIO_OBJS)
	$(CXX) $(EZIO_LDFLAGS) $(LDFLAGS) -shared $^ -o $@

sample/%.$(OBJEXT): sample/%.cpp
	$(CXX) $(CPPFLAGS) $(SAMPLE_CXXFLAGS) $(CXXFLAGS) -c $^ -o $@

sample/test: sample/test.$(OBJEXT)
	$(CXX) $(SAMPLE_LDFLAGS) $(LDFLAGS) $^ -o $@

OBJECTS += sample/test.$(OBJEXT)

sample/server: sample/server.$(OBJEXT)
	$(CXX) $(SAMPLE_LDFLAGS) $(LDFLAGS) $^ -o $@

OBJECTS += sample/server.$(OBJEXT)

.PHONY: all clean

