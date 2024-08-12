/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:58:59 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/12 17:37:50 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../Libft/includes/libft.h"
#include <limits.h>

static char	*delete_space(char *str)
{
	char	*s;
	char	*ret;
	int		i;

	if (!str || !*str)
		return (NULL);
	s = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (ft_isspace(*str))
		str++;
	if (!*str)
		return (free(s), NULL);
	i = 0;
	while (*str && !ft_isspace(*str))
		s[i++] = *(str++);
	while (ft_isspace(*str))
		str++;
	if (*str)
		return (free(s), NULL);
	s[i] = '\0';
	ret = ft_strdup(s);
	free(s);
	return (ret);
}

static int	check_type(char *str)
{
	char			*s;
	int				sign;
	int				i;
	unsigned long	num;

	s = delete_space(str);
	if (!s)
		return (-1);
	sign = 1;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign = -1;
	num = 0;
	while (ft_isdigit(s[i]))
	{
		num = num * 10 + s[i++] - '0';
		if ((num > LONG_MAX && sign == 1)
			|| (num > (unsigned long)LONG_MAX + 1 && sign == -1))
			return (free(s), -1);
	}
	if (s[i])
		return (free(s), -1);
	return (free(s), (unsigned char)(sign * num));
}

int	ft_exit(char **argv, t_data *data)
{
	int	num;

	if (argv)
		argv++;
	fd_printf(1, "exit\n");
	data->end = 1;
	if (*argv)
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
