# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 12:12:49 by ngordobi          #+#    #+#              #
#    Updated: 2024/11/08 12:23:09 by ngordobi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	gcc
CC_FLAGS			=	-g -Wall -Wextra -Werror
RL_FLAGS			=	-I/usr/include/readline -lreadline

LIBFT				=	libft.a

SRC_PATH			=	./src/
UT_PATH				=	./src/utils/
SPLIT_PATH			=	./src/split_args/
LIBFT_PATH			=	./libft/

SOURCES				=	$(SRC_PATH)minishell.c \
						$(SRC_PATH)structs.c \
						$(SRC_PATH)init_structs.c \

UT_SRC				=	$(UT_PATH)split_args.c \
						$(UT_PATH)parsing_utils.c \
						$(UT_PATH)rdl_utils.c \

OBJECTS				= 	$(SOURCES:%.c=%.o)
UT_OBJ				= 	$(UT_SRC:%.c=%.o)

INCLUDES			=	./includes/minishell.h \
						./includes/libft.h \

#COLORS
BLUE				=	\033[1;34m
BOLD_BLUE			=	\033[0;34m
WHITE				=	\033[0m

define MINISHELL
$(BOLD_BLUE)

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

all:				$(NAME) $(LIBFT)

$(NAME):			$(OBJECTS) $(UT_OBJ) $(LIBFT) $(INCLUDES)
					$(CC) $(CC_FLAGS) $(OBJECTS) $(UT_OBJ) $(LIBFT) $(RL_FLAGS) -o $(NAME)
					mkdir -p $(SRC_PATH)objects/
					mv $(OBJECTS) $(SRC_PATH)objects/
					mkdir -p $(UT_PATH)objects/
					mv $(UT_OBJ) $(UT_PATH)objects/
					echo "\n························· Compilation complete ··························"
					echo "$$MINISHELL"

$(LIBFT):
					@make --no-print-directory -C $(LIBFT_PATH)

clean:
					rm -rf $(SRC_PATH)objects/
					rm -rf $(SRC_PATH)*.o
					rm -rf $(UT_PATH)objects/
					rm -rf $(UT_PATH)*.o
					@make clean --no-print-directory -C $(LIBFT_PATH)
					echo "$(WHITE) · $(BLUE)Minishell objects removed.$(WHITE)\n"
					
fclean:				clean
					rm -rf $(NAME)
					rm -rf $(LIBFT)
					@make fclean --no-print-directory -C $(LIBFT_PATH)
					echo "$(WHITE) · $(BLUE)Minishell executable removed.$(WHITE)\n"

re:					fclean all
.PHONY:				all clean fclean re
