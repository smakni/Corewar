NAME_P1	=	asm
NAME_P2	=	corewar

ASM_PATH	=	assembleur/src/
COR_PATH	=	vm/src/

LIB_PATH	=	libft/
LIB			=	$(LIB_PATH)libft.a

HDR		=	includes/

DIR_O		=	temporary
DIR_O_P1	=	$(DIR_O)/tmp_asm/
DIR_O_P2	=	$(DIR_O)/tmp_corewar/

SOURCES_P1	=	encode_param.c\
				choose_encoding.c\
				handle_labels.c\
				parser.c\
				format_entry.c\
				encode_comment.c\
				encode_name.c\
				encode_types.c\
				encode_sti.c\
				encode_sub.c\
				encode_and.c\
				encode_or.c\
				encode_xor.c\
				encode_zjmp.c\
				encode_ldi.c\
				encode_fork.c\
				encode_lfork.c\
				encode_live.c \
				encode_ld.c\
				encode_lld.c\
				encode_lldi.c\
				encode_st.c\
				encode_add.c\
				encode_aff.c\
				encode_byte_param.c\
				parse_args.c\
				ft_strccmp.c\
				main.c\
				mem_init.c\
				memorize_label.c\
				safe_open.c\
				write_cor.c\
				encode_header.c\
				add_byte_elem.c\
				del_byte_elem.c\
				fill_addr.c\
				ft_strlen_c.c

SRCS_P1	=	$(addprefix $(ASM_PATH),$(SOURCES_P1))
OBJS_P1	=	$(addprefix $(DIR_O_P1),$(SOURCES_P1:.c=.o))

SOURCES_P2	=	main.c\
				ft_parse_argc.c\
				safe_open.c\
				write_champ.c\
				read_bytes.c\
				read_memory.c\
				type_param.c\
				decode_byte_param.c\
				exec_op.c\
				get_value.c\
				op_live.c\
				op_sti.c\
				op_ld.c\
				op_st.c\
				op_add.c\
				op_sub.c\
				op_and.c\
				op_or.c\
				op_xor.c\
				op_fork.c\
				op_zjmp.c\
				op_ldi.c\
				op_lld.c\
				op_lldi.c\
				op_lfork.c\
				op_aff.c\
				check_cycles.c\
				del_process.c\
				visu.c\
				mvback.c\
				first_visu.c\
				key_events.c\
				display_commands.c\
				print_infos.c\
				print_error.c\
				verbos.c\
				verbos_visu.c\
				write_champ_visu.c\
				read_memory_visu.c\
				protection_visu.c\
				init_color.c\
				check_args.c\
				save_op.c\
				print_memory.c\
				print_pc.c\
				check_last_live.c\
				save_params.c\
				redraw_pc.c


SRCS_P2	=	$(addprefix $(COR_PATH),$(SOURCES_P2))
OBJS_P2	=	$(addprefix $(DIR_O_P2),$(SOURCES_P2:.c=.o))

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra -g3

FFLAGS	=	-g3 -fsanitize=address

RM		=	rm -f

CLEAN	=	clean

all:	$(NAME_P1) $(NAME_P2)

$(LIB):
			@make -C $(LIB_PATH)

$(NAME_P1):	$(OBJS_P1) $(HDR)asm.h $(LIB) Makefile
				@$(CC) $(CFLAGS) -o $(NAME_P1) $(SRCS_P1) $(LIB) -I $(HDR)
				@echo "ASM	: assembleur has been successfully created."


$(NAME_P2):	$(OBJS_P2) $(HDR)vm.h $(LIB) Makefile
				@$(CC) $(CFLAGS) -o $(NAME_P2) $(SRCS_P2) $(LIB) -I $(HDR) -lncurses
				@echo "Corewar	: corewar has been successfully created."

$(DIR_O_P1)%.o: $(ASM_PATH)%.c
		@mkdir -p temporary
		@mkdir -p temporary/tmp_asm
		@$(CC) $(CFLAGS) -I $(HDR) -o $@ -c $<

$(DIR_O_P2)%.o: $(COR_PATH)%.c
		@mkdir -p temporary/tmp_corewar
		@$(CC) $(CFLAGS) -I $(HDR) -o $@ -c $<

sanitize:
			@$(CC) $(CFLAGS) $(FFLAGS) -o $(NAME_P2) $(SRCS_P2) $(LIB) -I $(HDR) -lncurses
			@echo "Corewar	: corewar in debug mode has been successfully created."

clean:
			@$(RM) $(OBJS_P1) $(OBJS_P2)
			@rm -rf $(DIR_O)
			@make clean -C $(LIB_PATH)
			@echo "Corewar : All .o files have been deleted."

fclean:	clean
			@make fclean -C $(LIB_PATH)
			@$(RM) $(NAME_P1) $(NAME_P2) $(LIB)
			@echo "Corewar	: exe have been deleted."

re:	fclean all

.PHONY:	all sanitize clean fclean re
