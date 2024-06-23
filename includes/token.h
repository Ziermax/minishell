/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:10:26 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 03:28:11 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include "structs.h"

bool	analize_tokens(t_token *token);
t_type	ft_istoken(char *str);
int		ft_isvarchar(int c);
t_token	*create_token(void);
//Borrar PRINT_TOKENS
void	clean_tokens(t_token **lst_token, char **envp);
char	*next_var(char *str);
char	*find_exec_path(char *command, char **path_split);

#endif
