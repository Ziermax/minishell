/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:28:15 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/27 15:28:20 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	ft_dir(unsigned long p, t_flag *flag)
{
	flag->space = 0;
	flag->sign = '0';
	flag->width -= 2;
	ft_putnbr(p, 16, flag);
}

void	ft_di(int n, t_flag *flag)
{
	long int	aux;

	if (flag->aim != -1)
		flag->zero = 0;
	aux = (long int)n;
	if (aux >= INT_MIN && aux <= INT_MAX)
	{
		if (aux < 0)
		{
			flag->sign = '-';
			flag->space = 0;
			aux = -aux;
		}
		ft_putnbr((unsigned long)aux, 10, flag);
	}
}

void	ft_u(unsigned int n, t_flag *flag)
{
	flag->sign = '0';
	flag->space = 0;
	if (flag->aim != -1)
		flag->zero = 0;
	ft_putnbr((unsigned long)n, 10, flag);
}

void	ft_xx(unsigned int n, t_flag *flag)
{
	flag->space = 0;
	flag->sign = '0';
	if (flag->aim != -1)
		flag->zero = 0;
	if (n == 0)
		flag->alter = 0;
	if (flag->alter)
		flag->width -= 2;
	ft_putnbr((unsigned long)n, 16, flag);
}
