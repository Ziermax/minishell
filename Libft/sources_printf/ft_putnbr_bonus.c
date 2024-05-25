/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:03:30 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/25 17:03:41 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static size_t	ft_nbrlen(unsigned long n, unsigned long base)
{
	size_t	len;

	len = 1;
	while (n >= base)
	{
		len++;
		n /= base;
	}
	len++;
	return (len);
}

char	ft_num(unsigned long n, char x)
{
	char	c;

	c = NUMBR[n];
	if (x == 'X' && n >= 10)
		c -= 32;
	return (c);
}

void	reverse(char *s)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (s[j])
		j++;
	j--;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
}

int	ft_putnbr(unsigned long n, unsigned long base, char x)
{
	int		i;
	char	*nbr;

	nbr = (char *)malloc(ft_nbrlen(n, base) * sizeof(char));
	if (!nbr)
		return (-1);
	i = 0;
	while (n >= base)
	{
		nbr[i] = ft_num(n % base, x);
		n /= base;
		i++;
	}
	nbr[i] = ft_num(n, x);
	nbr[i + 1] = '\0';
	reverse(nbr);
	i = ft_putstr(nbr);
	free(nbr);
	return (i);
}
