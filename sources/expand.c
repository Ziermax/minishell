/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:19:13 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/11 22:02:13 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

static char	**expand_asterisk_aux(char *string, void *null)
{
	char	**expansion;

	(void)null;
	expansion = expand_asterisk(string);
	if (!expansion)
		return (NULL);
	if (ft_isasterisk(string) && *expansion)
		return (expansion);
	free_split(expansion);
	string = remove_slash(string, "");
	if (!string)
		return (NULL);
	expansion = add_dir(NULL, string);
	if (!expansion)
		return (NULL);
	return (expansion);
}

char	**expand_string(char *string, void *data)
{
	char	**expansion;
	char	**aux;

	string = remove_slash(string, "\\\"'* ");
	if (!string)
		return (NULL);
	aux = expand_envvar(string, data);
	free(string);
	if (!aux)
		return (NULL);
	expansion = split_for_each(aux, remove_quotes_string);
	free_split(aux);
	if (!expansion)
		return (NULL);
	aux = ultra_split_for_each_aux(expansion, NULL, expand_asterisk_aux);
	free_split(expansion);
	if (!aux)
		return (NULL);
	expansion = split_for_each_aux(aux, "", remove_slash);
	free_split(aux);
	return (expansion);
}

char	**expand_split(char **split_string, t_data *data)
{
	char	**expansion;

	expansion = ultra_split_for_each_aux(split_string, data, expand_string);
	free_split(split_string);
	if (!expansion)
		return (NULL);
	return (expansion);
}
/*
int	main(int argc, char **argv, char **envp)
{
	char	**expansion;
	char	*str;
	char	*tmp;
	t_data	data;
	int		i;

	if (argc > 2)
		return (1);
	if (argc == 1)
		str = "'$USER'\"$USER.HOla Mundo\"\\$USER\\\"";
	else
		str = argv[1];
	data.exit_status = 123;
	data.envp = envp;
	printf("Expanding this:\n%s\n", str);
	expansion = expand_string(str, &data);
	if (!expansion)
		return (2);
	printf("Result:\n");
	print_split(expansion);
	free_split(expansion);
}*/
//	i = -1;
//	aux = NULL;
//	while (expansion[++i])
//	{
//		if (!ft_isonly_asterisk(expansion[i]))
//		{
//			tmp = remove_slash(expansion[i], "");
//			if (!tmp)
//				return (free_split(expansion), NULL);
//			aux = add_dir(aux, tmp);
//			if (!aux)
//				return (free(tmp), free_split(expansion), NULL);
//			continue ;
//		}
//		tmp = expand_asterisk(expansion[i]);
//		if (!tmp)
//			return (free_split(expansion), NULL);
//		if (!*tmp)
//		{
//			free(tmp);
//			tmp = remove_slash(expansion[i], "");
//			if (!tmp)
//				return (free_split(expansion), NULL);
//			aux = add_dir(aux, tmp);
//			if (!aux)
//				return (free(tmp), free_split(expansion), NULL);
//			continue ;
//		}
//		aux = add_array_to_array(aux, tmp, NULL);
//		if (!aux)
//			return (free_split(tmp), free_split(expansion), NULL);
//		free(tmp);
//	}
//	return (expansion);
