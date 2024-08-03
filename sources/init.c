/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:52:25 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/02 19:01:28 by adrmarqu         ###   ########.fr       */
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

static char	*get_init_data(char **envp, char *var)
{
	int		idx;
	char	*data;

	idx = get_index_var(envp, var);
	if (idx == -1)
		return (NULL);
	data = get_value(envp[idx]);
	return (data);
}

int	init_data(t_data *data, char **envp)
{
	data->pwd = get_init_data(data->envp, "PWD");
	if (!envp)
		void_env(data);
	else
	{
		data->envp = ft_splitdup(envp);
		data->exp = ft_splitdup(envp);
		data->home = get_init_data(data->envp, "HOME");
	}
	data->exit_status = 0;
	data->end = 0;
	data->heredoc = NULL;
	if (!data->envp || !data->exp || !data->pwd || !data->home)
		return (1);
	return (0);
}
