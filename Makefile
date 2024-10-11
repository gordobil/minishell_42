# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 11:26:56 by ngordobi          #+#    #+#              #
#    Updated: 2024/10/11 19:52:48 by ngordobi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	gcc
CC_FLAGS			=	-Wall -Wextra -Werror
RL_FLAGS			=	-I/usr/include/readline -lreadline

SRC_PATH			=	./src/

SOURCES				=	$(SRC_PATH)minishell.c \
						$(SRC_PATH)parser.c \
						$(SRC_PATH)utils.c \
						$(SRC_PATH)temp_libft.c \
						$(SRC_PATH)arg_split.c \

OBJECTS				= 	$(SOURCES:%.c=%.o)

INCLUDES			=	./includes/minishell.h \

#COLORS
BLUE				=	\033[1;33m
WHITE				=	\033[0m

define MINISHELL
$(BLUE)

 ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    
▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    
▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    
▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    
▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒
░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░
░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░
░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   
       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░
$(WHITE)
$(END)
endef
export MINISHELL

.SILENT:

all:				$(NAME)

$(NAME):			$(OBJECTS) $(INCLUDES)
					$(CC) $(CC_FLAGS) $(OBJECTS) $(RL_FLAGS) -o $(NAME)
					mkdir -p $(SRC_PATH)objects/
					mv $(OBJECTS) $(SRC_PATH)objects/
					echo "\n······················· Compilation complete ·························"
					echo "$$MINISHELL"

clean:
					rm -rf $(SRC_PATH)objects/
					rm -rf $(SRC_PATH)*.o
					echo "$(WHITE) · $(BLUE)Minishell objects removed.$(WHITE)\n"
					
fclean:				clean
					rm -rf $(NAME)
					echo "$(WHITE) · $(BLUE)Minishell executable removed.$(WHITE)\n"

re:					fclean all
.PHONY:				all clean fclean re
