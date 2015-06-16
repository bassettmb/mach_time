version = 0.0.3

srcdir = src
incdir = include
objdir = .obj
depdir = .dep

cflags := $(CFLAGS) -I$(incdir) -Wall -Wextra \
			-Wno-unused-parameter -fPIC -fvisibility=hidden \
			-g -O0 -c -DMT_VERSION=\"$(version)\" -MMD -MF

ldflags := $(LDFLAGS) -fvisibility=hidden -o
arflags := rcs

cc := $(CC)
ld := $(cc)
dyld := $(cc) -shared
ar := ar
rm := rm -rf
mkdir := mkdir -p

raw_src := mt_version.c mt_clock_serv.c mt_clock_task.c mt_clock_thread.c \
			mt_clock_getres.c mt_clock_gettime.c mt_clock_settime.c \
			mt_clock_getcpuclockid.c mt_pthread_getcpuclockid.c

src := $(addprefix $(srcdir)/, $(raw_src))
obj := $(addprefix $(objdir)/, $(raw_src:%.c=%.o))
dep := $(wildcard $(depdir)/*)

target = libmachtime-$(version)


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
	$(ar) $(arflags) $@ $+

$(objdir)/%.o: $(srcdir)/%.c
	$(cc) $(cflags) $(depdir)/$*.d -o $@ $<

include $(dep)

