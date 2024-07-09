/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@argvtudent.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:18:22 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/09 11:40:59 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"

static int	print_echo(char **argv, int newline)
{
	while (*argv)
	{
		if (fd_printf(1, "%s", *argv) == -1)
			return (1);
		argv++;
		if (*argv)
			if (fd_printf(1, " ") == -1)
				return (1);
	}
	if (newline)
		if (fd_printf(1, "\n") == -1)
			return (1);
	return (0);
}

int	ft_echo(char **argv, t_data *data)
{
	int	newline;
	int	i;

	argv++;
	newline = 1;
	if ((*argv)[0] == '-' && (*argv)[1] == 'n')
	{
		i = 1;
		while ((*argv)[i] == 'n')
			i++;
		newline = 0;
		argv++;
	}
	data->exit = print_echo(argv, newline);
	return (data->exit);
}
