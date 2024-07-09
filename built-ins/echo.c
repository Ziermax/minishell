/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:37:43 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/09 12:46:32 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"

static int	print_echo(char **argv, int newline)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		fd_printf(1, "%s", argv[i]);
		i++;
		if (argv[i])
			fd_printf(1, " ");
	}
	if (newline)
		fd_printf(1, "\n");
	return (0);
}

static int	check_newline(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i] == 'n')
			i++;
		if (str[i])
			return (1);
		return (0);
	}
	else
		return (1);
}

int	ft_echo(char **argv, t_data *data)
{
	int	newline;

	argv++;
	newline = check_newline(*argv);
	if (!newline)
		argv++;
	return (print_echo(argv, newline));
}
