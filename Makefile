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

link_so = $(CXX) -shared $(1) $(LDFLAGS) $^ -o $@
compile_cpp = $(CXX) $(CPPFLAGS) $(1) $(CXXFLAGS) -c $< -o $@
link_bin = $(CXX) $(1) $(LDFLAGS) $^ -o $@

define so_template
TARGETS += $(1).$$(SOEXT)
OBJECTS += $$($(join $(1),_OBJS))

all: $(1).$$(SOEXT)

$(1).$$(SOEXT): $$($(join $(1),_OBJS))
	$$(CXX) -shared $$($(join $(1),_LDFLAGS)) $$(LDFLAGS) $$^ -o $$@
endef

define bin_template
OBJECTS += $(1).$(OBJEXT)
TARGETS += $(1)

all: $(1)

$(1): $(1).$$(OBJEXT)
	$$(CXX) $$($(join $(1),_LDFLAGS)) $$(LDFLAGS) $$^ -o $$@
endef

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

libezio_OBJS := $(addsuffix .$(OBJEXT), $(EZIO_SOURCES))
libezio_LDFLAGS = -lev

$(eval $(call so_template, libezio))

# === sample rules ===

SAMPLE_CXXFLAGS += -I$(TOPLEVEL_DIR)
SAMPLE_LDFLAGS += -L$(TOPLEVEL_DIR) -lezio

sample/%.$(OBJEXT): sample/%.cpp
	$(call compile_cpp, $(SAMPLE_CXXFLAGS))

# === sample/test ===

sample/test_LDFLAGS = $(SAMPLE_LDFLAGS)

$(eval $(call bin_template, sample/test))

# === sample/server ===

sample/server_LDFLAGS = $(SAMPLE_LDFLAGS)

$(eval $(call bin_template, sample/server))

# === dependencies ===

CXXFLAGS += -MMD -MP
DEP_FILES = $(OBJECTS:%.$(OBJEXT)=%.d)
-include $(DEP_FILES)

