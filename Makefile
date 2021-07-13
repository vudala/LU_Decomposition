

CC = gcc
RM = rm -f
OBJS = main.o system.o utils.o
LIBS = -lm
OUTPUT = fatoracao
CFLAGS = 

all: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(OUTPUT)

main.o: main.c 
	$(CC) -c $(CFLAGS) $(LIBS) main.c

system.o: system.c 
	$(CC) -c $(CFLAGS) $(LIBS) system.c

utils.o: utils.c 
	$(CC) -c $(CFLAGS) $(LIBS) utils.c


clean limpar:
	@echo "Limpando..."
	@$(RM) $(OBJS)

purge faxina: clean
	@echo "Aplicando cloro..."
	@echo "Esfregando..."
	@echo "Vish... derrubei o balde"
	@echo "MÃE TRAZ O PANO"
	@$(RM) $(OUTPUT)