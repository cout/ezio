OBJEXT = o

TARGETS = test server

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

test: $(EZIO_OBJS) test.$(OBJEXT)
	$(CXX) $(LDFLAGS) $^ -o $@

server: $(EZIO_OBJS) server.$(OBJEXT)
	$(CXX) $(LDFLAGS) $^ -o $@

.PHONY: all clean

