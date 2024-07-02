/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:12:34 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/02 18:11:40 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	lst_add_back(void *list, void *node)
{
	void	**aux;

	if (!list || !node)
		return ;
	if (!*(void **)list)
	{
		*(void **)list = node;
		return ;
	}
	aux = *(void **)list;
	while (*aux)
		aux = *aux;
	*aux = node;
}

void	lst_add_front(void *list, void *node)
{
	if (!list || !node)
		return ;
	lst_add_back(&node, *(void **)list);
	*(void **)list = node;
}

void	lst_clear(void *list, void (*del)(void *))
{
	void	**aux;
	void	*tmp;

	if (!list || !del)
		return ;
	aux = *(void **)list;
	while (aux)
	{
		tmp = *aux;
		del(aux);
		free(aux);
		aux = tmp;
	}
	*(void **)list = NULL;
}

void	lst_for_each(void *list, void (*func)(void *))
{
	void	**aux;

	if (!list || !func)
		return ;
	aux = list;
	while (aux)
	{
		func(aux);
		aux = *aux;
	}
}
