/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:52:40 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 05:04:41 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"

/*	line: ">hola cat|ls -l>out&&$USER'<NOTOKEN$NOUSERninada'"
 *	sep: "> hola cat | ls -l > out && $USER '<NOTOKEN$NOUSERninada' "	*/
//	t_file	*files;
int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**path_split;
	t_cmd	*commands;
	t_token	*tokens;

	argc = argc;
	argv = argv;
	str = "h>>out<<in||hola&&hola&&&hola&& hola((hola))";
	if (argc == 1)
	{
		printf("str:\n%s\n\n", str);
		tokens = tokeinator(str, envp);
	}
	else
	{
		printf("str:\n%s\n\n", argv[1]);
		tokens = tokeinator(argv[1], envp);
	}
	lst_for_each(tokens, print_token);
	printf("\n###GETTING COMMANDS\n\n");
	path_split = split_path_env(envp);
	commands = get_command(tokens, path_split);
	lst_for_each(commands, print_command);
	lst_clear(&commands, del_command);
	free_split(path_split);
	lst_clear(&tokens, del_token);
}
/*	cmd_split = get_cmd_split(tokens);
	free_split(cmd_split);
	files = get_files(tokens);
	lst_for_each(files, print_file);
	lst_clear(&files, del_file);*/
	//str = "\"$TEST\"'$PATH' $USER$TEST $USER\"hola\"";
	//str = "    $HOLS";
