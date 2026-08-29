# **************************************************************************** #
#                              Dr_Quine  —  ASM                                #
# **************************************************************************** #

NASM      = nasm
NASMFLAGS = -f elf64
CC        = gcc

NAMES     = Colleen Grace Sully
OBJS      = $(addsuffix .o, $(NAMES))

all: $(NAMES)

# link each program from its object (only relinks if the .o changed)
$(NAMES): %: %.o
	$(CC) $< -o $@

# assemble each .s into its .o (only reassembles if the .s changed)
%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAMES)
	rm -f Grace_kid.s Sully_*

re: fclean all

.PHONY: all clean fclean re
