/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:03:04 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/25 20:01:53 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_type(va_list lst, t_flag *flag)
{
	if (flag->type == '%')
		ft_putchar('%', flag);
	else if (flag->type == 'c') 
		ft_putchar(va_arg(lst, int), flag);
	else if (flag->type == 's')
		ft_putstr(va_arg(lst, char *), flag);
	else if (flag->type == 'p')
		ft_dir(va_arg(lst, unsigned long), flag);
	else if (flag->type == 'd' || c == 'i')
		ft_di(va_arg(lst, int), flag);
	else if (flag->type == 'u')
		ft_u(va_arg(lst, unsigned int), flag);
	else if (flag->type == 'x' || c == 'X')
		ft_xx(va_arg(lst, unsigned int), flag);
	else if (flag->type)
		ft_putchar(f->type, flag);
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
			ban_flags(flag);
			ft_type(lst, flag);
		}
		else
		{
			f->length++;
			if (ft_putchar(*s) == -1)
				f->error = 1;
		}
		if (*s)
			s++;
	}
}

int	ft_printf(char const *s, ...)
{
	va_list	lst;
	t_flag	flag;

	if (!s)
		return (-1);
	flag = init_struct();
	va_start(lst, s);
	ft_read(lst, (char *)s, &flag);
	va_end(lst);
	if (flag.error)
		return (-1);
	return (flag.length);
}
