TEST_OBJS = \
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

test: $(TEST_OBJS) test.o
	g++ $(LDFLAGS) $^ -o $@

