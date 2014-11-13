CXX = g++-4.8

CXXFLAGS = -std=c++11 -Iinclude

LDFLAGS = -lSDL2 -lGLEW -lGL

DEBUG = true

ifeq ($(DEBUG),true)
	CXXFLAGS += -O0 -g3
	BINDIR = bin/Debug
	OBJDIR = obj/Debug
	REPLACE = %s/src\//obj\/Debug\//g
else
	CXXFLAGS += -O2 -s
	BINDIR = bin/Release
	OBJDIR = obj/Release
	REPLACE = %s/src\//obj\/Release\//g
endif

SRCS = $(shell find src/ -name "*.cpp")

HEADERS = $(shell find include/ -name "*.hpp") $(shell find include/ -name "*.h")

INCLUDES = $(HEADERS)

OBJS = $(patsubst src/%,$(OBJDIR)/%,$(SRCS:.cpp=.o))

NAME = $(BINDIR)/gema

all: $(OBJDIR)/Makefile.deps $(NAME)

$(NAME): $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(LDFLAGS)

-include $(OBJDIR)/Makefile.deps

$(OBJDIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run:
	./$(NAME)

$(OBJDIR)/Makefile.deps: $(SRCS) $(HEADERS)
	@mkdir -p $(dir $@)
	@makedepend -Yinclude/ -- -- $(SRCS) -f- > $(OBJDIR)/Makefile.deps 2> /dev/null
	@\vim $(OBJDIR)/Makefile.deps -c '$(REPLACE)' -c wq

.PHONY: all clean fclean re run
