NAME = minishell

PATH_SRCS = ./sources/
PATH_OBJS = ./objects/
PATH_INCL = ./includes/
PATH_LIBFT = ./libft/

VPATH = $(addprefix $(PATH_SRCS), \
		./ \
		./sources/)

SRCS = 	main.c \
		signals.c \
		exit.c \
		pwd.c \
		cd.c \
		echo.c \
		env.c \
		export.c \

OBJS = $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

LIBFT = $(PATH_LIBFT)libft.a

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
IFLAGS = -I $(PATH_INCL)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(PATH_LIBFT)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(OBJS): | $(PATH_OBJS)

$(PATH_OBJS)%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(PATH_OBJS):
	mkdir -p $(PATH_OBJS)

clean:
	rm -rf $(PATH_OBJS)
	make clean -C $(PATH_LIBFT)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(PATH_LIBFT)

re: fclean all

.PHONY: all clean fclean re