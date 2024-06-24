/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:21:15 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/24 17:56:05 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built.h"

static int	update_pwd(char ***env, const char *path)
{
	int		oldpwd_idx;
	int		pwd_idx;
	char	*new;

	pwd_idx = get_index_var(*env, "PWD=");
	oldpwd_idx = get_index_var(*env, "OLDPWD=");
	if (pwd_idx == -1 || oldpwd_idx == -1)
		return (1);
	new = ft_strjoin("OLD", (*env)[pwd_idx]);
	if (!new)
		return (1);
	free((*env)[oldpwd_idx]);
	(*env)[oldpwd_idx] = new;
	new = ft_strjoin("PWD=", (char *)path);
	if (!new)
		return (1);
	free((*env)[pwd_idx]);
	(*env)[pwd_idx] = new;
	return (0);
}

static int	make_cd(t_data *data, const char *path)
{
	if (!ft_strcmp((char *)path, ".") && !getcwd(NULL, 0))
        fd_printf(1, "cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n", strerror(errno));
	if (chdir(path) == -1)
	{
		fd_printf(1, "cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	if (update_pwd(&(data->env), path) == -1)
		return (1);
	if (update_pwd(&(data->exp), path) == -1)
		return (1);
	return (0);
}

int	ft_cd(t_data *data, char **input)
{
	input++;
	if (get_size(input) != 1)
	{
		fd_printf(1, "cd: too many arguments\n");
		return (1);
	}
	if (!input || !(*input) || !(*input)[0])
		return (make_cd(data, ft_strdup(getenv("HOME"))) > 0);
	return (make_cd(data, *input) > 0);
}
