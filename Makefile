LIBS = -lGL -lGLU -lglfw3 -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
GPP = g++ -std=c++11 -Wall
GOO = $(GPP) -c
GPY = coupled/extract.py
RM = rm -irf
srcdir = src/
srcpy = coupled/
bindir = bin/
docdir = doc/
savedir = save/
SRCPY := $(wildcard $(srcpy)*.cpp) $(wildcard $(srcpy)*/*.cpp)
SRC := $(subst $(srcpy), $(srcdir), $(SRCPY)) $(srcdir)main.cpp
HEAD := $(wildcard $(srcdir)*.h) $(wildcard $(srcdir)*/*.h)
OBJ := $(subst $(srcdir), $(bindir), $(SRC:.cpp=.o))
PROG = Prog

all = $(PROG)

$(PROG) : $(SRC) $(OBJ)
	$(GPP) $(OBJ) -o $@ $(LIBS)

$(bindir)%.o : $(srcdir)%.cpp
	mkdir -p $(dir $@)
	$(GOO) $^ -o $@

$(srcdir)%.cpp : $(srcpy)%.cpp $(GPY)
	mkdir -p $(dir $@)
	$(GPY) $(word 1, $^)
$(srcdir)%.h : $(srcpy)%.cpp $(GPY)
	mkdir -p $(dir $@)
	$(GPY) $(word 1, $^)

.PHONY : clean
clean :
	$(RM) $(bindir)*

.PHONY : init
init :
	mkdir src bin
