NAME1	=	asm

SOURCES	=	main.c\
			mem_init.c
			ft_strccmp.c\
			encode_sti.c\
			encode_param.c\
			encode_cmd.c\
			memorize_label.c\

DIR_ASM	=	asm

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

all:		$(NAME)

$(LIB):
			@make -C $(LIB_PATH)

$(NAME):	$(LIB) $(OBJS) $(HDR) Makefile
			@$(CC) $(CFLAGS) -I$(DIR_H) -o $(NAME) $(SRCS) $(LIB)
			@echo "Lem-in		: lem-in file has been successfully created."

$(DIR_O)/%.o: %.c
			@mkdir -p temporary
			@mkdir -p temporary/srcs
			@$(CC) $(CFLAGS) -I$(DIR_H) -o $@ -c $<

clean:	
			@$(RM) $(DIR_O)
			@make clean -C $(LIB_PATH)
			@echo "Lem-in		: *.o files have been deleted."

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C $(LIB_PATH)
			@echo "Lem-in		: lem-in file has been deleted."

re:			fclean all

.PHONY: all clean fclean re
