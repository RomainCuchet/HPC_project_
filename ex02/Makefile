# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahabbard <ahabbard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/18 22:53:36 by ahabbard          #+#    #+#              #
#    Updated: 2025/11/18 23:01:57 by ahabbard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES=main.c utils.c
OFILES=$(CFILES:.c=.o)
CC=mpicc
CFLAGS= -Wall -Wextra -Werror
Q=@
NAME=prog_ex02
NPROC=5
N=1000000000
#default i set N= 1000000000
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

run: $(NAME)
	$(Q)$(EXEC) -n $(NPROC)  ./$(NAME) $(N)
	$(Q)rm -f $(OFILES) $(NAME)
.PHONY: all clean fclean re exec run