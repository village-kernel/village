
CFLAGS  := -I/usr/include/ncurses -DCURSES_LOC="<ncurses.h>" -DLOCALE -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer
LDFLAGS := -lncurses

cc := gcc

lxdialog := lxdialog/checklist.o lxdialog/util.o lxdialog/inputbox.o
lxdialog += lxdialog/textbox.o lxdialog/yesno.o lxdialog/menubox.o

conf-objs  := conf.o  zconf.tab.o
mconf-objs := mconf.o zconf.tab.o $(lxdialog)

all: prepare mconf conf

%.o : %.c
	gcc -c $(CFLAGS) $(LDFLAGS) $< -o $@

prepare:
	cp zconf.lex.c_shipped zconf.lex.c
	cp zconf.tab.c_shipped zconf.tab.c

mconf: $(mconf-objs)
	@$(MAKE) prepare
	gcc -o $@ $^ $(LDFLAGS)

conf: $(conf-objs)
	@$(MAKE) prepare
	gcc -o $@ $^ $(LDFLAGS)

clean:
	find -name "*.o" -exec rm "{}" \;
