#
#  USAGE:
#     make          ... to build the program
#

include make.def

EXES= pi$(EXE) #Add others binaries files

all: $(EXES)

pi$(EXE): pi.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o pi$(EXE) pi.$(OBJ) $(LIBS)

# Add the others sources files (Binaries files)

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<