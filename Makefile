NAME_ASM	=	asm

SOURCES	=	main.c\
			mem_init.c\
			ft_strccmp.c\
			encode_sti.c\
			encode_param.c\
			encode_cmd.c\
			memorize_label.c

DIR_ASM	=	asm/src

DIR_H	=	includes

DIR_O	=	temporary

SRCS	=	$(addprefix $(DIR_ASM)/,$(SOURCES))

OBJS	=	$(addprefix $(DIR_O)/,$(SRCS:.c=.o))

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

LIB_PATH=	libft

LIB		=	$(LIB_PATH)/libft.a

HDR		=	$(DIR_H)/lem_in.h

RM		=	rm -rf

CLEAN	=	clean

all:		$(NAME_ASM)

$(LIB):
			@make -C $(LIB_PATH)

$(NAME_ASM):	$(LIB) $(OBJS) $(HDR) Makefile
			@$(CC) $(CFLAGS) -I$(DIR_H) -o $(NAME_ASM) $(SRCS) $(LIB)
			@echo "Corewar	: asm file has been successfully created."

$(DIR_O)/%.o: %.c
			@mkdir -p temporary
			@mkdir -p temporary/asm
			@mkdir -p temporary/asm/src
			@$(CC) $(CFLAGS) -I$(DIR_H) -o $@ -c $<

clean:	
			@$(RM) $(DIR_O)
			@make clean -C $(LIB_PATH)
			@echo "Corewar	: *.o files have been deleted."

fclean:		clean
			@$(RM) $(NAME_ASM)
			@make fclean -C $(LIB_PATH)
			@echo "Corewar	: asm file has been deleted."

re:			fclean all

.PHONY: all clean fclean re
