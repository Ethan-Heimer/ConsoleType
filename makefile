TOPSIR := home/crookedshaft445/Programming/Cpp/ConsoleType/
SRCDIR := $(TOPDIR)src/
OBJDIR := $(TOPDIR)obj/
BINDIR := $(TOPDIR)bin/
NAME := ConsoleType
EXE := $(BINDIR)$(NAME)
SFILES := cpp
OFILES := o
CC := g++
CFLAGS := -c -Wall
SOURCES := $(shell find $(SRCDIR) -name "*.$(SFILES)")
OBJECTS := $(patsubst $(SRCDIR)%.$(SFILES), $(OBJDIR)%.$(OFILES), $(SOURCES))
ALLFILES := $(SOURCES)

LIBS := -lncursesw

$(EXE): $(OBJECTS)
	@$(CC) $^ $(LIBS) -o $@
$(OBJDIR)%$(OFILES): $(SRCDIR)%$(SFILES)
	@$(CC) $(CFLAGS) $< -o $@
