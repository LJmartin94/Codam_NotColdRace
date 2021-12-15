# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/15 08:21:27 by limartin      #+#    #+#                  #
#    Updated: 2021/12/15 09:17:53 by limartin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = coldrace

SRC_PATH = ./srcs/

INCL_PATH = ./includes/

UTILS = utils/

CC = gcc

CFLAGS = -Wall -Wextra -Werror

HEADER_FILES = $(INCL_PATH)

#Source files mandatory part
SRC = $(SRC_PATH)main.c \
	$(SRC_PATH)store_kvps.c \
	$(SRC_PATH)$(UTILS)get_next_line.c \
	$(SRC_PATH)$(UTILS)get_next_line_utils.c \
	$(SRC_PATH)$(UTILS)general_utils.c \


#Source files bonus part
SRC_B = # $(SRC_PATH) bonus_goes_here.c #TODO

#Object files
OBJ := ${SRC:%.c=%.o}

#Bonus object files
BOBJ := ${SRC_B:%.c=%.o}

#Avoid relinking bonus
ifdef WITH_BONUS
COMPILE_OBJECTS = $(OBJ) $(BOBJ)
else
COMPILE_OBJECTS = $(OBJ)
endif

all: $(NAME)

$(NAME): $(COMPILE_OBJECTS)
	@$(CC) -o $(NAME) $(COMPILE_OBJECTS) $(CFLAGS)
	@echo "!ColdRace compiled"

%.o: %.c $(HEADER_FILES)
	@$(CC) -o $@ -c $< $(CFLAGS) -O3 -I $(INCL_PATH)

bonus:
	@$(MAKE) WITH_BONUS=1 all
	@echo "...but done ✨fancy✨"

clean:
	@rm -f $(OBJ) $(BOBJ)
	@echo "!ColdRace object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "!ColdRace fully cleaned"

re: fclean all

.PHONY: all bonus clean fclean re