NAME		= libasm.a

SRCS		= ft_strlen.s \
			  ft_strcpy.s \
			  ft_strcmp.s \
			  ft_write.s \
			  ft_read.s \
			  ft_strdup.s

OBJS		= $(SRCS:.s=.o)

TEST		= test_libasm
TEST_SRCS	= main.c

ASM			= nasm
ASMFLAGS	= -f elf64
AR			= ar
ARFLAGS		= rcs
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

test: $(NAME) $(TEST_SRCS)
	$(CC) $(CFLAGS) $(TEST_SRCS) -L. -lasm -o $(TEST)
	./$(TEST)

clean:
	$(RM) $(OBJS) $(TEST)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test
