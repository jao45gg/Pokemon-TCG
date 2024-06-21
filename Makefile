CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := main.exe
CFLAGS := -g -Wall -std=c++11 -I include/
TESTTARGET := tests/Testes

all: main

Cartas:
	mkdir -p $(BUILDDIR)/Cartas
	$(CC) $(CFLAGS) -c $(SRCDIR)/Cartas.cpp -o $(BUILDDIR)/Cartas/Cartas.o

Baralho:
	mkdir -p $(BUILDDIR)/Baralho
	$(CC) $(CFLAGS) -c $(SRCDIR)/Baralho.cpp -o $(BUILDDIR)/Baralho/Baralho.o

Usuario:
	mkdir -p $(BUILDDIR)/Usuario
	$(CC) $(CFLAGS) -c $(SRCDIR)/Usuario.cpp -o $(BUILDDIR)/Usuario/Usuario.o

Partida:
	mkdir -p $(BUILDDIR)/Partida
	$(CC) $(CFLAGS) -c $(SRCDIR)/Partida.cpp -o $(BUILDDIR)/Partida/Partida.o

main: Cartas Baralho Usuario Partida
	$(CC) $(CFLAGS) $(BUILDDIR)/Cartas/Cartas.o $(BUILDDIR)/Baralho/Baralho.o $(BUILDDIR)/Usuario/Usuario.o $(BUILDDIR)/Partida/Partida.o $(SRCDIR)/main.cpp -o $(TARGET)
	# $(CC) $(CFLAGS) $(BUILDDIR)/Cartas/Cartas.o $(BUILDDIR)/Baralho/Baralho.o $(BUILDDIR)/Usuario/Usuario.o $(BUILDDIR)/Partida/Partida.o tests/Testes.cpp -o $(TESTTARGET)

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET) $(TESTTARGET)
