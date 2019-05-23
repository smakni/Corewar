/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <jergauth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:39:54 by jergauth          #+#    #+#             */
/*   Updated: 2019/05/23 19:48:16 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdarg.h>

# define BUFF_SIZE	32
# define IDENTICAL	0
# define ALL_FLAGS	"Llh+- .#0123456789,*"
# define ALL_CONV	"cspdiouxXbf%"
# define REDIRECT	"DIOU"
# define INT_CONV	"di"
# define UINT_CONV	"ouxXb"
# define BASE_CONV	"oxXb"
# define CHAR_CONV	"cs%"
# define SEPARABLES	"iduf"
# define RESET		"\033[0m"
# define BOLD		"\033[1m"
# define ITALIC		"\033[3m"
# define UNDERLINE	"\033[4m"
# define REVERSE	"\033[7m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define BG_BLACK	"\033[40m"
# define BG_RED		"\033[41m"
# define BG_GREEN	"\033[42m"
# define BG_YELLOW	"\033[43m"
# define BG_BLUE	"\033[44m"
# define BG_MAGENTA	"\033[45m"
# define BG_CYAN	"\033[46m"
# define BG_WHITE	"\033[47m"
# define CLEAR		"\e[1;1H\e[2J"

typedef struct		s_buf
{
	void			*str;
	size_t			len;
}					t_buf;

typedef struct		s_flags
{
	int				prc;
	int				pad;
	char			c;
	unsigned short	hh	: 1;
	unsigned short	h	: 1;
	unsigned short	l	: 1;
	unsigned short	ll	: 1;
	unsigned short	lm	: 1;
	unsigned short	dz	: 1;
	unsigned short	f0	: 1;
	unsigned short	mo	: 1;
	unsigned short	pl	: 1;
	unsigned short	sp	: 1;
	unsigned short	com	: 1;
	unsigned short	base: 5;
}					t_flags;

typedef enum		e_bool
{
	false = 0,
	true = 1
}					t_bool;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_stack
{
	struct s_stack	*next;
	int				nb;
}					t_stack;

typedef struct		s_file
{
	struct s_file	*next;
	char			*str;
	int				fd;
}					t_file;

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*data;
	int				height;
}					t_btree;

size_t				ft_strlen(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isoperator(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strcpy(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strncpy(char *dest, const char *src, size_t n);
size_t				ft_strspn(const char *s, const char *accept);
void				ft_bzero(void *s, size_t n);
char				*ft_strcdup(const char *str, const char limit);
char				*ft_arrjoin(const char **arr, const int glue);

/*
**	Memory functions
*/

void				*ft_memset(void *str, int c, size_t n);
void				*ft_memcpy(void *str1, const void *str2, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_memjoin(const void *first, size_t size_f,
						const void *second, size_t size_s);
void				*ft_memjoin_free(void *first, size_t size_f, void *second,
						size_t size_s);

char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
char				*ft_itoa(int n);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
**	Linked lists
*/

t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstnew_addr(void *content);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstadd_back(t_list **head, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstpop(t_list **head);

/*
**	Stack
*/

t_stack				*ft_stack_new(int nb);
void				ft_stack_del(t_stack **head);
void				ft_stack_pop(t_stack **head, int nb);
void				ft_stack_push_front(t_stack **head, t_stack *new);
void				ft_stack_push_back(t_stack **head, t_stack *new);
void				ft_stack_swap_top(t_stack **head);
void				ft_stack_rotate(t_stack **head);
void				ft_stack_rev_rotate(t_stack **head);
void				ft_stack_print(t_stack *current);
unsigned int		ft_stack_find(t_stack *head, int nb_ref);
int					ft_stack_min(t_stack *head);
int					ft_stack_nmin(t_stack *head, unsigned int limit);
int					ft_stack_max(t_stack *head);
int					ft_stack_nmax(t_stack *head, unsigned int limit);
int					ft_stack_at(t_stack *head, unsigned int index);
unsigned int		ft_stack_size(t_stack *head);
t_stack				*ft_stack_duplicate(t_stack *origin);
int					ft_stack_is_sort(t_stack *head, int rev);
int					ft_stack_is_nsort(t_stack *head, unsigned int limit,
						int rev);
int					ft_stack_cmp(t_stack *head, int data_ref,
						int (*f)(int, int));
int					ft_stack_ncmp(t_stack *head, int data_ref,
						int (*f)(int, int), unsigned int limit);
long				ft_stack_sum(t_stack *head);
long				ft_stack_nsum(t_stack *head, unsigned int limit);
t_stack				*ft_stack_node_at(t_stack *head, unsigned int index);
void				ft_stack_remove(t_stack **head, const unsigned int index);

/*
**	BINARY TREES - AVL IMPLEMENTATION
*/

t_btree				*btree_create_node(void *data);
int					btree_insert_data(t_btree **root, void *x,
						int (*cmpf)(const void *, const void *));
int					btree_height(t_btree *root);
int					btree_balance_factor(t_btree *root);
void				btree_rotate_right(t_btree **root);
void				btree_rotate_left(t_btree **root);
void				btree_apply_prefix_lr(t_btree *root,
						void (*applyf)(void *));
void				btree_apply_prefix_rl(t_btree *root,
						void (*applyf)(void *));
void				btree_apply_infix_lr(t_btree *root,
						void (*applyf)(void *));
void				btree_apply_infix_rl(t_btree *root,
						void (*applyf)(void *));
void				btree_apply_postfix_lr(t_btree *root,
						void (*applyf)(void *));
void				btree_apply_postfix_rl(t_btree *root,
						void (*applyf)(void *));
void				btree_remove_node(t_btree *node);
void				*btree_search_data(t_btree *root, void *data_ref,
						int (*cmpf)(const void *, const void *));
int					btree_level_count(t_btree *root);
void				btree_del(t_btree **root, int data_is_malloc);

int					ft_isblank(int c);
int					ft_iscntrl(int c);
int					ft_isgraph(int c);
int					ft_islower(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
int					ft_isxdigit(int c);
int					ft_str_is_alpha(const char *str);
int					ft_str_is_lowercase(const char *str);
int					ft_str_is_numeric(const char *str);
int					ft_str_is_printable(const char *str);
int					ft_str_is_uppercase(const char *str);
char				*ft_strcapitalize(char *s);
char				*ft_strlowcase(char *str);
char				*ft_strupcase(char *s);
int					ft_strcasecmp(const char *s1, const char *s2);
int					ft_strncasecmp(const char *s1, const char *s2, size_t n);
char				*ft_strcasestr(const char *s1, const char *s2);
char				*ft_strndup(const char *s, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
void				ft_printtab(char **tab);
void				ft_strrev(char *s);
int					get_next_line(const int fd, char **line, int *eol);
void				print_bits(unsigned char c);
void				ft_putchar_err(char c);
void				ft_putstr_err(char *str);
void				ft_putendl_err(char *str);
void				ft_swap(int *a, int *b);
char				*ft_itoa_base(int nb, int base);
int					*ft_range(int start, int end);
void				putnbr_base(int n, int base);
char				*ft_uitoa_base(unsigned int nb, int base);
void				putunbr_base(unsigned int n, unsigned int base);
void				putlnbr_base(long n, short base);
void				putulnbr_base(unsigned long n, unsigned int base);
void				putllnbr_base(long long n, short base);
void				putullnbr_base(unsigned long long n, unsigned int base);
int					ft_atoi_base(const char *str, int base);
long				ft_atol_base(const char *str, int base);
void				ft_putdouble(double d, unsigned short precision);
char				*ft_dtoa(double d, unsigned short precision);
char				*ft_ldtoa(long double d, unsigned short precision);
char				*ft_ltoa_base(long nb, short base);
char				*ft_ultoa_base(unsigned long nb, short base);
char				*ft_lltoa_base(long long nb, short base);
char				*ft_ulltoa_base(unsigned long long nb, short base);
int					ft_abs(int nb);
int					brackets(char *str);
int					cycle_detector(const t_list *list);
void				ft_tabdel(void **tab, size_t size);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strpbrk(const char *s, const char *accept);
int					ft_instr(const char c, const char *accept);
char				*ft_strncpy_safe(char *dest, const char *src, size_t n);
double				ft_pow_ten(double nb, int power);
char				*ft_dtoa_concat(char *s, long l, int sign);
char				*ft_ldtoa_concat(char *s, long long l, int sign);
size_t				ft_arrlen(void **arr);
int					ft_nb_is_lower(int nb, int ref);

/*
**	FT_PRINTF
*/

int					ft_printf(const char *format, ...);
int					ft_sprintf(char *str, const char *format, ...);
int					ft_snprintf(char *s, size_t size, const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_vprintf(const char *format, va_list ap);
int					ft_vsprintf(char *s, const char *format, va_list ap);
int					ft_vsnprintf(char *s, size_t size, const char *format,
						va_list ap);
int					ft_vdprintf(int fd, const char *format, va_list ap);
t_buf				*init_buf(void);
t_flags				*init_flags(void);
void				add_flag(const char c, t_flags *fl);
int					parse_format(const char **format, t_buf *buf);
int					parse_flags(const char **format, t_buf *buf, va_list ap);
int					ft_parse_color(const char **format, t_buf *buf);
void				redirection_conversion(t_flags *fl);
int					conversion(t_flags *fl, t_buf *buf, va_list ap);
int					ft_conv_numeric(t_flags *fl, t_buf *buf, va_list ap);
int					ft_conv_double(t_flags *fl, t_buf *buf, va_list ap);
int					ft_conv_str(t_flags *fl, t_buf *buf, va_list ap);
int					ft_conv_ptr(t_flags *fl, t_buf *buf, va_list ap);
int					ft_format_flag(t_flags *fl, char **conv);
int					ft_format_prc(t_flags *fl, char **conv, int *len);
int					ft_zero_value_numeric_conv_zero_prc(t_flags *fl,
						char **conv);
int					ft_format_plus_space(t_flags *fl, char **conv, int sign);
int					compute_padding_len(t_flags *fl, int len, int sign);
int					ft_format_padding(t_flags *fl, char **conv, int len,
						int sign);
int					ft_format_diese(t_flags *fl, char **conv);
int					ft_format_char(t_flags *fl, t_buf *buf, unsigned char c);
int					ft_format_str(t_flags *fl, char **conv, int len,
						t_buf *buf);
int					dieze_position(t_flags *fl, char **conv, int len, int sign);
int					plus_position(t_flags *fl, char **conv, int len, int sign);
int					format_sign(t_flags *fl, char **conv, int len, int sign);
int					format_no_sign(t_flags *fl, char **conv, int len, int sign);
int					ft_format_comma(t_flags *fl, char **conv);

#endif
