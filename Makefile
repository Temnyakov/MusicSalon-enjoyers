BINDIR = bin
SRCDIR = src
OBJDIR = obj
TARGET = $(BINDIR)/main
CXXFLAGS = -std=c++20 -Ofast

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJDIR)/main.o $(OBJDIR)/authentication.o $(OBJDIR)/sqlite3_database.o \
 	   $(OBJDIR)/aes128.o $(OBJDIR)/MD5.o $(OBJDIR)/user_actions.o
	mkdir $(BINDIR)
	g++-11 -o $@ $^ -Ofast -lsqlite3

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	mkdir $(OBJDIR)
	g++-11 -c -o $@ $< $(CXXFLAGS) -lsqlite3

#$(OBJDIR)/sqlite3.o: $(SRCDIR)/sqlite3.c
#	gcc-11 -c -o $@ $< -Ofast

$(OBJDIR)/sqlite3_database.o: $(SRCDIR)/sqlite3_database.cpp
	g++-11 -c -o $@ $< $(CXXFLAGS) -lsqlite3

$(OBJDIR)/authentication.o: $(SRCDIR)/authentication.cpp
	g++-11 -c -o $@ $< $(CXXFLAGS) -lsqlite3

$(OBJDIR)/MD5.o: $(SRCDIR)/MD5.cpp
	g++-11 -c -o $@ $< $(CXXFLAGS) -lsqlite3

$(OBJDIR)/aes128.o: $(SRCDIR)/aes128.cpp
	g++-11 -c -o $@ $< $(CXXFLAGS) -lsqlite3

$(OBJDIR)/user_actions.o: $(SRCDIR)/user_actions.cpp
	g++-11 -c -o $@ $< $(CXXFLAGS) -lsqlite3

clean:
	rm -rf $(BINDIR) $(OBJDIR)