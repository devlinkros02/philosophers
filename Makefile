NAME         = philo
CC        	 = cc
CFLAGS     	 = -Wall -Wextra -Werror -pthread -Iincs
RM           = rm -f
SRCS         = $(shell find src -type f -name '*.c')
OBJS         = $(SRCS:.c=.o)

all:        $(NAME)

$(NAME):    $(OBJS)
	@echo "Linking object files."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Build complete: $(NAME)."

src/%.o: src/%.c incs/philo.h
	@echo "Compiling $<."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:     clean
	$(RM) $(NAME)

re:         fclean all

.PHONY:     all clean fclean re
