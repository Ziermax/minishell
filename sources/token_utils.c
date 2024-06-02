/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:28:05 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/31 21:25:12 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_istoken(int c)
{
	return (c == '<' || c == '>' || c == '&'
		|| c == '|' || c == '(' || c == ')');
}

t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->string = NULL;
	token->next = NULL;
	token->type = 0;
	token->to_expand = 1;
	return (token);
}

void	add_token(t_token **lst_token, t_token *token)
{
	t_token	*aux;

	if (!lst_token || !token)
		return ;
	if (!lst_token)
	{
		*lst_token = token;
		return ;
	}
	aux = *lst_token;
	while (aux->next)
		aux = aux->next;
	aux->next = token;
}

void	free_tokens(t_token **lst_token)
{
	t_token	*aux;
	t_token	*tmp;

	if (!lst_token || !*lst_token)
		return ;
	aux = *lst_token;
	while (aux)
	{
		tmp = aux->next;
		if ((*lst_token)->state == DONE)
			free(aux->string);
		free(aux);
		aux = tmp;
	}
	*lst_token = NULL;
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("TOKEN [%p]:\n", token);
		printf("| string: \"_%s_\"\n", token->string);
		printf("| type: %d\n", token->type);
		printf("| to_expand: %d\n", token->to_expand);
		printf("| next: [%p]\n", token->next);
		token = token->next;
	}
}
