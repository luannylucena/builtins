/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:27:49 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/30 14:52:04 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	execute_builtin(char **args, t_minishell *minishell)
// {
// 	if (strcmp(args[0], "exit") == 0)
// 		ft_exit(args);
// 	else if (strcmp(args[0], "pwd") == 0)
// 		ft_pwd();
// 	else if (strcmp(args[0], "cd") == 0)
// 		ft_cd(args);
// 	else if (strcmp(args[0], "echo") == 0)
// 		ft_echo(args);
// 	else if (strcmp(args[0], "env") == 0)
// 		ft_env(minishell);
// 	else if (strcmp(args[0], "export") == 0)
// 	{
// 		if (args[1] != NULL)
// 			ft_export(minishell, args);
// 		else
// 			ft_env(minishell);
// 	}
// 	else if (strcmp(args[0], "unset") == 0)
// 	{
// 		if (args[1] != NULL)
// 			ft_unset(minishell, args[1]);
// 	}
// 	else
// 		return (0);// Não é um comando built-in
// 	return (1);// É um comando built-in
// }

void	ft_exit(char **args);
void	ft_pwd(void);
void	ft_cd(char **args);
void	ft_echo(char **args);
void	ft_env(void);
void	ft_export(char **args);
void	ft_unset(char *arg);

BuiltInCommand	*get_builtin_commands(void)
{
	static BuiltInCommand	commands[] = {
	{"exit", ft_exit},
	{"pwd", ft_pwd},
	{"cd", ft_cd},
	{"echo", ft_echo},
	{"env", ft_env},
	{"export", ft_export},
	{"unset", ft_unset}
	};

	return (commands);
}

int	execute_builtin(char **args)
{
	BuiltInCommand	*built_in_commands;
	size_t			num_commands;
	size_t			i;

	num_commands = sizeof(built_in_commands) / sizeof(built_in_commands[0]);
	*built_in_commands = get_builtin_commands();
	i = 0;
	while (i < num_commands)
	{
		if (strcmp(args[0], built_in_commands[i].command) == 0)
		{
			built_in_commands[i].function(args);
			return (1);
		}
		i++;
	}
	return (0);
}
