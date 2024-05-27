/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:24 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/27 17:20:49 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	ft_add_width(t_flag *flag, int len, char c)
{
	int	length;

	length = flag->width - len;
	if (length < 0)
		length = 0;
	while (length > 0)
	{
		ft_putchar(c, flag);
		length--;
	}
}

static void	*ft_add_aim_num2(char *s, char *r, t_flag *flag)
{
	int	length;
	int	i;

	i = 0;
	length = flag->aim - (int)ft_strlen(s);
	while (i < length)
	{
		r[i] = '0';
		i++;
	}
	length = (int)ft_strlen(s);
	while (length > 0)
	{
		r[i] = *s;
		i++;
		s++;
		length--;
	}
	return (r);
}

static char	*ft_add_aim_num(char *s, t_flag *flag)
{
	char	*r;
	int		length;

	if (flag->aim > (int)ft_strlen(s))
	{
		length = (int)ft_strlen(s) + flag->aim;
		r = (char *)ft_calloc(length, sizeof(char));
		if (!r)
		{
			flag->error = 1;
			return (NULL);
		}
		r = ft_add_aim_num2(s, r, flag);
		free(s);
		return (r);
	}
	return (s);
}

char	*ft_put_flags(char *s, t_flag *flag)
{
	if (flag->aim != -1)
	{
		if (flag->type == 's')
			s[flag->aim] = '\0';
		else
			s = ft_add_aim_num(s, flag);
	}
	if ((flag->sign == '+' || flag->sign == '-' || flag->space)
		&& flag->type != 's')
		flag->width--;
	if (!flag->minus && !flag->zero)
		ft_add_width(flag, (int)ft_strlen(s), ' ');
	if ((flag->sign == '+' || flag->sign == '-') && flag->type != 's')
		ft_putchar(flag->sign, flag);
	if (flag->space && flag->type != 's')
		ft_putchar(' ', flag);
	if (flag->type == 'p' || (flag->alter && flag->type == 'x'))
		ft_putstr("0x", flag);
	if (flag->alter && flag->type == 'X')
		ft_putstr("0X", flag);
	if (flag->zero)
		ft_add_width(flag, (int)ft_strlen(s), '0');
	return (s);
}
