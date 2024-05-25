/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:02:52 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/25 18:07:05 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_dir(unsigned long p)
{
	int	a;

	if (write(1, "0x", 2) == -1)
		return (-1);
	a = ft_putnbr(p, 16, 'x');
	if (a == -1)
		return (-1);
	return (a + 2);
}

int	ft_di(int n)
{
	int		a;
	long	xd;

	if (n < 0)
	{
		xd = (long)n;
		xd = -xd;
		if (ft_putchar('-') == -1)
			return (-1);
		a = ft_putnbr((unsigned long)xd, 10, 'a');
		if (a == -1)
			return (-1);
		return (a + 1);
	}
	else
		return (ft_putnbr((unsigned long)n, 10, 'a'));
}

int	ft_u(unsigned int n)
{
	return (ft_putnbr((unsigned long)n, 10, 'a'));
}

int	ft_xx(unsigned int n, char x)
{
	return (ft_putnbr((unsigned long)n, 16, x));
}
