/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:29:19 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/20 04:12:15 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

static int	ft_isvarchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*next_var(char *str)
{
	if (*str == '$'
		&& ((ft_isvarchar(str[1]) && !ft_isdigit(str[1])) || str[1] == '?'))
	{
		str++;
		if (*str == '?')
			return (str + 1);
		while (ft_isvarchar(*str))
			str++;
		return (str);
	}
	while (*str)
	{
		if (*str == '$'
			&& ((ft_isvarchar(str[1]) && !ft_isdigit(str[1])) || str[1] == '?'))
			break ;
		str++;
	}
	return (str);
}

static char	*search_envvar(char *envvar, char **envp)
{
	int	i;
	int	len;

	if (!envvar || !envp)
		return (NULL);
	if (*envvar == '?')
		return ("0");
	i = 0;
	len = ft_strlen(envvar);
	while (envp[i])
	{
		if (!ft_strncmp(envvar, envp[i], ft_strlen(envvar) - 1)
			&& envp[i][len])
			return (&envp[i][len + 1]);
		i++;
	}
	return ("");
}

static char	*expand_string(char *string, char **envp)
{
	char	**split_var;
	char	*tmp;
	int		i;

	split_var = ultra_split(string, no_skip, next_var);
	if (!split_var)
		return (NULL);
	i = -1;
	while (split_var[++i])
	{
		if (split_var[i][0] != '$')
			continue ;
		else if (!ft_isvarchar(split_var[i][1]) && split_var[i][1] != '?')
			continue ;
		tmp = ft_strdup(search_envvar(&split_var[i][1], envp));
		if (!tmp)
			return (free_split(split_var), NULL);
		free(split_var[i]);
		split_var[i] = tmp;
	}
	tmp = ft_splitjoin(split_var);
	free_split(split_var);
	return (tmp);
}

static char	*expand_token(char *token, char **envp)
{
	char	**split_string;
	char	*tmp;
	int		i;

	split_string = ultra_split(token, no_skip, next_string);
	if (!split_string)
		return (NULL);
	i = -1;
	while (split_string[++i])
	{
		if (split_string[i][0] == '\'')
			continue ;
		tmp = expand_string(split_string[i], envp);
		if (!tmp)
			return (free_split(split_string), NULL);
		free(split_string[i]);
		split_string[i] = tmp;
	}
	tmp = ft_splitjoin(split_string);
	free_split(split_string);
	return (tmp);
}

int	ft_isexpansible(char *str)
{
	int	asterisk;

	if (!str)
		return (0);
	asterisk = 0;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			str = next_string(str);
			continue ;
		}
		if (*str == '*')
			asterisk = 1;
		else if (*str == '/')
			return (0);
		str++;
	}
	return (asterisk);
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
	return (closedir(directory), dir_files);
}

int	ft_ismatch(char *file, char **rules)
{
	char	*curnt;
	char	*prev;
	int		i;

	if (rules[0][0] == '*' && !rules[1] && file[0] != '.')
		return (1);
	i = -1;
	prev = NULL;
	while (rules[++i])
	{
		if (rules[i][0] == '*')
			continue ;
		printf("\n#################\nSearching this: %s in this file: %s\n",
			rules[i], file);
		if (i == 0)
		{
			curnt = search_word_in_start(rules[i], file, ft_strlen(rules[i]));
			printf("searching in START: %s\n", curnt);
		}
		else if (!rules[i + 1])
		{
			curnt = search_word_in_end(rules[i], file);
			printf("searching in END: %s\n", curnt);
		}
		else
		{
			curnt = search_word_in_str(rules[i], file, ft_strlen(rules[i]));
			printf("searching in ANY: %s\n", curnt);
		}
		if (!curnt)
		{
			printf("RETURNING 0\nprev: %p = %p curnt\n", prev, curnt);
			return (0);
		}
		prev = curnt;
		file = curnt + ft_strlen(rules[i]);
		/*if (!prev)
			curnt = search_word_relative(rules[i], file,
				STR_START, ft_strlen(rules[i]));
		else if (!rules[i + 1] || !rules[i + 2])
			curnt = search_word_relative(rules[i], file,
				STR_END, ft_strlen(rules[i]) + 1);
		else
			curnt = search_word_relative(rules[i], file,
				STR_MIDDLE, ft_strlen(rules[i]));
		//printf("Match: %s < %s\n%p - %p = %ld\n\n\n",
			//prev, curnt, prev, curnt, prev - curnt);
		if (!curnt || prev - curnt > 0)
		{
			//printf("Bad match: %s < %s\n%p - %p = %ld\n",
				//prev, curnt, prev, curnt, prev - curnt);
			return (0);
		}*/
	}
	return (1);
}

char	**find_matched_files(char **name_matches, char **files)
{
	char	**match;
	char	*tmp;
	int		i;

	i = -1;
	match = NULL;
	while (files[++i])
	{
		if (ft_ismatch(files[i], name_matches))
		{
			tmp = ft_strdup(files[i]);
			if (!tmp)
				return (free_split(match), NULL);
			match = add_dir(match, tmp);
			if (!match)
				return (free(tmp), NULL);
		}
	}
	printf("\n###########\nMATCHESSS: %p\n\n", match);
	print_split(match);
	free_split(match);
	return (NULL);
	if (!match)
		return (ft_calloc(sizeof(char *), 1));
	return (match);
}

char	**expand_asterisk(char *string)
{
	char	**expansion;
	char	**files;
	char	**matched_files;

	expansion = ultra_split(string, no_skip, next_asterisk);
	if (!expansion)
		return (NULL);
	files = get_file_in_dir(".");
	if (!files)
		return (free_split(expansion), NULL);
	printf("\n###########\nFiles: %p\n\n", expansion);
	print_split(files);
	printf("\n###########\nExpand Asterisk: %p\n\n", expansion);
	print_split(expansion);
	matched_files = find_matched_files(expansion, files);
	free_split(expansion);
	free_split(files);
	return (matched_files);
}

char	**expand_full(char *string)
{
	char	*expanded_vars;
	char	**expansion;
	char	**tmp;
	int		i;

	expansion = ultra_split(string, skip_spaces, next_word);
	i = -1;
	printf("\n###########\nExpandFull: %p\n\n", expansion);
	print_split(expansion);
	while (expansion[++i])
	{
		if (ft_isexpansible(expansion[i]))
		{
			printf("\nexpansible: %s\n", expansion[i]);
			tmp = expand_asterisk(expansion[i]);
			if (!tmp)
				return (free_split(expansion), NULL);
		}
	}
	return (expansion);
}

int	main(int argc, char **argv, char **envp)
{
	char	*expanded;
	char	**expansion;
	
	if (argc != 2)
		return (0);
	expanded = expand_token(argv[1], envp);
	printf("\n###########\nExpand token: %s\n\n", expanded);
	if (!expanded)
		return (1);
	expansion = expand_full(expanded);
	printf("\n###########\nExpansion: %p\n\n", expansion);
	print_split(expansion);
	free_split(expansion);
	free(expanded);
}
