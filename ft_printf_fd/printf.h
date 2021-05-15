/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:22:46 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 13:08:27 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_con
{
	int					fd;
	int					flag_checker2;
	int					flag_checker;
	int					integer;
	int					char_count;
	int					count;
	int					flag1;
	int					flag2;
	int					width1;
	int					width2;
	unsigned long int	address;
	void				*pointer;
	char				c;
	char				*string;
	char				*str;
	char				conversion;
}						t_con;

void					ft_putchar_3(char c, t_con *con);
void					ft_p_conversion2(t_con *con, int strlen);
void					ft_s_con6(t_con *con, int strlen);
void					ft_s_conversion2(t_con *con, int strlen, int mark);
void					ft_p_6(t_con *con, int strlen);
void					ft_s_con(t_con *con);
void					ft_s_con2(t_con *con, int strlen);
void					ft_s_con3(t_con *con, int strlen);
void					ft_s_con4(t_con *con, int strlen);
void					ft_s_con5(t_con *con);
void					ft_putstr_len(char *s, t_con *con, int len);
void					ft_p(t_con *con);
void					ft_p_2(t_con *con, int strlen);
void					ft_p_3(t_con *con, int strlen);
void					ft_p_4(t_con *con, int strlen);
void					ft_p_5(t_con *con, int strlen);
void					ft_p_conversion(t_con *con, va_list valist);
void					ft_s_conversion(t_con *con, va_list valist);
char					*ft_itoa_for_p(unsigned long int n);
void					ft_strdup_xudi(t_con *con);
void					ft_strdup_xudi2(t_con *con);
void					ft_strdup_for_c2(t_con *con);
void					ft_strdup_for_c(t_con *con);
void					ft_c_conversion(t_con *con, va_list valist);
void					ft_c_width1(t_con *con);
char					*ft_strdup_3(char *s);
char					*ft_itoa_u(unsigned int n);
int						ft_words(int n);
int						ft_counter(unsigned long int n, unsigned long int size);
char					*ft_itoa_x(unsigned int n, int count);
void					ft_x_conversion(t_con *con, va_list valist);
char					ft_check_conversion(char *str);
int						ft_printf_fd(int fd, const char *format, ...);
void					ft_i_d_conversion(t_con *con, va_list valist);
void					ft_check(va_list valist, t_con *con);
void					ft_add_cons(t_con *con, va_list valist);
void					ft_while(t_con *con, va_list valist);
char					*ft_itoa_d(int n);
int						ft_check_flag(char *str);
void					ft_check_mike_count(t_con *con);
void					ft_check_width1(t_con *con, va_list valist);
void					ft_check_width2(t_con *con, va_list valist);
int						ft_check_true2(char *str);
int						ft_atoi_3(t_con *con);
void					ft_zero(int a, t_con *con);
void					ft_space(int b, t_con *con);
void					ft_putstr_3(char *s, t_con *con);
int						ft_strlen_3(char *s);
void					ft_con_width1_vol2(t_con *con, int strlen, int mark);
void					ft_con_width1(t_con *con, int strlen, int mark);
void					ft_con_width1andwidth2(t_con *con,
							int strlen, int mark);
void					ft_con_width1andwidth2_vol2(t_con *con,
							int strlen, int mark);
void					ft_con_width1andwidth2_vol3(t_con *con,
							int strlen, int mark);
void					ft_con_width1andwidth2_vol5(t_con *con,
							int strlen, int mark);

#endif
