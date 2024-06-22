/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:28:05 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/21 23:41:32 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"
#include <stdio.h>

int	ft_istoken(int c)
{
	return (c == '<' || c == '>'
		|| c == '|' || c == '(' || c == ')');
}
// || c == '&'

t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->string = NULL;
	token->expanded = NULL;
	token->next = NULL;
	token->type = 0;
	return (token);
}
//	token->to_expand = 1;

void	del_token(void *token)
{
	t_token	*aux;

	aux = token;
	free(aux->string);
	free(aux->expanded);
}

void	print_token(void *token)
{
	t_token	*aux;

	aux = token;
	printf("TOKEN [%p]:\n", aux);
	printf("| string: _%s_\n", aux->string);
	printf("| expanded: _%s_\n", aux->expanded);
	if (aux->type)
		printf("| type: '%c'\n", aux->type);
	else
		printf("| type: %d\n", aux->type);
	printf("| next: [%p]\n", aux->next);
}
