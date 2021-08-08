NAME		=	philo

SRCS		= 	philo.c \
				create.c \
				libft.c \
				parser.c \
				routine.c

OBJS		= 	$(SRCS:.c=.o)

CC			= 	gcc

FLAGS		= 	-Wall -Wextra -Werror

RM			= 	rm -f

all:			$(NAME)

%.o:%.c
				$(CC) $(FLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re