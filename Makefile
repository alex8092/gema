UNAME_S := $(shell uname -s)

CXXFLAGS	=	-std=c++11 -W -Wall -I./include
ifeq ($(UNAME_S),Darwin)
	CXX = clang++
	#	Dynamic paths not yet ...
	#
	#	brew install sdl2 glew glfw3
	#
	CXXFLAGS += -I/usr/local/Cellar/sdl2/2.0.3/include -I/usr/local/Cellar/glew/1.11.0/include/ -I/usr/local/Cellar/glfw3/3.0.4/include
	LDFLAGS = -L/usr/local/Cellar/sdl2/2.0.3/lib -L/usr/local/Cellar/glfw3/3.0.4/lib -L/usr/local/Cellar/glew/1.11.0/lib -lsdl2 -framework OpenGL -lglfw3 -lglew
else
	CXX = g++-4.8
	LDFLAGS = -lSDL2 -lGLEW -lGL
endif

DEBUG	=	true

ifeq ($(DEBUG),true)
	CXXFLAGS += -O0 -g3 -fno-inline
	OBJDIR = obj/Debug
	BINDIR = bin/Debug
else
	CXXFLAGS += -O2
	ifneq ($(CXX),clang++)
		CXXFLAGS += -s
	endif
	OBJDIR = obj/Release
	BINDIR = bin/Release
endif

NAME	=	$(BINDIR)/gema

SRCS	= $(shell find src -name "*.cpp")
OBJS	= $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

DEPS	=	$(OBJDIR)/Makefile.deps

all				:	$(OBJDIR) $(BINDIR) $(DEPS) $(NAME)

$(addprefix $(OBJDIR)/, %.o)	:	%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(NAME)			:	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)  $(LDFLAGS)

$(OBJDIR)		:
	/bin/mkdir -p $(OBJDIR)/src

$(BINDIR)		:
	/bin/mkdir -p $(BINDIR)/src

ifneq ("$(wildcard $(DEPS))", "")
-include $(DEPS)
endif

$(DEPS) :
	$(eval RETURN_VAL := $(shell makedepend 2>/dev/null; echo $$?))
	@if [ $(RETURN_VAL) -eq 0 ]; then																\
		makedepend -- $(CXXFLAGS) -- $(SRCS) -p $(OBJDIR)/ -Y./include -f- > $(DEPS) 2>/dev/null;	\
	fi

clean		:
	/bin/rm -f $(NAME)

fclean		:
	/bin/rm -fr $(OBJDIR) $(BINDIR)

re			:	fclean all

run			:	all
	./$(NAME)

.PHONY: re clean fclean run
# DO NOT DELETE
