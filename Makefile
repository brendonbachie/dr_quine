# **************************************************************************** #
#            Dr_Quine  —  top-level (recurses into C/ and ASM/)                #
# **************************************************************************** #
# The subject only requires a Makefile inside C/ and ASM/. This one is a
# convenience wrapper so `make` at the root builds both implementations.

DIRS = C ASM

all clean fclean re:
	@for d in $(DIRS); do $(MAKE) -C $$d $@; done

.PHONY: all clean fclean re
