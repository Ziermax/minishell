/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:56:20 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/07 15:11:35 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	ft_free(char **s)
{
	if (!s || !*s)
		return (1);
	while (*s)
	{
		free(*s);
		*s = NULL;
		s++;
	}
	free(s);
	s = NULL;
	return (1);
}

static int	delete_var(char ***var, char *s, int index)
{
	char	**new;
	int		i;
	int		j;

	new = calloc(get_size(*var), sizeof(char *));
	if (!new)
		return (1);
	i = 0;
	j = 0;
	while ((*var)[i])
	{
		if (i == index)
			i++;
		new[j] = strdup((*var)[i]);
		if (!new[j])
			return (ft_free(new));
		i++;
		j++;
	}
	//ft_free(*var);
	*var = new;
	return (0);
}

static int	find_var(t_data *data, char *s)
{
	int	flag;
	int	i;
	int	len;

	i = 0;
	flag = 0;
	len = strlen(s);
	while (data->env && data->env[i])
	{
		if (strncmp(data->env[i], s, len) == 0)
			flag += delete_var(&(data->env), s, i);
		i++;
	}
	i = 0;
	while (data->exp && data->exp[i])
	{
		if (strncmp(data->exp[i], s, len) == 0)
			flag += delete_var(&(data->exp), s, i);
		i++;
	}
	return (flag);
}

static void	xd(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
}

int	ft_unset(t_data *data, char **input)
{
	int	flag;

	/*
	printf("\n-------------------------\n");
	xd(data->env);
	printf("\n-------------------------\n");
	printf("\n-------------------------\n");
	xd(data->exp);
	printf("\n-------------------------\n");
	*/
	flag = 0;
	input++;
	if (!input || !(*input))
		return (0);
	while (*input)
	{
		flag += find_var(data, *input);
		input++;
	}
	/*
	
	printf("\n-------------------------\n");
	xd(data->env);
	printf("\n-------------------------\n");
	printf("\n-------------------------\n");
	xd(data->exp);
	printf("\n-------------------------\n");
	
	*/
	
	return (flag > 0);
}
