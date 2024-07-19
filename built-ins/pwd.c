/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:05:15 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/13 19:33:36 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../includes/built_utils.h"
#include "../Libft/includes/libft.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

char	*get_pwd(char **envp, char *path)
{
	char	*cwd;
	char	*var;
	int		idx;
	
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		var = ft_strjoin("PWD=", cwd);
		free(cwd);
	}
	else
	{
		idx = get_index_var(envp, "PWD");
		if (idx == -1)
			return (NULL);
		var = ft_threejoin(envp[idx], "/", path);
	}
	return (var);
}

int	check_options(char *str)
{
	if (!str || !str[0])
		return (0);
	if (str[0] == '-')
	{
		fd_printf(2, "pwd: options are not avaliable\n");
		return (1);
	}
	return (0);
}

int	ft_pwd(char **argv, t_data *data)
{
	char	*cwd;

	argv++;
	if (check_options(*argv))
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		fd_printf(2, "pwd: %s\n", strerror(errno));
		data->end = 0;
		return (1);
	}
	fd_printf(1, "%s\n", cwd);
	free(cwd);
	return (0);
}
