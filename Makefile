CC = 		gcc
OBJS = 		main.o system.o matrix.o utils.o
LIBS = 		-lm
LIKWID_PATH = /home/soft/likwid
OUTPUT = 	matrixInv
CFLAGS = 	-Wall
RM = 		rm -f

all: $(OBJS)
	$(CC) -L$(LIKWID_PATH)/lib $(OBJS) $(LIBS) -o $(OUTPUT)

main.o: main.c 
	$(CC) -DLIKWID_PERFMON -I${LIKWID_PATH}/include -c $(CFLAGS) $(LIBS) main.c
	
%.o: %.c %.h
	$(CC) -DLIKWID_PERFMON -I${LIKWID_PATH}/include -c $(CFLAGS) $(LIBS) $<

clean limpar:
	@echo "Limpando..."
	@$(RM) $(OBJS)

purge faxina: clean
	@echo "Faxina..."
	@$(RM) $(OUTPUT)