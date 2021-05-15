#include "checker.h"

void	ft_default_stack(char **argv, t_all *t, t_v *v)
{
	int i;
	int j;
	long nbr;

	i = 0;
	j = -1;
	while (argv[++i])
	{
		if (!ft_isnumber(argv[i], v, t))
			exit(ft_fail("Error", 3, t, v));
		nbr = ft_atoi(argv[i]);
		t->stack_a[++j] = nbr;
	}
}

void	ft_init(t_all *t, t_v *v)
{
	t->stack_a = (int *)malloc(sizeof(int) * t->a);
	if (!t->stack_a)
		exit(ft_fail("couldn't allocate that much space", 0, t, v));
	t->stack_b = (int *)malloc(sizeof(int) * t->a);
	if (!t->stack_b)
		exit(ft_fail("couldn't allocate that much space", 1, t, v));
}

int	ft_success(char *s, t_all *t)
{
	free(t->stack_a);
	free(t->stack_b);
	ft_printf_fd(1, "%s\n", s);
	return (0);
}

int	main(int argc, char **argv)
{
	int mark;
	t_all t;
	t_v *v;

	if (argc < 2)
		return (1);
	t.a = argc - 1;
	t.b = 0;
	v = ft_lstnew(NULL);
	ft_init(&t, v);
	ft_default_stack(argv, &t, v);
	mark = 0;
	ft_instructions(v, &t);
	ft_print_v(v, &t);
	mark = ft_check_stacks(&t); 
	ft_lstclear(&v, ft_memdel);
	if (mark == 1)
		return (ft_fail("KO", 2, &t, v));
	return (ft_success("OK", &t));
}
