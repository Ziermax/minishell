/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:18:41 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/04 17:02:10 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static int	fd_printstr(int fd, char *str)
{
	if (!str)
		return (write(fd, "(null)", 6));
	return (fd_putstr(fd, str));
}

static int	fd_percentge(int fd, char c, va_list ap, int *len)
{
	int	ret;

	ret = 0;
	if (c == 'c')
		ret = fd_putchar(fd, va_arg(ap, int));
	else if (c == 's')
		ret = fd_printstr(fd, va_arg(ap, char *));
	else if (c == 'p')
		ret = fd_printmem(fd, va_arg(ap, long));
	else if (c == 'd' || c == 'i' || c == 'u')
		ret = fd_printnbr(fd, va_arg(ap, int), c);
	else if (c == 'x' || c == 'X')
		ret = fd_printhex(fd, va_arg(ap, unsigned int), c);
	else if (c == '%')
		ret = fd_putchar(fd, '%');
	*len += ret;
	return (ret);
}

int	fd_printf(int fd, char *str, ...)
{
	va_list	ap;
	int		ret;
	int		i;

	ret = 0;
	va_start(ap, str);
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != '%')
			i++;
		if (write(fd, str, i) == -1)
			return (va_end(ap), -1);
		ret += i;
		str = &str[i];
		if (*str == '%' && fd_percentge(fd, *(++str), ap, &ret) == -1)
			return (va_end(ap), -1);
		if (*str)
			str++;
	}
	return (va_end(ap), ret);
}

void	error_printf(int error, char *str, ...)
{
	va_list	ap;
	int		ret;
	int		i;

	ret = 0;
	va_start(ap, str);
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != '%')
			i++;
		if (write(2, str, i) == -1)
			return (va_end(ap), exit(error));
		ret += i;
		str = &str[i];
		if (*str == '%' && fd_percentge(2, *(++str), ap, &ret) == -1)
			return (va_end(ap), exit(error));
		if (*str)
			str++;
	}
	return (va_end(ap), exit(error));
}
