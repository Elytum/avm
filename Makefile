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
			must/Int8.cpp			\
			exceptions/syntax.cpp		\
			exceptions/invalid_file.cpp

INC		=	-I ./includes -I ./srcs/exceptions -I ./libs -I ./srcs/must
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
