/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:17:23 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/22 22:25:10 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type
{
	PIPE = 1,
	AND,
	OR,
	O_PAR,
	C_PAR,
	R_IN,
	HDOC,
	R_OUT,
	APP,
	CMD,
	ARG,
	FILES,
}	t_type;

typedef struct s_anal
{
	t_type	last_type;
	char	is_cmd_assign;
	char	is_cmd_syntax;
	char	content;
	int		parenthesis;
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
	char			open_mode;
	char			*string;
}	t_file;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			connection_type;
	char			**cmd_split;
	char			*path;
	t_file			*files;
	t_token			*subcommand;
	//char			**infiles;
	//char			**outfiles;
}	t_cmd;

#endif
