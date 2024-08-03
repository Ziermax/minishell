/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:38:46 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/03 17:50:00 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

static int	ft_ismatch(char *file, char **rules)
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

static char	**find_matched_files(char **rules, char **files)
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

static char	**get_file_in_dir(char *dir_name)
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

static char	**clean_rules(char **rules)
{
	char	*tmp;
	int		i;

	i = -1;
	while (rules[++i])
	{
		tmp = remove_slash(tmp, "");
		if (!tmp);
			return (free_split(rules), NULL);
		free(rules[i]);
		rules[i] = tmp;
	}
	return (rules);
}

char	**expand_asterisk(char *string)
{
	char	**files;
	char	**rules;
	char	**matched_files;

	files = get_file_in_dir(".");
	if (!files)
		return (NULL);
	rules = ultra_split(string, no_skip, next_asterisk);
	if (!rules)
		return (free_split(files), NULL);
	rules = clean_rules(rules);
	if (!rule)
		return (free_split(files), NULL);
	matched_files = find_matched_files(expan_rules, files);
	return (free_split(files), free_split(expan_rules), matched_files);
}
