
######################################
# includes
######################################
CFLAGS  := -I/usr/include/ncurses -DCURSES_LOC="<ncurses.h>" -DLOCALE -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer
LDFLAGS := -lncurses


#######################################
# binaries
#######################################
lxdialog := lxdialog/checklist.o lxdialog/util.o lxdialog/inputbox.o
lxdialog += lxdialog/textbox.o lxdialog/yesno.o lxdialog/menubox.o

conf-objs  := zconf.tab.o conf.o  
mconf-objs := zconf.tab.o mconf.o $(lxdialog)

#######################################
# remove
#######################################
ifeq ($(OS), Windows_NT)
RM = del /Q /S
else
RM = rm -rf
endif


# default action: build all
all: prepare mconf conf


#######################################
# build the application
#######################################
prepare:
	cp zconf.lex.c_shipped zconf.lex.c
	cp zconf.tab.c_shipped zconf.tab.c

mconf: $(mconf-objs)
	@$(MAKE) prepare
	gcc -o $@ $^ $(LDFLAGS)

conf: $(conf-objs)
	@$(MAKE) prepare
	gcc -o $@ $^ $(LDFLAGS)

%.o : %.c
	gcc -c $(CFLAGS) $(LDFLAGS) $< -o $@


#######################################
# clean up
#######################################
clean:
ifneq ($(OS), Windows_NT)
	@$(RM) lxdialog/*o
endif
	@$(RM) *.o
	@$(RM) conf mconf
