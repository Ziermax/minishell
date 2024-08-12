/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:58:43 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/12 17:29:42 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/includes/libft.h"

static char	**make_envp(char *pwd, char *var1, char *var2)
{
	char	**env;

	if (!pwd)
		return (NULL);
	env = ft_calloc(4, sizeof(char *));
	if (!env)
		return (NULL);
	env[0] = ft_strjoin("PWD=", pwd);
	env[1] = ft_strdup(var1);
	env[2] = ft_strdup(var2);
	if (!env[0] || !env[1] || !env[2])
	{
		free_split(env);
		return (NULL);
	}
	return (env);
}

void	void_env(t_data *data)
{
	data->envp = make_envp(data->pwd, "SHLVL=1", "_=/usr/bin/env");
	data->exp = make_envp(data->pwd, "SHLVL=1", "OLDPWD");
}
