# LIKWID
	LIKPATH = /home/soft/likwid
	
# PROGRAMA
    PROG = interpola

# Compilador
    CC     = gcc
    CFLAGS = -Wall -Wpedantic -Werror -g -O3 -std=c11 -mavx -march=native -D_POSIX_C_SOURCE=199309L -I $(LIKPATH)/include -L $(LIKPATH)/lib
    LDLIBS = -DLIKWID_PERFMON -lm -llikwid

# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

all: $(PROG)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
