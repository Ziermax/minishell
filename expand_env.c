/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:53:15 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/23 16:22:33 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

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
		if (*str == '$' && ((ft_isvarchar(str[1]) && !ft_isdigit(str[1]))
				|| str[1] == '?'))
			break ;
		str++;
	}
	return (str);
}

static char	*expand_env(char *string, t_data *data)
{
	char	**splt_str;
	char	*tmp;
	int		i;

	splt_str = ultra_split(string, no_skip, next_var);
	if (!splt_str)
		return (NULL);
	i = -1;
	while (splt_str[++i])
	{
		if (splt_str[i][0] != '$' || (splt_str[i][0] &&
				!ft_isvarchar(splt_str[i][1]) && splt_str[i][1] != '?'))
			continue ;
		tmp = search_envvar(&splt_str[i][1], data);
		if (!tmp)
			return (free_split(splt_str), NULL);
		free(splt_str[i]);
		splt_str[i] = tmp;
	}
	tmp = ft_splitjoin(splt_str);
	free_split(splt_str);
	return (tmp);
}

static char	*expand_envvar(char *string, t_data *data)
{
	char	**splt_str;
	char	*tmp;
	int		i;

	splt_str = ultra_split(string, no_skip, next_string);
	if (!splt_str)
		return (NULL);
	i = -1;
	while (splt_str[++i])
	{
		if (splt_str[i][0] == '\'')
			continue ;
		tmp = expand_env(splt_str[i], data);
		if (!tmp)
			return (free_split(splt_str), NULL);
		free(splt_str[i]);
		splt_str[i] = tmp;
	}
	tmp = ft_splitjoin(splt_str);
	printf("################\nSplit String\n");
	print_split(splt_str);
	printf("Join:\"\n%s\n\"\n", tmp);
	free_split(splt_str);
	return (tmp);
}

static char	*remove_quotes(char *string)
{
	char	**splt_str;
	char	*tmp;
	int		len;
	int		i;

	splt_str = ultra_split(string, no_skip, next_string);
	if (!splt_str)
		return (NULL);
	i = -1;
	while (splt_str[++i])
	{
		if (splt_str[i][0] != '\'' && splt_str[i][0] != '\"')
			continue ;
		len = ft_strlen(splt_str[i]);
		if (splt_str[i][len - 1] == '\'' || splt_str[i][len - 1] == '\"')
			splt_str[i][len - 1] = '\0';
		tmp = ft_substr(splt_str[i], 1, len);
		if (!tmp)
			return (free_split(splt_str), NULL);
		free(splt_str[i]);
		splt_str[i] = tmp;
	}
	tmp = ft_splitjoin(splt_str);
	free_split(splt_str);
	return (tmp);
}

char	**expand_envvar_string(char *string, t_data *data)
{
	char	**splt_str;
	char	**aux;
	char	*tmp;
	int		i;

	string = expand_envvar(string, data);
	if (!string)
		return (NULL);
	splt_str = ultra_split(string, skip_spaces, next_word);
	free(string);
	if (!splt_str)
		return (NULL);
	printf("################\nNEW Split String\n");
	print_split(splt_str);
	i = -1;
	while (splt_str[++i])
	{
		if (!ft_strchr(splt_str[i], '\"')
			&& !ft_strchr(splt_str[i], '\''))
			continue ;
		tmp = remove_quotes(splt_str[i]);
		if (!tmp)
			return (free_split(splt_str), NULL);
		free(splt_str[i]);
		splt_str[i] = tmp;
	}
	printf("Ended expansion\n");
	return (splt_str);
}
//	printf("split var:\n");
//	print_split(splt_str);
//	printf("expansion of var: %s\n", string);
/*
#include <unistd.h>
#include <stdio.h>
int	main(int argc, char **argv, char **envp)
{
	char	**expansion;
	t_data	data;

	if (argc != 2)
		return (0);
	printf("########\nString to expand:\n%s\n\n", argv[1]);
	data.exit = 2147483647;
	data.envp = envp;
	expansion = expand_envvar_string(argv[1], &data);
	if (!expansion)
		return (write(2, "Error\n", 6));
	print_split(expansion);
	free_split(expansion);
}*/
