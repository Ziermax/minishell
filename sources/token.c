/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:08:07 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/02 13:54:07 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*next_token(char *str)
{
	int	special;

	if (ft_istoken(*str))
	{
		special = *str;
		while (*str == special)
			str++;
		return (str);
	}
	while (*str && !ft_istoken(*str) && !ft_isspace(*str))
	{
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
	t_token	*new;
	int	i;

	i = 0;
	tokens = NULL;
	while (token_split[i])
	{
		new = create_token();
		if (!new)
			return (free_tokens(&tokens), NULL);
		new->string = token_split[i];
		add_token(&tokens, new);
		printf("token_split[%d]: \"%s\"\n", i, token_split[i]);
		i++;
	}
	tokens->state = DONE;
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

int	main(void)
{
	char	**token_split;
	int		i;
	char	*str;

	str = "()()l$USER>>i$USERnfile<&'out'f\"ile ca<>|&t \"e|g\"rep $USER\" hola|>outfile \"Holla mundo\"";
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
}
