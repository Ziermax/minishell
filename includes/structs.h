/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:17:23 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/26 19:01:52 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include "color.h"

# define RD 0
# define WR 1
# define PROMTP "\033[1;92m➜ \033[1;36mminishell\033[1;33m > \033[0;39m"
# define PRMTERR "\033[1;91mminichell: \033[0;39m"

extern int				g_exit_status;

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

typedef enum e_built
{
	ECHO = 1,
	UNSET,
	EXPORT,
	ENV,
	CD,
	PWD,
	EXIT,
}	t_built;

typedef struct s_data
{
	char	**envp;
	char	**exp;
	char	*heredoc;
	char	*pwd;
	char	*home;
	int		exit_status;
	int		end;
	char	*arrow_color;
	char	*prompt;
}	t_data;

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
	t_cmd	*subcommand;
	int		fd_read;
	int		fd_write;
	int		fd_aux;
	int		failed;
};

typedef struct s_anal
{
	t_type	last_type;
	int		parenthesis;
	bool	is_cmd_assign;
	bool	is_cmd_syntax;
	bool	content;
	char	**path_split;
	t_cmd	*aux;

}	t_anal;

typedef struct s_executor
{
	int		pid;
	int		num_of_cmd;
	int		exit_status;
	int		error;
	int		*pids;
}	t_executor;

char	*get_type_str(t_type type);
void	del_token(void *token);
void	del_file(void *file);
void	del_command(void *command);
void	del_data(t_data *data);
void	print_token(void *token);
void	print_file(void *file);
void	print_command(void *command);

#endif
