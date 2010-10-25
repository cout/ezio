OBJEXT = o

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

all: test server

clean:
	$(RM) $(EZIO_OBJS) test server

EZIO_OBJS = $(addsuffix .$(OBJEXT), $(EZIO_SOURCES))

CXXFLAGS += -g -ggdb

LDFLAGS += -lev

CXXFLAGS += -MMD -MP
EZIO_DEP_FILES=$(EZIO_OBJS:%.$(OBJEXT)=%.d)
-include $(EZIO_DEP_FILES)

test: $(EZIO_OBJS) test.$(OBJEXT)
	$(CXX) $(LDFLAGS) $^ -o $@

server: $(EZIO_OBJS) server.$(OBJEXT)
	$(CXX) $(LDFLAGS) $^ -o $@

.PHONY: all clean

