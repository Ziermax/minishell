/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:00:45 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/04 16:34:43 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	get_last_chars(t_line *node, t_line **lst)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	while (node->chunk[i] && node->chunk[i] != '\n' && i < BUFFER_SIZE)
		i++;
	if (node->chunk[i] == '\n')
		i += 1;
	len = 0;
	while (node->chunk[i + len] && i < BUFFER_SIZE)
		len++;
	if (len == 0)
		return (get_free_lst(lst, FREE_ALL));
	j = 0;
	while (j < len)
		node->chunk[j++] = node->chunk[i++];
	node->chunk[j] = '\0';
}

void	get_free_lst(t_line **lst, int flag)
{
	t_line	*aux;
	t_line	*tmp;

	if (!*lst)
		return ;
	aux = *lst;
	while (aux->next)
	{
		tmp = aux->next;
		free(aux);
		aux = tmp;
	}
	if (flag == KEEP_LAST)
	{
		*lst = aux;
		get_last_chars(aux, lst);
		return ;
	}
	free(aux);
	*lst = NULL;
}

t_line	*get_bigger_lst(t_line **lst)
{
	t_line	*new;
	t_line	*aux;

	new = malloc(sizeof(t_line));
	if (!new)
		return (get_free_lst(lst, FREE_ALL), NULL);
	new->next = NULL;
	if (!*lst)
		return (*lst = new);
	aux = *lst;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
	return (new);
}

void	get_last_deleted(t_line **lst)
{
	t_line	*last;
	t_line	*before_last;

	if (!*lst)
		return ;
	last = *lst;
	if (!last->next)
	{
		free(last);
		*lst = NULL;
		return ;
	}
	while (last->next)
	{
		before_last = last;
		last = last->next;
	}
	free(last);
	before_last->next = NULL;
}

int	get_new_line_info(t_line *node, int *buffsize, int read)
{
	int	i;

	if (!node)
		return (0);
	i = 0;
	node->chunk[read] = '\0';
	while (node->chunk[i] && i < read)
	{
		if (node->chunk[i++] == '\n')
		{
			*buffsize += i;
			return (1);
		}
	}
	*buffsize += i;
	return (0);
}
/*
int	main(void)
{
	t_line	*text;

	text = malloc(sizeof(t_line));
	if (!text)
		return (write(1, "mallcofail\n", 11));
	text->chunk[0] = '\n';
	text->chunk[1] = 'o';
	text->chunk[2] = 'l';
	text->chunk[3] = 'a';
	text->chunk[4] = ' ';
	text->chunk[5] = 'm';
	text->chunk[6] = 'o';
	text->chunk[7] = 'n';
	text->chunk[8] = '\n';
	text->chunk[9] = '\0';
	printf("old_chunk: \"%s\"\n", text->chunk);
	get_last_chars(text, &text);
	if (!text)
		return (printf("No list, erased\n"));
	printf("new_chunk: \"%s\"\n", text->chunk);
}*/
