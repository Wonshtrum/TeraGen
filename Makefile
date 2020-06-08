LIBS = -lGL -lGLU -lglfw3 -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
GPP = g++ -std=c++11 -Wall
GOO = $(GPP) -c
RM = rm -if
srcdir = src/
bindir = bin/
docdir = doc/
savedir = save/
SRC = $(wildcard $(srcdir)*.cpp)
HEAD = $(wildcard $(srcdir)*.h)
OBJ = $(subst $(srcdir), $(bindir), $(SRC:.cpp=.o))
PROG = Prog

all = $(PROG)

$(PROG) : $(OBJ)
	$(GPP) $^ -o $@ $(LIBS)

$(bindir)%.o : $(srcdir)%.cpp
	$(GOO) $^ -o $@

.PHONY : clean
clean :
	$(RM) $(bindir)*

.PHONY : init
init : 
	mkdir src bin
