/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_full.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 03:22:27 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/23 20:39:16 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"
#include <unistd.h>

char	**create_for_asterisk(char *string, int *index)
{
	char	**creation;

	creation = expand_asterisk(string);
	if (!creation)
		return (NULL);
	if (*creation)
		*index += ft_arraylen(creation) - 1;
	return (creation);
/*	char	**new;
	int		i;

	i = *index;
	new = expand_asterisk(expansion[i]);
	if (!new)
		return (free_split(expansion), NULL);
	if (!*new)
		return (free_split(new), expansion);
	expansion = add_array_to_array(expansion, new, expansion[i]);
	if (!expansion)
		return (free_split(new), NULL);
	expansion = remove_dir(expansion, expansion[i]);
	if (!expansion)
		return (free(new), NULL);
	*index += ft_arraylen(new) - 1;
	free(new);
	return (expansion);*/
}

char	**expand_full(char *string, t_data *data)
{
	char	**expansion;
	char	**tmp;
	int		i;

	expansion = expand_envvar_string(string, data);
	if (!expansion)
		return (NULL);
	i = -1;
	while (expansion[++i])
	{
		if (!ft_isexpansible(expansion[i]))
			continue ;
		expansion = expand_and_replace(expansion, &i, create_for_asterisk);
//		expansion = expand_replace_asterisk(expansion, &i);
		if (!expansion)
			return (NULL);
	}
	return (expansion);
}
	//printf("Expansion: %p\n", expansion);
	//if (expansion)
	//	printf("expansion[0]: %s\n", *expansion);
	//print_split(expansion);
//char	**expand_command(char **command, t_data *data)
//{
//	int	i;
//
//	i = -1;
//	while (command[++i])
//	{
//		if (!ft_
//	}
//}
//		tmp = expand_asterisk(expansion[i]);
//		if (!tmp)
//			return (free_split(expansion), NULL);
//		if (!*tmp)
//		{
//			free_split(tmp);
//			continue ;
//		}
//		expansion = add_array_to_array(expansion, tmp, expansion[i]);
//		if (!expansion)
//			return (free_split(tmp), NULL);
//		free(expansion[i]);
//		expansion = remove_dir(expansion, expansion[i]);
//		if (!expansion)
//			return (free_split(tmp), NULL);
//		i += ft_arraylen(tmp) - 1;
//		free(tmp);
//		printf("expan[%p]: %s\n", expansion[i], expansion[i]);

int	main(int argc, char **argv, char **envp)
{
	char	**expansion;
	t_data	data;

	if (argc != 2)
		return (0);
	data.exit = 2147483647;
	data.envp = envp;
	expansion = expand_full(argv[1], &data);
	if (!expansion)
		return (write(2, "Error\n", 6));
	print_split(expansion);
	free_split(expansion);
}
//	printf("########\nString to expand:\n%s\n\n", argv[1]);
