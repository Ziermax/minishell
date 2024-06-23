/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:17:23 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 04:15:43 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef enum e_type
{
	AND = 1,
	OR,
	PIPE,
	O_PAR,
	C_PAR,
	R_IN,
	R_OUT,
	HDOC,
	APP,
	CMD,
	ARG,
	FILES,
}	t_type;

typedef struct s_anal
{
	t_type	last_type;
	int		parenthesis;
	bool	is_cmd_assign;
	bool	is_cmd_syntax;
	bool	content;
}	t_anal;

typedef struct s_token
{
	struct s_token	*next;
	char			*string;
	char			*expanded;
	t_type			type;
}	t_token;

typedef struct s_files
{
	struct s_files	*next;
	char			*string;
	t_type			open_mode;
}	t_file;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			connection_type;
	char			**cmd_split;
	char			*path;
	t_file			*files;
	t_token			*subcommand;
}	t_cmd;

void	del_token(void *token);
void	del_file(void *file);
void	del_command(void *command);
void	print_token(void *token);
void	print_file(void *file);
void	print_command(void *command);

#endif
