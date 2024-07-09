/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:52:25 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/09 18:37:00 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"
#include <limits.h>

static void	sort(char **s)
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

int	init_data(t_data *data, char **envp)
{
	data->envp = ft_splitdup(envp);
	data->exp = ft_splitdup(envp);
	if (!data->envp || !data->exp)
		return (1);
	sort(data->exp);
	data->exit_status = 0;
	data->end = 0;
	data->heredoc = NULL;
	return (0);
}
