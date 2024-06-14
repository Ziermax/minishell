/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:31:19 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/14 21:13:50 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/includes/libft.h"

# define ERROR 'e'
# define DONE 8

typedef struct s_token
{
	char			*string;
	char			type;
	struct s_token	*next;
}	t_token;

bool	analize_tokens(t_token *token);
t_token	*minisheller(char *line, char **envp);
t_token	*tokener(char *line);
t_token	*create_token(void);
int		ft_istoken(int c);
void	add_token(t_token **lst_token, t_token *token);
void	free_tokens(t_token **lst_token);
void	print_tokens(t_token *token);
void	clean_tokens(t_token **lst_token, char **envp);

#endif
