/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:02:52 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/27 12:26:16 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_dir(unsigned long p, t_flag *flag)
{
	f->width -= 2;
	ft_putnbr(p, 16, flag);
}

void	ft_di(int n, t_flag *flag)
{
	long int	aux;

	aux = (long int)n;
	if (aux >= INT_MIN && aux <= INT_MAX)
	{
		if (aux < 0)
		{
			var->sign = '-';
			var->space = 0;
			aux = -aux;
		}
		ft_putnbr((unsigned long)aux, 10, flag);
	}
}

void	ft_u(unsigned int n, t_flag *flag)
{
	ft_putnbr((unsigned long)n, 10, flag);
}

void	ft_xx(unsigned int n, t_flag *flag)
{
	if (n == 0)
		flag->alter = 0;
	if (flag->alter)
		flag->width -= 2;
	ft_putnbr((unsigned long)n, 16, flag);
}
