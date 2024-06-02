/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:31:19 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/31 21:25:12 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/includes/libft.h"

# define ERROR 0
# define DONE 10

typedef struct s_token
{
	char			*string;
	char			type;
	char			to_expand;
	char			state;
	struct s_token	*next;
}	t_token;

void	minisheller(char *line);
t_token	*tokener(char *line);
t_token	*create_token(void);
int		ft_istoken(int c);
void	add_token(t_token **lst_token, t_token *token);
void	free_tokens(t_token **lst_token);

#endif
