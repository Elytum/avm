# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achazal <achazal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:54:29 by achazal           #+#    #+#              #
#    Updated: 2014/12/13 12:55:35 by achazal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------Compilateur------------------#
CC		=	g++
#--------------Name-------------------------#
NAME	=	avm
MYPATH	=	$(HOME)
#--------------Sources----------------------#
FILES	=	main.cpp					\
			compile.cpp					\
			extract.cpp					\
			execute.cpp					\
			get_file_contents.cpp		\
			put_file_contents.cpp		\
			last_edit.cpp				\
			must/Factory.cpp			\
			must/Int8.cpp				\
			must/Int16.cpp				\
			must/Int32.cpp				\
			must/Float.cpp				\
			must/Double.cpp				\
			errors/Overflow.cpp			\
			errors/Underflow.cpp		\
			errors/Division.cpp			\
			errors/Modulo.cpp			\
			errors/WrongAssert.cpp		\
			errors/Print.cpp			\
			errors/Type.cpp				\
			errors/Pop.cpp				\
			errors/Instruction.cpp		\
			errors/Syntax.cpp			\
			errors/LexicalFunction.cpp	\
			errors/LexicalType.cpp		\
			errors/MissingArgument.cpp	\
			errors/ExtraArgument.cpp	\
			errors/AssertEmpty.cpp		\
			errors/PrintEmpty.cpp		\
			errors/MathError.cpp		\
			errors/InvalidFile.cpp

INC		=	-I ./includes -I ./srcs/exceptions -I ./srcs/errors -I ./libs -I ./srcs/must
CCFLAGS	=	-std=c++11 -Wall -Wextra -Werror -g

SRCS	=	$(addprefix srcs/, $(FILES))
OBJS	=	$(SRCS:.cpp=.o)

#--------------Actions----------------------#

.PHONY: $(NAME) clean fclean re test

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CCFLAGS) $(INC) $(OBJS) -o $(NAME) $(LIBS) -O3

%.o: %.cpp
	$(CC) $(CCFLAGS) $(INC) -c $< -o $@
	
clean:
	rm -f $(OBJS)
	
fclean:	clean
	rm -f $(NAME)

re: fclean all
	make
