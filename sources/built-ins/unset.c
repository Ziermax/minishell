/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:50:47 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/07 19:57:33 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	del_var(char ***var, char *to_del, int index)
{
	int		i;
	int		j;
	int		len;
	char	**new;

	len = strlen(to_del);
	new = malloc(get_size(*var) * sizeof(char *));
	if (!new)
		return (1);
	i = 0;
	j = 0;
	while ((*var)[i])
	{
		if (i != index)
			new[j++] = strdup((*var)[i]);
		i++;
	}
	ft_free(var);
	*var = new;
	return (0);
}

int	ft_unset(t_data *data, char **input)
{
	int	flag;
	int	exist;

	input++;
	if (!input || !*input)
		return (0);
	flag = 0;
	while (*input)
	{
		exist = check_var(data->env, *input);
		if (exist)
			flag += del_var(&(data->env), *input, exist);
		exist = check_var(data->exp, *input);
		if (exist)
			flag += del_var(&(data->exp), *input, exist);
		input++;
	}
	return (flag);
}
