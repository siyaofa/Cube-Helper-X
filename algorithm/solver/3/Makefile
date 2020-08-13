CKOCIEMBA_SRC = ckociemba/coordcube.c ckociemba/cubiecube.c ckociemba/facecube.c ckociemba/search.c
CKOCIEMBA_INCLUDE = ckociemba/include
CFLAGS = -std=c99 -O3 -shared -fPIC
BINDIR = bin
BIN = libkociemba.so

solve: $(CKOCIEMBA_SRC)
	mkdir -p $(BINDIR)
	gcc $(CFLAGS) $(CKOCIEMBA_SRC) -I$(CKOCIEMBA_INCLUDE)  -o $(BINDIR)/$(BIN)