BINDIR = bin
SRCDIR = src
OBJDIR = obj
TARGET = $(BINDIR)/main
CXXFLAGS = -std=c++20 -Ofast

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJDIR)/main.o $(OBJDIR)/authentication.o $(OBJDIR)/sqlite3_database.o $(OBJDIR)/sqlite3.o $(OBJDIR)/aes128.o $(OBJDIR)/MD5.o
	mkdir $(BINDIR)
	g++ -o $@ $^ -Ofast

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	mkdir $(OBJDIR)
	g++ -c -o $@ $< $(CXXFLAGS)

$(OBJDIR)/sqlite3.o: $(SRCDIR)/sqlite3.c
	gcc -c -o $@ $< -Ofast

$(OBJDIR)/sqlite3_database.o: $(SRCDIR)/sqlite3_database.cpp
	g++ -c -o $@ $< $(CXXFLAGS)

$(OBJDIR)/authentication.o: $(SRCDIR)/authentication.cpp
	g++ -c -o $@ $< $(CXXFLAGS)

$(OBJDIR)/MD5.o: $(SRCDIR)/MD5.cpp
	g++ -c -o $@ $< $(CXXFLAGS)

$(OBJDIR)/aes128.o: $(SRCDIR)/aes128.cpp
	g++ -c -o $@ $< $(CXXFLAGS)

clean:
	rm -rf $(BINDIR) $(OBJDIR)
