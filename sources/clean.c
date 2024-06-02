/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:09:26 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/01 20:41:42 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isvarchar(int c)
{
	return (ft_isalpha);
}


char	*next_var(char *str)
{
	if (
}

char	*expand_string(char *string)
{
	char	**split_var;
	int		i;

	split_var = ultra_split(
}

void	expand_token(t_token *token)
{
	char	**split_string;
	char	*tmp;
	int		i;

	split_string = ultra_split(token->string, no_skip, next_string);
	if (!split_string)
		return ((void)(token->state = ERROR));
	i = 0;
	while (split_string[i])
	{
		tmp = expand_string(split_string[i]);
		if (!tmp)
			return ((void)(token->state = ERROR));
		free(split_string[i]);
		split_string[i] = tmp;
		i++;
	}
}

void	clean_tokens(t_token **lst_token)
{
	t_token	*aux;

	if (!lst_token || !*lst_token)
		return ;
	aux = *lst_token;
	while (aux)
	{
		if (!ft_istoken(aux->string[0]))
			expand_token(aux);
		if (!aux->state == ERROR)
			return (free_tokens(lst_token));
		aux = aux->next;
	}
}
