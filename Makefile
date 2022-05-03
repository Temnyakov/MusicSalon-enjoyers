BINDIR = bin
SRCDIR = src
OBJDIR = obj
TARGET = $(BINDIR)/main

$(TARGET): $(OBJDIR)/main.o $(OBJDIR)/sqlite3.o $(OBJDIR)/sqlite3_database.o
	mkdir -p $(BINDIR)
	g++ -o $@ $^ -Ofast

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	mkdir -p $(OBJDIR)
	g++ -c -o $@ $< -Ofast

$(OBJDIR)/sqlite3.o: $(SRCDIR)/sqlite3.c
	gcc -c -o $@ $< -Ofast

$(OBJDIR)/sqlite3_database.o: $(SRCDIR)/sqlite3_database.cpp
	g++ -c -o $@ $< -Ofast

clean:
	rm -f $(BINDIR) $(OBJDIR)