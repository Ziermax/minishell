/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:31:13 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/04 16:32:05 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define KEEP_LAST 10
# define FREE_ALL 69
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

typedef struct s_line
{
	char			chunk[BUFFER_SIZE + 1];
	struct s_line	*next;
}	t_line;

void	get_free_lst(t_line **lst, int flag);
void	get_last_deleted(t_line **lst);
t_line	*get_bigger_lst(t_line **lst);
int		get_new_line_info(t_line *node, int *buffsize, int read);

#endif
