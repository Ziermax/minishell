/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:08:07 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/15 20:11:14 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

static char	*next_token(char *str)
{
	t_type	type;

	if (!str)
		return (NULL);
	type = ft_istoken(str);
	if (type >= PIPE && type <= R_OUT)
		return (str + 1);
	else if (type != 0)
		return (str + 2);
	while (*str && !ft_istoken(str) && !ft_isspace(*str))
	{
		if (*str != '\'' && *str != '\"')
			str++;
		else
			str = next_string(str);
	}
	return (str);
}

static t_token	*assing_tokens(char **token_split)
{
	t_token	*tokens;
	t_token	*aux;
	int		i;

	i = -1;
	tokens = NULL;
	while (token_split[++i])
	{
		aux = ft_calloc(sizeof(t_token), 1);
		if (!aux)
			return (lst_clear(&tokens, del_token), NULL);
		lst_add_back(&tokens, aux);
	}
	i = -1;
	aux = tokens;
	while (token_split[++i])
	{
		aux->string = token_split[i];
		aux = aux->next;
	}
	return (tokens);
}

static t_token	*tokenize(char *line)
{
	char	**token_split;
	t_token	*tokens;

	tokens = NULL;
	token_split = ultra_split(line, skip_spaces, next_token);
	if (!token_split)
		return (NULL);
	tokens = assing_tokens(token_split);
	if (!tokens)
		return (free_split(token_split), NULL);
	free(token_split);
	return (tokens);
}

t_token	*tokeinator(char *line, char **envp)
{
	t_token	*tokens;

	tokens = tokenize(line);
	if (!tokens)
		return (NULL);
	if (!analize_tokens(tokens))
		return (lst_clear(&tokens, del_token), NULL);
	if (!tokens)
		return (NULL);
	envp = envp + 1;
	return (tokens);
}
