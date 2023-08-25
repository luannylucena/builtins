/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:47:34 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/25 18:37:28 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input_line;
	t_minishell	minishell;
	int			i;

	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
	minishell.envp_copy = env_duplicate(envp);
	minishell.export_list = env_duplicate(envp);
	while (1)
	{
		(void) argv;
		(void) envp;
		if (argc != 1)
			return (1);
		input_line = readline("minishell$ ");
		if (input_line == NULL)
			ctrl_d(input_line);
		char **token_args = ft_split(input_line, ' ');
		if (strcmp(token_args[0], "exit") == 0)
			ft_exit(token_args);
		if (strcmp(token_args[0], "pwd") == 0)
			ft_pwd();
		if (strcmp(token_args[0], "cd") == 0)
			ft_cd(token_args);
		if (strcmp(token_args[0], "echo") == 0)
			ft_echo(token_args);
		if (strcmp(token_args[0], "env") == 0)
			ft_env(&minishell);
		if (strcmp(token_args[0], "export") == 0)
		{
			if (token_args[1] != NULL)
				ft_export(&minishell, token_args);
			else
				ft_env(&minishell);
		}
		if (strcmp(token_args[0], "unset") == 0)
		{
			if (token_args[1] != NULL)
				ft_unset(&minishell, token_args[1]);
		}
		i = 0;
		while (token_args[i] != NULL)
		{
			free(token_args[i]);
			i++;
		}
		free(token_args);
		if (input_line)
		{
			printf("%s\n", input_line);
			if (ft_strlen(input_line) > 0)
				add_history(input_line);
			free(input_line);
		}
	}
	return (0);
}
