/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:48:43 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/01 19:15:21 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built_utils.h"

int	check_mode(char **data, char *var)
{
	int		idx;
	char	*name;
	char	*value;

	name = get_var(var);
	idx = get_index_var(data, name);
	if (idx == -1)
	{
		free(name);
		return (-1);
	}
	free(name);
	value = get_value(var);
	if (!value)
		return (-2);
	free(value);
	return (idx);
}

char	*delete_plus(char *var)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(var), sizeof(char));
	if (!new)
	{
		free(var);
		return (NULL);
	}
	i = 0;
	while (var[i] != '+')
	{
		new[i] = var[i];
		i++;
	}
	j = i;
	i++;
	while (var[i])
		new[j++] = var[i++];
	return (new);
}

static void	id_error(char *s)
{
	fd_printf(2, "minishell: export: `%s': not a valid identifier\n", s);
}

int	get_type(char *var)
{
	int	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (id_error(var), -1);
	i = 0;
	while (var[i] && var[i] != '+' && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (id_error(var), -1);
		i++;
	}
	if (var[i] == '+' && var[i + 1] != '=')
		return (id_error(var), -1);
	if (var[i] == '=' && var[i + 1] == '(')
		return (4);
	if (var[i + 1] == '=' && var[i + 2] == '(')
		return (3);
	if (var[i] == '+')
		return (2);
	if (var[i] == '=')
		return (1);
	return (0);
}

char	*get_value(char *var)
{
	char	*value;
	int		i;

	if (!var)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (NULL);
	i++;
	value = ft_strdup(var + i);
	return (value);
}
