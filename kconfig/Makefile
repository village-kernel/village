
######################################
# includes
######################################
HOST_CFLAGS  := -I/usr/include/ncurses -DCURSES_LOC="<ncurses.h>" -DLOCALE -DKBUILD_NO_NLS
HOST_CFLAGS  +=  -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer
HOST_LDFLAGS := -lncurses

HOST_CC      := gcc

#######################################
# binaries
#######################################
lxdialog := lxdialog/checklist.o lxdialog/util.o lxdialog/inputbox.o
lxdialog += lxdialog/textbox.o lxdialog/yesno.o lxdialog/menubox.o

conf-objs  := zconf.tab.o conf.o  
mconf-objs := zconf.tab.o mconf.o $(lxdialog)

# We need this, in case the user has it in its environment
unexport CONFIG_


# default action: build all
all: prepare mconf conf


#######################################
# build the application
#######################################
prepare:
	$(Q)cp zconf.lex.c_shipped zconf.lex.c
	$(Q)cp zconf.tab.c_shipped zconf.tab.c

mconf: $(mconf-objs)
	$(Q)echo Host Building mconf
	$(Q)$(MAKE) prepare
	$(Q)$(HOST_CC) -o $@ $^ $(HOST_LDFLAGS)

conf: $(conf-objs)
	$(Q)echo Host Building conf
	$(Q)$(MAKE) prepare
	$(Q)$(HOST_CC) -o $@ $^ $(HOST_LDFLAGS)

%.o : %.c
	$(Q)echo Host Compiling $(notdir $@)
	$(Q)$(HOST_CC) -c $(HOST_CFLAGS) $< -o $@


#######################################
# clean up
#######################################
clean:
	$(Q)rm -rf lxdialog/*o
	$(Q)rm -rf *.o
	$(Q)rm -rf conf mconf zconf.lex.c zconf.tab.c
