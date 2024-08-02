/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:35:11 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/02 18:09:45 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../includes/built_utils.h"
#include "../Libft/includes/libft.h"
#include <unistd.h>

static int	check_options(char *str)
{
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' && str[1])
	{
		fd_printf(2, "minishell: pwd: %s: invalid option\n", str);
		fd_printf(2, "pwd: no accept options\n", str);
		return (2);
	}
	return (0);
}

int	ft_pwd(char **argv, t_data *data)
{
	char	*cwd;

	if (argv)
	{
		argv++;
		if (check_options(*argv))
			return (2);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (fd_printf(1, "%s\n", data->pwd), 0);
	fd_printf(1, "%s\n", cwd);
	free(cwd);
	return (0);
}
