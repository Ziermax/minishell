/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:03:04 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/25 18:05:59 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_type(va_list lst, t_flag *f)
{
	if (f->type == '%')
		ft_putchar('%', f);
	else if (f->type == 'c')
		ft_putchar(va_arg(lst, int), f);
	else if (f->type == 's')
		ft_putstr(va_arg(lst, char *), f);
	else if (f->type == 'p')
		ft_dir(va_arg(lst, unsigned long), f);
	else if (f->type == 'd' || c == 'i')
		ft_di(va_arg(lst, int), f);
	else if (f->type == 'u')
		ft_u(va_arg(lst, unsigned int), f);
	else if (f->type == 'x' || c == 'X')
		ft_xx(va_arg(lst, unsigned int), f);
	else if (f->type)
		ft_putchar(f->type, f);
}

static void	ft_read(va_list lst, char *s, t_flag *f)
{
	while (*s && !f->error)
	{
		if (*s == '%')
		{
			get_flags(&s, f);
			f->type = *s;
			ft_type(lst, f);
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
	t_flag	f;

	if (!s)
		return (-1);
	f = init_struct();
	va_start(lst, s);
	ft_read(lst, s, &f);
	va_end(lst);
	if (f.error)
		return (-1);
	return (f.length);
}
