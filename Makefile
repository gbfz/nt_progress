NAME		=	calculate
OBJS		=	Calculator.o \
			calculate.o
CXX		=	g++
CXXFLAGS	=	-std=c++17 -Wall -Wextra -Werror
GTESTFLAGS	=	-pthread -lgtest -lgtest_main

all:		$(NAME)

DEPS		=	$(patsubst %.o, %.d, $(OBJS))
-include		$(DEPS)
DEPFLAGS	=	-MMD -MF $(@:.o=.d)

$(NAME):	$(OBJS) Makefile
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o:		src/%.cpp Makefile
		$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS) $(DEPS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
