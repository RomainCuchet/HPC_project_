# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurele <aurele@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/17 17:45:19 by aurele            #+#    #+#              #
#    Updated: 2025/11/24 14:43:22 by aurele           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES=main.c utils.c
OFILES=$(CFILES:.c=.o)
CC=mpicc
CFLAGS= -Wall -Wextra -Werror
Q=@
NAME=prog
NPROC=5
N=1000000000
#default we set N= 1000000000
EXEC=mpirun
all : $(NAME)

$(NAME): $(OFILES)
	$(Q)$(CC) $^ -o $(NAME)

%.o:%.c
	$(Q)$(CC) -c $< -o $@

clean:
	$(Q)rm -f $(OFILES)

fclean:clean
	$(Q)rm -f $(NAME)

re: fclean all

exec: $(NAME)
	$(Q)$(EXEC) -n $(NPROC)  ./$(NAME) $(N)

.PHONY: all clean fclean re exec run info

run: $(NAME)
	$(Q)$(EXEC) -n $(NPROC)  ./$(NAME) $(N)
	$(Q)rm -f $(OFILES) $(NAME)

info:
	@echo "default variables :"
	@echo "  NPROC = $(NPROC)"
	@echo "  N     = $(N)"
	@echo ""
	@echo "Commandes :"
	@echo "  all, clean, fclean, re, exec, run"
	@echo ""
	@echo "Usage :"
	@echo "  make run NPROC=4 N=1000"


