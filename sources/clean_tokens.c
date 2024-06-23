/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:09:26 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 03:35:51 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

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

void	clean_tokens(t_token **lst_token, char **envp)
{
	t_token	*aux;

	if (!lst_token || !*lst_token)
		return ;
	aux = *lst_token;
	while (aux)
	{
		if (aux->type >= CMD && aux->type <= FILES)
		{
			aux->expanded = expand_token(aux->string, envp);
			if (!aux->expanded)
				return (lst_clear(lst_token, del_token));
		}
		aux = aux->next;
	}
}
