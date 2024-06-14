/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:08:07 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/13 13:06:46 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*next_special_token(char *str)
{
	int	special;
	int	count;

	if (!str)
		return (NULL);
	special = *str;
	count = 0;
	while (*str == special)
	{
		if (count == 1 && (special == ')' || special == '('))
			break ;
		if (count >= 2 && (special == '>' || special == '<' || special == '&'
				|| special == '|'))
			break ;
		str++;
		count++;
	}
	return (str);
}

char	*next_token(char *str)
{
	if (!str)
		return (NULL);
	if (ft_istoken(*str) || (*str == '&' && *(str + 1) == '&'))
		return (next_special_token(str));
	while (*str && !ft_istoken(*str) && !ft_isspace(*str))
	{
		if (*str == '&' && *(str + 1) == '&')
			break ;
		if (*str != '\'' && *str != '\"')
			str++;
		else
			str = next_string(str);
	}
	return (str);
}

t_token	*assing_tokens(char **token_split)
{
	t_token	*tokens;
	t_token	*aux;
	int		i;

	i = -1;
	tokens = NULL;
	while (token_split[++i])
	{
		aux = create_token();
		if (!aux)
			return (free_tokens(&tokens), NULL);
		add_token(&tokens, aux);
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

t_token	*tokener(char *line)
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
/*
int	main(void)
{
	char	**token_split;
	int		i;
	char	*str;

	str = "()()l$USER>>i$USERnfile<&'out'f\"ile ca<
	>|&t \"e|g\"rep $USER\" hola|>outfile \"Holla mundo\"";
//	str = "(cat)&&$$$(echo ls -l)";
	printf("str:\n%s\n\n", str);
	token_split = ultra_split(str, skip_spaces, next_token);
	i = 0;
	while (token_split[i])
	{
		printf("token_split[%d]: %s\n", i, token_split[i]);
		i++;
	}
	free_split(token_split);
}*/
