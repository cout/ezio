EZIO_OBJS = \
			 ezio/Addrinfo.o \
			 ezio/Connection_Failure.o \
			 ezio/File.o \
			 ezio/Getaddrinfo_Exception.o \
			 ezio/Runtime_Error.o \
			 ezio/Shared_Object.o \
			 ezio/Socket.o \
			 ezio/System_Exception.o \
			 ezio/TCP_Socket.o \
			 ezio/UDP_Socket.o \
			 ezio/Bind_Failure.o \
			 ezio/TCP_Server.o \
			 ezio/Reactor.o \
			 ezio/Libev_Reactor.o \
			 ezio/cxx_demangle.o \
			 ezio/Backtrace.o \
			 ezio/Exception.o \
			 ezio/Regex.o \

LDFLAGS += -lev

all: test server

test: $(EZIO_OBJS) test.o
	g++ $(LDFLAGS) $^ -o $@

server: $(EZIO_OBJS) server.o
	g++ $(LDFLAGS) $^ -o $@

