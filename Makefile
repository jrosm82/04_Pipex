NAME = pipex

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	pipex.c\
	pipex_utils.c\
		-Llibft\
		-Lft_printf\
		-lft\
		-lftprintf
		



$(NAME) :
	make all -C libft
	make all -C ft_printf
	cc $(CFLAGS) -o $(NAME) $(SRCS)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft
	make fclean -C ft_printf

clean :
	$(RM) $(NAME)
	make clean -C libft
	make clean -C ft_printf

re : fclean all
