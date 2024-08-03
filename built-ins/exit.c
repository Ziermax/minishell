/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:58:59 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/02 18:43:01 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../Libft/includes/libft.h"
#include <limits.h>

static char	*delete_space(char *s)
{
	int		i;
	int		j;
	char	*str;

	if (!s || !*s)
		return (NULL);
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		str[j++] = s[i++];
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i])
	{
		free(str);
		return (NULL);
	}
	str[j] = '\0';
	return (str);
}

static int	check_type(char *str)
{
	int				sign;
	unsigned long	num;
	char			*s;

	s = delete_space(str);
	if (!s)
		return (-1);
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	num = 0;
	while (ft_isdigit(*s))
	{
		num = num * 10 + *(s++) - '0';
		if ((num > LONG_MAX && sign == 1)
			|| (num > (unsigned long)LONG_MAX + 1 && sign == -1))
			return (-1);
	}
	if (*s)
		return (-1);
	return ((unsigned char)(sign * num));
}

int	ft_exit(char **argv, t_data *data)
{
	int	num;

	if (argv)
		argv++;
	fd_printf(1, "exit\n");
	data->end = 1;
	if (argv && *argv)
	{
		num = check_type(*argv);
		if (num == -1)
		{
			fd_printf(2, "minishell: exit: %s: numeric "
				"argument required\n", *argv);
			return (2);
		}
		argv++;
		if (*argv)
		{
			data->end = 0;
			fd_printf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
		return (num);
	}
	return (data->exit_status);
}
