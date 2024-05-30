/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:56:20 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/30 17:19:22 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	delete_var(char *var, char **envp)
{
	int	i;
	int	len;

	len = strlen(var);
	i = 0;
	while (envp[i])
	{
		if (strncmp(var, envp[i], len) == 0)
		{
			while (envp[i] && envp[i + 1])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			return ;
		}
		i++;
	}
}

int	ft_unset(char **s, char **envp)
{
	if (!(*s))
		return (0);
	while (*s)
	{
		delete_var(*s, envp);
		s++;
	}
	return (0);
}
