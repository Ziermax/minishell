/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:21:35 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/09 11:38:05 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"

int	ft_pwd(char **argv, t_data *data)
{
	char	*cwd;

	argv++;
	if (*argv && (*argv)[0] == '-')
	{
		fd_printf(2, "minishell: pwd: We are not accepting options today\n");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		fd_printf(2, "pwd: %s", strerror(errno));
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	data->exit = 0;
	argv++;
	return (0);
}
