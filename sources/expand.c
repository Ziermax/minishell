/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:29:19 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/10 18:52:47 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"

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
		if (search_word_relative(envvar, envp[i], STR_START,
				ft_strlen(envvar) - 1) && envp[i][len])
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

#include <unistd.h>
char	**expand_full(char *string)
{
	char	*expanded_vars;
	char	**expansion;
	char	**tmp;
	int		i;

	expansion = ultra_split(string, skip_spaces, next_word);
	i = -1;
	while (expansion[++i])
	{
		if (ft_isexpansible(expansion[i]))
		{
			tmp = expand_asterisk(expansion[i]);
			if (!tmp)
				return (free(expansion), NULL);
			printf("expansible: %s\n", expansion[i]);
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
	fd_printf(1, "Recived: %s\n\n", argv[1]);
	expanded = expand_token(argv[1], envp);
	if (!expanded)
		return (1);
	fd_printf(1, "Expanded like this:\n%s\n\n", expanded);
	expansion = expand_full(expanded);
	printf("expansion: %p\n\n", expansion);
	if (expansion)
	print_split(expansion);
	free(expanded);
}
