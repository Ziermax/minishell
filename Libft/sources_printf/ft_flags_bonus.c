/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:20 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/25 18:04:34 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_flag(char c)
{
	return (c == '+' || c == '-' || c == '#' ||
		c == ' ' || c == '.' || is_digit(c));
}

static int	ft_atoi_move(char **s)
{
	int	num;

	num = 0;
	if (**s == '.')
		*s += 1;
	while (is_digit(**s))
	{
		num = num * 10 + **s - '0';
		*s += 1;
	}
	*s -= 1;
	return (num);
}

void	get_flags(char **s, t_flag *flag)
{
	reset_flags(flag);
	while (is_flag(**s))
	{
		if (**s == '-')
			flag->minus = 1;
		else if (**s == '0')
			flag->zero = 1;
		else if (**s == '.')
			flag->aim = ft_atoi_move(s);
		else if (**s == '#')
			flag->alter = 1;
		else if (**s == ' ')
			flag->space = 1;
		else if (**s == '+')
			flag->sign = '+';
		else
			flag->width = ft_atoi_move(s);
		*s += 1;
	}
}
