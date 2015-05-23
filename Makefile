srcdir = src
incdir = include
objdir = .obj
depdir = .dep

cflags := $(CFLAGS) -I$(incdir) -fPIC -g -O0 -c -MMD -MF
ldflags := $(LDFLAGS) -o
arflags := rcs
depflags := -MM -I$(incdir) -o

cc := $(CC)
ld := $(cc)
dyld := $(cc) -shared
ar := ar
rm := rm -rf
mkdir := mkdir -p

raw_src := clock_serv.c clock_task.c clock_thread.c \
			clock_getres.c clock_gettime.c clock_settime.c \
			clock_getcpuclockid.c pthread_getcpuclockid.c

src := $(addprefix $(srcdir)/, $(raw_src))
obj := $(addprefix $(objdir)/, $(raw_src:%.c=%.o))
dep := $(wildcard $(depdir)/*)

version = 0.0.1
target = libmachclock-$(version)


.PHONY: all static dynamic clean

all: $(objdir) $(depdir) static dynamic

static: $(target).a

dynamic: $(target).dylib

clean:
	$(rm) $(target).a
	$(rm) $(target).dylib
	$(rm) $(objdir)

distclean: clean
	$(rm) $(depdir)

$(objdir):
	$(mkdir) $@

$(depdir):
	$(mkdir) $@

$(target).dylib: $(obj)
	$(dyld) -o $@ $+

$(target).a: $(obj)
	$(ar) $(arflags) $@ $^

$(objdir)/%.o: $(srcdir)/%.c
	$(cc) $(cflags) $(depdir)/$*.d -o $@ $<

include $(dep)

