OBJEXT = o

TARGETS = sample/test sample/server

TOPLEVEL_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

all: $(TARGETS)

clean:
	$(RM) $(GENERATED_FILES) $(TARGETS)

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
GENERATED_FILES += $(EZIO_OBJS)

CXXFLAGS += -g -ggdb

LDFLAGS += -lev

CXXFLAGS += -MMD -MP
EZIO_DEP_FILES=$(EZIO_OBJS:%.$(OBJEXT)=%.d)
-include $(EZIO_DEP_FILES)

SAMPLE_CXXFLAGS += -I$(TOPLEVEL_DIR)

sample/%.$(OBJEXT): sample/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SAMPLE_CXXFLAGS) -c $^ -o $@

sample/test: $(EZIO_OBJS) sample/test.$(OBJEXT)
	$(CXX) $(SAMPLE_CXXFLAGS) $(LDFLAGS) $^ -o $@

sample/server: $(EZIO_OBJS) sample/server.$(OBJEXT)
	$(CXX) $(SAMPLE_CXXFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: all clean

