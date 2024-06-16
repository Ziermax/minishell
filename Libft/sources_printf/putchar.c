/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:59 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/14 17:24:27 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	ft_putchar(char c, t_flag *flag)
{
	flag->length++;
	if (write(flag->fd, &c, 1) == -1)
		flag->error = 1;
}

void	ft_putchar_flag(char c, t_flag *flag)
{
	if (!flag->minus && !flag->zero)
		ft_add_width(flag, 1, ' ');
	if (flag->zero)
		ft_add_width(flag, 1, '0');
	ft_putchar(c, flag);
	if (flag->minus)
		ft_add_width(flag, 1, ' ');
}

void	ft_putstr(char *s, t_flag *flag)
{
	int	len;

	if (!s)
	{
		len = write(flag->fd, "(null)", 6);
		if (len == -1)
		{
			flag->error = 1;
			return ;
		}
		flag->length += 6;
	}
	else
	{
		len = (int)ft_strlen(s);
		if (write(flag->fd, s, len) == -1)
			flag->error = 1;
		flag->length += len;
	}
}

static void	get_null(t_flag *flag)
{
	char		*s;

	s = ft_strdup("(null)");
	s = ft_put_flags(s, flag);
	ft_putstr(s, flag);
	if (flag->minus)
		ft_add_width(flag, (int)ft_strlen(s), ' ');
	free(s);
}

void	ft_putstr_flag(char *s, t_flag *flag)
{
	if (!s)
		get_null(flag);
	else
	{
		s = ft_put_flags(s, flag);
		ft_putstr(s, flag);
		if (flag->minus)
			ft_add_width(flag, (int)ft_strlen(s), ' ');
		if (flag->type != 's')
			free(s);
	}
}
