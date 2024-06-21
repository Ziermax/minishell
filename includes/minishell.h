/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:31:19 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/21 13:29:11 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/errno.h>
# include "../Libft/includes/libft.h"

typedef struct s_token
{
	char			*string;
	char			type;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char			**env;
	char			**exp;
}	t_data;

void				minisheller(char *line);
t_token				*tokener(char *line);
int					init_data(t_data *data, char **envp);
int					ft_free(char ***s);
char				*check_line(char *line);

#endif
