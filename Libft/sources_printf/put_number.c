/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:42 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/27 15:29:52 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static size_t	ft_nbrlen(unsigned long n, unsigned long base)
{
	size_t	len;

	len = 1;
	while (n >= base)
	{
		n /= base;
		len++;
	}
	len++;
	return (len);
}

static char	ft_num(unsigned long n, char x)
{
	char	c;

	c = NUMBR[n];
	if (x == 'X' && n >= 10)
		c -= 32;
	return (c);
}

static void	reverse(char *s)
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

void	ft_putnbr(unsigned long n, unsigned long base, t_flag *flag)
{
	int		i;
	char	*nbr;

	nbr = (char *)ft_calloc(ft_nbrlen(n, base), sizeof(char));
	if (!nbr)
	{
		flag->error = 1;
		return ;
	}
	i = 0;
	while (n >= base)
	{
		nbr[i] = ft_num(n % base, flag->type);
		n /= base;
		i++;
	}
	nbr[i] = ft_num(n, flag->type);
	reverse(nbr);
	ft_putstr_flag(nbr, flag);
	free(nbr);
}
