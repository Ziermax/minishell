/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:09:26 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/22 10:41:07 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

char	*search_envvar(char *envvar, char **envp)
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

char	*expand_string(char *string, char **envp)
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
//		printf("expandString %d: %s\n", i, split_var[i]);
//		printf("tmp: %s\n", tmp);

char	*expand_token(char *token, char **envp)
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

void	clean_tokens(t_token **lst_token, char **envp)
{
	t_token	*aux;

	if (!lst_token || !*lst_token)
		return ;
	aux = *lst_token;
	while (aux)
	{
		if (!ft_istoken(aux->string[0]) && ft_strncmp(aux->string, "&&", 3))
		{
			aux->expanded = expand_token(aux->string, envp);
			if (!aux->expanded)
				return (lst_clear(lst_token, del_token));
		}
		aux = aux->next;
	}
}
/*
int	ft_isvarchar(int c)
{
	return (ft_isalpha(c) || c == '_');
}

char	*next_var2(char *str)
{
	int	is_var;

	is_var = 0;
	if (*str == '$')
		is_var = *(str++);
	if (is_var && *str == '?')
		return (str + 1);
	if (is_var && ft_isvarchar(*str))
	{
		while (ft_isvarchar(*str))
			str++;
		return (str);
	}
	while (*str)
	{
		if (*str == '$' && (ft_isvarchar(str[1]) || str[1] == '?'))
			break ;
		str++;
	}
	return (str);
}*/
/*
char	*next_var(char *str)
{
	if (*str == '$' && str[1] == '?')
		return (&str[2]);
	if (*str == '$' && ft_isvarchar(*(str + 1)))
	{
		str++;
		while (ft_isvarchar(*str))
			str++;
		return (str);
	}
	if (*str == '$')
		str++;
	while (*str && *str != '$')
	{
		if (str[1] == '$' && !ft_isvarchar(str[2]) && str[2] != '?')
			str++;
		if (*str)
			str++;
	}
	return (str);
}*/
/*
int	main(int argc, char **argv, char **envp)
{
	char	**var_split;
	int		i;
	char	*str;

	argc = argc + 1;
	argv = argv;
	envp = envp;
	str = "hola$ $?$$$$.hola=$hola.PATH=$PATH._Mundo $  USER=$USER";
//	str = "(cat)&&$$$(echo ls -l)";
	printf("str:\n%s\n\n", str);
	var_split = ultra_split(str, no_skip, next_var2);
	i = 0;
	while (var_split[i])
	{
		printf("var_split[%d]: \"%s\"\n",
			i, var_split[i]);
		if (var_split[i][0] == '$' && (ft_isvarchar(var_split[i][1])
			|| var_split[i][1] == '?'))
		{
		//	printf("ENTERED IF\nWhatsInside[%d] %c[%p] %c[%p]\n",
		//		i, var_split[i][0], var_split[i],
		//		var_split[i][1], &var_split[i][1]);
		//	printf("searching: \"%s\", %d\n",
		//		&(var_split[i][1]), var_split[i][1]);
		//	printf("EXITING IF\n\n");
			var_split[i] = search_envvar(&var_split[i][1], envp);
		}
		i++;
	}
	i = 0;
	printf("Finished searcing\n\n");
	while (var_split[i])
	{
		printf("var_split[%d]: %s\n", i, var_split[i]);
		i++;
	}
	printf("\nstr: \"%s\"\n", str);
	printf("\njoinsplit: \"%s\"\n", ft_splitjoin(var_split));
}*/
