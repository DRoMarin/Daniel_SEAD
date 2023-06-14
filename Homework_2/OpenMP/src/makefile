#
#  USAGE:
#     make          ... to build the program
#

include make.def

EXES= pi pi_omp_private $(EXE) #Add others binaries files

all: $(EXES)

pi$(EXE): pi.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o pi$(EXE) pi.$(OBJ) $(LIBS)

pi_omp_private$(EXE): pi_omp_private.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o pi_omp_private$(EXE) pi_omp_private.$(OBJ) $(LIBS)

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<