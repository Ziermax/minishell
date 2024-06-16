/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:28:25 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/14 17:28:34 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static void	ft_type(va_list lst, t_flag *flag)
{
	if (flag->type == '%')
		ft_putchar_flag('%', flag);
	else if (flag->type == 'c')
		ft_putchar_flag(va_arg(lst, int), flag);
	else if (flag->type == 's')
		ft_putstr_flag(va_arg(lst, char *), flag);
	else if (flag->type == 'p')
		ft_dir(va_arg(lst, unsigned long), flag);
	else if (flag->type == 'd' || flag->type == 'i')
		ft_di(va_arg(lst, int), flag);
	else if (flag->type == 'u')
		ft_u(va_arg(lst, unsigned int), flag);
	else if (flag->type == 'x' || flag->type == 'X')
		ft_xx(va_arg(lst, unsigned int), flag);
	else if (flag->type)
		ft_putchar_flag(flag->type, flag);
}

static void	ft_read(va_list lst, char *s, t_flag *flag)
{
	while (*s && !flag->error)
	{
		if (*s == '%')
		{
			s++;
			get_flags(&s, flag);
			flag->type = *s;
			ft_type(lst, flag);
		}
		else
			ft_putchar(*s, flag);
		if (*s)
			s++;
	}
}

int	fd_printf(int fd, char const *s, ...)
{
	va_list	lst;
	t_flag	flag;

	if (!s || fd < 0 || fd > FOPEN_MAX)
		return (-1);
	flag = init_struct();
	flag.fd = fd;
	va_start(lst, s);
	ft_read(lst, (char *)s, &flag);
	va_end(lst);
	if (flag.error)
		return (-1);
	return (flag.length);
}
