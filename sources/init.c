/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:52:25 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/15 20:10:28 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built_utils.h"
#include "../includes/minishell.h"
#include <limits.h>

void	sort(char **s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[j] && s[j + 1])
		{
			if (ft_strncmp(s[j], s[j + 1], INT_MAX) > 0)
			{
				tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static char	*get_home(char **envp, char *var)
{
	int		idx;
	char	*data;
	char	*home;

	if (envp && envp[0])
	{
		idx = get_index_var(envp, var);
		if (idx == -1)
			return (NULL);
		data = ft_strdup(envp[idx]);
		if (!data)
			return (NULL);
		home = get_value(data);
		free(data);
		return (home);
	}
	return (search_for_my_home());
}

int	init_data(t_data *data, char **envp)
{
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		fd_printf(2, PRMTERR"run minishell in a valid directory, bitch\n");
		return (1);
	}
	data->home = get_home(envp, "HOME");
	if (envp && envp[0])
	{
		data->envp = ft_splitdup(envp);
		data->exp = ft_splitdup(envp);
	}
	else
		void_env(data);
	data->end = 0;
	data->heredoc = NULL;
	if (!data->envp || !data->exp || !data->home)
	{
		free(data->home);
		free(data->pwd);
		free_split(data->envp);
		free_split(data->exp);
		return (fd_printf(2, "Failed to initiate minishell\n"), 1);
	}
	return (0);
}
