/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:03:18 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/27 12:32:55 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_putchar(char c, t_flag *flag)
{
	if (write(1, &c, 1) == -1)
		flag->error = 1;
}

void	ft_putstr(char *s, t_flag *flag)
{
	int	i;

	if (!s)
		if (write(1, "(null)", 6) == -1)
			flag->error = 1;
	i = 0;
	while (s[i])
		i++;
	return (write(1, s, i));
}
