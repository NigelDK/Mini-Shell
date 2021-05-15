#ifndef CHECKER_H
# define CHECKER_H

# include "../../ft_printf_fd/printf.h"
# include "../../get_next_line/get_next_line.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct		s_v
{
	char		*str;
	struct s_v	*next;
}			t_v;

typedef struct		s_all
{
	int		*stack_a;
	int		*stack_b;
	int		a;
	int		b;
}			t_all;

void	ft_memdel(char *s);
void	ft_lstclear(t_v **lst, void (*del)(char *));
void	ft_rev_rotate_both(t_all *t);
void	ft_rotate_both(t_all *t);
void	ft_swap_and_print(t_v *v, t_all *t);
void	ft_swap_both(t_all *t);
void	ft_swap_b(t_all *t);
void	ft_push_a(t_all *t);
void	ft_swap_a(t_all *t);
void	ft_rotate_a(t_all *t);
void	ft_rotate_b(t_all *t);
void	ft_rev_rotate_b(t_all *t);
void	ft_rev_rotate_a(t_all *t);
void	ft_push_b(t_all *t);
int		ft_check_stacks(t_all *t);
long	ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int c);
int		ft_isnumber(char *s, t_v *v, t_all *t);
char	*ft_strdup(char *s1);
int		ft_fail(char *s, int k, t_all *t, t_v *v);
void	ft_instructions(t_v *v, t_all *t);
void	ft_print_v(t_v *v, t_all *t);
t_v		*ft_lstnew(char *content);
void	ft_print_stacks(t_all *t);
void	ft_swapping(char *s, t_all *t);

#endif
