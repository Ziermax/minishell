/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:37:43 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/02 11:27:31 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"

static void	print_home(char *path, char *home)
{
	fd_printf(1, "%s", home);
	path++;
	if (*path)
		fd_printf(1, "%s", path);
}

static void	print_echo(char **argv, int newline, char *home)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '~' && (argv[i][1] == '/' || !argv[i][1]))
			print_home(argv[i], home);
		else
			fd_printf(1, "%s", argv[i]);
		i++;
		if (argv[i])
			fd_printf(1, " ");
	}
	if (newline)
		fd_printf(1, "\n");
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
	return (1);
}

int	ft_echo(char **argv, t_data *data)
{
	int	newline;
	int	nl;

	argv++;
	newline = check_newline(*argv);
	nl = newline;
	while (!nl)
	{
		argv++;
		nl = check_newline(*argv);
	}
	return (print_echo(argv, newline, data->home), 0);
}
