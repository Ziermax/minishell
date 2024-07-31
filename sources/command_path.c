/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 03:20:54 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/31 18:44:14 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../Libft/includes/libft.h"

char	*find_exec_path(char *command, char **path_split)
{
	char	*path;
	int		i;

	if (!command || !path_split)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	i = 0;
	while (path_split[i])
	{
		path = ft_threejoin(path_split[i], "/", command);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (ft_calloc(sizeof(char), 1));
}

char	**split_path_env(char **envp)
{
	char	*path;

	path = search_word_in_split("PATH=", envp, 4);
	if (!path)
		return (ft_calloc(sizeof(char *), 1));
	return (ft_split_char(&path[5], ":"));
}
