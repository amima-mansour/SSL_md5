# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amansour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 13:33:28 by amansour          #+#    #+#              #
#    Updated: 2019/07/02 09:55:59 by amansour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# SOURCES       															   #
################################################################################

SRCS		= $(addprefix $(PATH_SRC)/, \
							main.c\
							md5.c\
							sha256.c\
							sha224.c\
							sha512.c\
							sha384.c\
							print_hash.c\
							stdin.c\
							error.c\
							prepare_hash.c\
							hash_sha2_256.c\
							hash_sha2_512.c\
							tools.c)

################################################################################
# BASIC VARIABLES															   #
################################################################################

PATH_OBJ	= obj
PATH_SRC	= src
PATH_INC	= inc

NAME		= ft_ssl
CFLAGS		= -Wall -Wextra -Werror
OBJECTS 	= $(SRCS:$(PATH_SRC)/%.c=$(PATH_OBJ)/%.o)
LIBRARY     = libft/libft.a
################################################################################
# RULES																		   #
################################################################################

all: $(NAME)

$(NAME): $(LIBRARY) $(OBJECTS)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo && echo $(GREEN) "[√]     [$(NAME) Successfully Compiled!]"
	@echo $(WHITE)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	@gcc -c -o $@ $(CFLAGS) $^ -I $(PATH_INC)/

$(LIBRARY):
	@make -C libft/

# - - - - - - - - — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

DEL = /bin/rm -rf

clean:
	@$(DEL) $(shell find . -name '*.o')
	@rm -rf $(PATH_OBJ)
	@make clean -C libft/

fclean: clean
	@$(DEL) $(NAME)
	@make fclean -C libft/

re: fclean all

re: fclean $(NAME)

# Text Colorization — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
GREEN = "\033[1;32m"
WHITE = "\033[1;37m"

# Norminette Check — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

nc:
	@echo && echo $(GREEN) "Checking Norme -- Source Files:" && echo $(WHITE);
	@norminette $(shell find . -name '*.c')

nh:
	@echo && echo $(GREEN) "Checking Norme -- Header Files:" && echo $(WHITE);
	@norminette $(shell find . -name '*.h')

na: nh nc

# Correction Script — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

correction:

	@echo '==============================================================='
	@echo && echo $(GREEN) "I - Checking Author File:" && echo $(WHITE);
	@sleep 1
	cat author
	@echo
	@sleep 1

	@echo '==============================================================='
	@echo && echo $(GREEN) "II - Checking Norme:" && echo $(WHITE);
	@sleep 1

	@echo && echo $(GREEN) "a - Checking Norme -- Header Files:" && echo $(WHITE);
	@sleep 1
	@norminette $(shell find . -name '*.h')

	@sleep 1
	@echo && echo $(GREEN) "b - Checking Norme -- Source Files:" && echo $(WHITE);
	@sleep 1
	@norminette $(shell find . -name '*.c')
	@echo

	@echo '==============================================================='
	@sleep 1
	@echo && echo $(GREEN) "III - Checking Compilation:" && echo $(WHITE);
	@sleep 1
	@echo 'make all'
	@echo
	@sleep 1
	@make all
	@sleep 1
	@sleep 1

	@echo '==============================================================='
	@echo && echo $(GREEN) "IV - Checking Makefile Rules:" && echo $(WHITE);
	@sleep 1
	@echo 'Current working directory:'
	@echo
	@sleep 1
	@echo 'ls -1'
	@echo
	@sleep 1
	@ls -1
	@echo
	@sleep 1

	@echo '==============================================================='
	@echo && echo $(GREEN) "a - make clean" && echo $(WHITE);
	@sleep 1
	@echo 'make clean'
	@echo
	@make clean
	@sleep 1
	@sleep 1
	@ls -1
	@echo
	@sleep 1

	@echo '==============================================================='
	@echo && echo $(GREEN) "b - make fclean" && echo $(WHITE);
	@sleep 1
	@echo 'make fclean'
	@echo
	@make fclean
	@sleep 1
	@sleep 1
	@ls -1
	@echo
	@sleep 1

	@echo '==============================================================='
	@echo && echo $(GREEN) "V - Explain code/approach" && echo $(WHITE);
	@echo $(GREEN) "VI - Q&A" && echo $(WHITE);
	@echo '==============================================================='

# — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

.PHONY: all clean fclean re nc nh na

# — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —