SRC = pipex.c utils.c

OBJ = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = pipex.a

all : $(NAME)

$(NAME) : $(OBJ)
		ar rcs $(NAME) $(OBJ)

%.o : %.c
		$(CC) -c $< -o $@

clean : 
		rm -f $(OBJ)
	
fclean : clean
		rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
