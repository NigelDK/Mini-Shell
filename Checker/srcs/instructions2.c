#include "checker.h"

void	ft_rotate_a(t_all *t)
{
	int count;
	int tmp;
	int i;

	i = 0;
	count = t->a - 1;
	tmp = t->stack_a[0];
	i = -1;
	while (++i < count)
		t->stack_a[i] = t->stack_a[i + 1];
	t->stack_a[i] = tmp;
}

void	ft_swap_b(t_all *t)
{
	int tmp;

	tmp = t->stack_b[0];
	t->stack_b[0] = t->stack_b[1];
	t->stack_b[1] = tmp;
}

void	ft_swap_a(t_all *t)
{
	int tmp;

	tmp = t->stack_a[0];
	t->stack_a[0] = t->stack_a[1];
	t->stack_a[1] = tmp;
}

void	ft_swap_both(t_all *t)
{
	ft_swap_a(t);
	ft_swap_b(t);
}

void	ft_rotate_both(t_all *t)
{
	ft_rotate_a(t);
	ft_rotate_b(t);
}
