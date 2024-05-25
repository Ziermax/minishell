/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:39:27 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/04 16:34:14 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	get_linefd_to_lst(int fd, t_line **lst, int *buffsize)
{
	t_line	*node;
	int		rd;
	int		nl_found;

	rd = BUFFER_SIZE;
	nl_found = get_new_line_info(*lst, buffsize, BUFFER_SIZE);
	while (rd == BUFFER_SIZE && !nl_found)
	{
		node = get_bigger_lst(lst);
		if (!node)
			return ;
		rd = read(fd, node->chunk, BUFFER_SIZE);
		if (rd < 0)
			return (get_free_lst(lst, FREE_ALL));
		if (rd == 0)
			return (get_last_deleted(lst));
		nl_found = get_new_line_info(node, buffsize, rd);
	}
}

void	get_lst_to_line(t_line *lst, char *line, int buffsize)
{
	int	i;
	int	i_line;

	i_line = 0;
	while (lst)
	{
		i = 0;
		while (lst->chunk[i] && i < BUFFER_SIZE && i_line < buffsize)
		{
			line[i_line++] = lst->chunk[i];
			if (lst->chunk[i++] == '\n')
				break ;
		}
		lst = lst->next;
	}
	line[i_line] = '\0';
}

char	*get_next_line(int fd)
{
	static t_line	*lst_line;
	char			*line;
	int				buffsize;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffsize = 0;
	get_linefd_to_lst(fd, &lst_line, &buffsize);
	if (!lst_line)
		return (NULL);
	line = malloc(sizeof(char) * (buffsize + 1));
	if (!line)
		return (get_free_lst(&lst_line, FREE_ALL), NULL);
	get_lst_to_line(lst_line, line, buffsize);
	get_free_lst(&lst_line, KEEP_LAST);
	return (line);
}
/*
int	main(int argc, char **argv)
{
	char	*text;
	int		fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	text = (void *)1;
	printf("Text\n\"");
	while (text)
	{
		text = get_next_line(fd);
		if (!text)
			break ;
		printf("%s", text);
		free(text);
	}
	printf("\"\n");
	close(fd);
}*/
