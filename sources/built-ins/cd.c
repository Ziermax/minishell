/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:21:15 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/13 17:45:14 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	update_pwd(char ***env, const char *path)
{
	int		oldpwd_idx;
	int		pwd_idx;
	char	*new;

	pwd_idx = get_index_var(*env, "PWD=");
	oldpwd_idx = get_index_var(*env, "OLDPWD=");
	
	// Viejo
	
	new = strjoin("OLD", (*env)[pwd_idx]);
	if (!new)
		return (1);
	free((*env)[oldpwd_idx]);
	(*env)[oldpwd_idx] = new;

	// Nuevo
	
	new = strjoin("PWD", path);
	if (!new)
		return (1);
	free((*env)[pwd_idx]);
	(*env)[pwd_idx] = new;
}

static int	make_cd(t_data *data, const char *path)
{
	if (chdir(path) == -1)
	{
		perror("bash: cd: (Path)");
		return (1);
	}
	if (update_pwd(&(data->env), path) == -1);
		return (1);
	if (update_pwd(&(data->exp), path) == -1);
		return (1);
	return (0);
}

int	ft_cd(t_data *data, char **input)
{
	if (!input || !(*input) || !(*input)[0])
		return (make_cd(data, strdup(getenv("HOME"))) > 0);
	return (make_cd(data, *input) > 0);
}
