CC = gcc
RM = rm -f
OBJS = main.o system.o matrix.o utils.o
LIBS = -lm
OUTPUT = matrixInv
CFLAGS = 

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(OUTPUT)

main.o: main.c 
	$(CC) -c $(CFLAGS) $(LIBS) main.c

system.o: system.c 
	$(CC) -c $(CFLAGS) $(LIBS) system.c

matrix.o: matrix.c 
	$(CC) -c $(CFLAGS) $(LIBS) matrix.c
	
utils.o: utils.c 
	$(CC) -c $(CFLAGS) $(LIBS) utils.c

clean limpar:
	@echo "Limpando..."
	@$(RM) $(OBJS)

purge faxina: clean
	@echo "Faxina..."
	@$(RM) $(OUTPUT)