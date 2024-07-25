/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:07:08 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/25 18:24:22 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include <sys/types.h>
#include <dirent.h>

int	ft_ismatch(char *file, char **rules)
{
	char	*current;
	int		len;
	int		i;

	if (*file == '.' && rules[0] && rules[0][0] != '.')
		return (0);
	if (rules[0] && rules[0][0] == '*' && !rules[1])
		return (1);
	i = -1;
	while (rules[++i])
	{
		if (rules[i][0] == '*')
			continue ;
		len = ft_strlen(rules[i]);
		if (i == 0)
			current = search_word_in_start(rules[i], file, len);
		else if (!rules[i + 1])
			current = search_word_in_end(rules[i], file);
		else
			current = search_word_in_str(rules[i], file, len);
		if (!current)
			return (0);
		file = current + len;
	}
	return (1);
}

char	**find_matched_files(char **rules, char **files)
{
	char	**matches;
	char	*tmp;
	int		i;

	i = -1;
	matches = NULL;
	while (files[++i])
	{
		if (!ft_ismatch(files[i], rules))
			continue ;
		tmp = ft_strdup(files[i]);
		if (!tmp)
			return (free_split(matches), NULL);
		matches = add_dir(matches, tmp);
		if (!matches)
			return (free(tmp), NULL);
	}
	if (!matches)
		return (ft_calloc(sizeof(char *), 1));
	return (matches);
}

char	**get_file_in_dir(char *dir_name)
{
	struct dirent	*entity;
	DIR				*directory;
	char			**dir_files;
	char			*tmp;

	directory = opendir(dir_name);
	if (!directory)
		return (ft_calloc(sizeof(char *), 1));
	entity = readdir(directory);
	dir_files = NULL;
	while (entity)
	{
		tmp = ft_strdup(entity->d_name);
		if (!tmp)
			return (free_split(dir_files), closedir(directory), NULL);
		dir_files = add_dir(dir_files, tmp);
		if (!dir_files)
			return (free(tmp), closedir(directory), NULL);
		entity = readdir(directory);
	}
	closedir(directory);
	if (!dir_files)
		return (ft_calloc(sizeof(char *), 1));
	return (dir_files);
}

char	*next_asterisk(char *str)
{
	if (!str)
		return (NULL);
	if (*str == '*')
		while (*str == '*')
			str++;
	else
	{
		while (*str && *str != '*')
		{
			if (*str == '\'' || *str == '\"')
				str = next_string(str);
			else
				str++;
		}
	}
	return (str);
}

char	**expand_asterisk(char *string)
{
	char	**rules;
	char	**files;
	void	*aux;
	int		i;

	files = get_file_in_dir(".");
	if (!files)
		return (NULL);
	rules = ultra_split(string, no_skip, next_asterisk);
	if (!rules)
		return (free_split(files), NULL);
	i = -1;
	while (rules[++i])
	{
		if (!!ft_strchr(rules[i], '\"') || !ft_strchr(rules[i], '\''))
			continue ;
		aux = rules[i]
	}
	aux = find_matched_files(rules, files);
	return (free_split(files), free_split(rules), aux);
}
