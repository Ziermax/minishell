/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:03:04 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/03 16:45:55 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static int	fd_putmem(int fd, unsigned long mem)
{
	if (mem >= 16)
	{
		if (fd_putmem(fd, mem / 16) == -1)
			return (-1);
		return (fd_putmem(fd, mem % 16));
	}
	else if (mem > 9)
		return (fd_putchar(fd, mem % 10 + 'a'));
	return (fd_putchar(fd, mem + '0'));
}

static int	fd_putchex(int fd, unsigned int hex)
{
	if (hex >= 16)
	{
		if (fd_putchex(fd, hex / 16) == -1)
			return (-1);
		return (fd_putchex(fd, hex % 16));
	}
	else if (hex > 9)
		return (fd_putchar(fd, hex % 10 + 'A'));
	return (fd_putchar(fd, hex + '0'));
}

int	fd_printmem(int fd, unsigned long mem)
{
	if (write(fd, "0x", 2) == -1)
		return (-1);
	if (fd_putmem(fd, mem) == -1)
		return (-1);
	return (ft_lhexlen(mem));
}

int	fd_printnbr(int fd, int nbr, int n)
{
	if (n == 'd' || n == 'i')
	{
		if (fd_putnbr(fd, nbr) == -1)
			return (-1);
		return (ft_intlen(nbr));
	}
	if (fd_putunbr(fd, (unsigned int)nbr) == -1)
		return (-1);
	return (ft_untlen(nbr));
}

int	fd_printhex(int fd, unsigned int hex, int x)
{
	if (x == 'x' && fd_puthex(fd, hex) == -1)
		return (-1);
	else if (x == 'X' && fd_putchex(fd, hex) == -1)
		return (-1);
	return (ft_hexlen(hex));
}
