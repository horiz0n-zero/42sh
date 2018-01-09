# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/23 13:37:43 by afeuerst          #+#    #+#              #
#    Updated: 2017/10/18 13:52:36 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

C_SRC = $(shell find ./srcs -type f | grep "\.c")
O_SRC = $(C_SRC:.c=.o)

FLAGS = -Weverything
INCLUDES = -I ./includes

PRINT = printf "\r\e[38;5;39m%-27s -->> \e[38;5;46m%-27s"

all: $(NAME)

$(NAME): $(O_SRC)
	@ar -rsc $@ $^
	@printf "\r\e[38;5;118m%s is now compiled ! %30s\n\e[0;37m" $(NAME) ""

%.o: %.c
	@clang $< $(FLAGS) $(INCLUDES) -c -o $@ && $(PRINT) $(notdir $<) $(notdir $@)

clean:
	@rm -rf $(O_SRC)

fclean: clean
	@rm -rf $(NAME)
	@printf "\e[38;5;196m%s as been removed.\n\e[0;37m" $(NAME)

re: fclean all
