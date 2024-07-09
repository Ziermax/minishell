/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:58:59 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/08 21:02:45 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../Libft/includes/libft.h"
#include <limits.h>

static int	check_type(char *str)
{
	int				sign;
	unsigned long	num;

	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	num = 0;
	while (ft_isdigit(*str))
	{
		num = num * 10 + *(str++) - '0';
		if (num > LONG_MAX && sign == 1
			|| num > (unsigned long)LONG_MAX + 1 && sign == -1)
			return (-1);
	}
	while (ft_isspace(*str))
		str++;
	if (*str)
		return (-1);
	return ((unsigned char)(sign * num));
}

int	ft_exit(char **argv, t_data *data)
{
	int	num;

	argv++;
	fd_printf(2, "exit\n");
	data->end = 1;
	if (argv)
	{
		num = check_type(*argv);
		if (num == -1)
		{
			fd_printf(2, "minishell: exit %s, numeric "
				"argument required\n", *argv);
			return (2);
		}
		argv++;
		if (argv)
		{
			data->end = 0;
			fd_printf(2, "minishell: exit: too many arguments");
			return (1);
		}
		return (num);
	}
	return (data->exit);
}
