CKOCIEMBA_SRC = PocketCube.cpp
CKOCIEMBA_INCLUDE = .
CFLAGS = 
CXXFLAGS = -std=c++11 -O3 -shared -fPIC
BINDIR = bin
BIN = libpocketcube.so

solve: $(CKOCIEMBA_SRC)
	mkdir -p $(BINDIR)
	g++ $(CXXFLAGS) $(CKOCIEMBA_SRC) -I$(CKOCIEMBA_INCLUDE)  -o $(BINDIR)/$(BIN)