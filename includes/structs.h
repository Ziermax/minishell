/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:17:23 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/02 18:19:43 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef enum e_type
{
	NO_TYPE = 0,
	AND,
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

typedef struct s_data
{
	char			**env;
	char			**exp;
	int				exit;
}	t_data;

typedef struct s_anal
{
	t_type	last_type;
	int		parenthesis;
	bool	is_cmd_assign;
	bool	is_cmd_syntax;
	bool	content;
}	t_anal;

typedef struct s_token	t_token;

struct s_token
{
	t_token	*next;
	char	*string;
	char	*expanded;
	t_type	type;
};

typedef struct s_file	t_file;

struct s_file
{
	t_file	*next;
	char	*string;
	t_type	open_mode;
};

typedef struct s_cmd	t_cmd;

struct s_cmd
{
	t_cmd	*next;
	char	connection_type;
	char	**cmd_split;
	char	*path;
	char	**envp;
	t_file	*files;
	t_token	*subcommand;
	int		fd_read;
	int		fd_write;
	int		fd_aux;
};

typedef struct s_pipe	t_pipe;

struct s_pipe
{
	t_pipe	*next;
	int		end[2];
};

typedef struct s_executor
{
	int		pid;
	int		num_of_cmd;
	int		exit_status;
	t_pipe	*pipes;
	int		error;
	int		*pids;
}	t_executor;

void	del_token(void *token);
void	del_file(void *file);
void	del_command(void *command);
void	print_token(void *token);
void	print_file(void *file);
void	print_command(void *command);

#endif