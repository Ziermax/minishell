/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:08:07 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/28 23:58:00 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

//	static int	i;
//	printf("analizing %d: \"%s\"\n", i++, str);
//	printf("| type: %d\n", type);
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
	//clean_tokens(&tokens, envp);
	if (!tokens)
		return (NULL);
	envp = envp + 1;
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
