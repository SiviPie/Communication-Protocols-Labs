CXXFLAGS= -Wall -Werror -Wno-error=unused-variable

all: send recv

link_emulator/lib.o:
	$(MAKE) -C link_emulator

send: send.o link_emulator/lib.o common.o
	g++ $(CXXFLAGS) -g send.o link_emulator/lib.o common.o -o send

recv: recv.o link_emulator/lib.o common.o
	g++ $(CXXFLAGS) -g recv.o link_emulator/lib.o common.o -o recv

common.o: common.c common.h

.cpp.o:
	g++ $(CXXFLAGS) -g -c $?

clean:
	$(MAKE) -C link_emulator clean
	-rm -f *.o send recv common.h.gch
