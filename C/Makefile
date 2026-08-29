# **************************************************************************** #
#                              Dr_Quine  —  C                                  #
# **************************************************************************** #

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

NAMES   = Colleen Grace Sully

all: $(NAMES)

# compile each program from its source (only rebuilds if the .c changed)
$(NAMES): %: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(addsuffix .o, $(NAMES))

fclean: clean
	rm -f $(NAMES)
	rm -f Grace_kid.c Sully_*

re: fclean all

.PHONY: all clean fclean re
