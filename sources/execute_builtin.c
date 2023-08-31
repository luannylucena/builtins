/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:27:49 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/31 18:20:19 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_builtin(char **args, t_minishell *minishell)
{
	if (strcmp(args[0], "exit") == 0)
		ft_exit(args);
	else if (strcmp(args[0], "pwd") == 0)
		ft_pwd();
	else if (strcmp(args[0], "cd") == 0)
		ft_cd(args);
	else if (strcmp(args[0], "echo") == 0)
		ft_echo(args);
	else if (strcmp(args[0], "env") == 0)
		ft_env(minishell);
	else if (strcmp(args[0], "export") == 0)
	{
		if (args[1] != NULL)
			ft_export(minishell, args);
		else
			ft_env(minishell);
	}
	else if (strcmp(args[0], "unset") == 0)
	{
		if (args[1] != NULL)
			ft_unset(minishell, args[1]);
	}
	else
		return (0);// Não é um comando built-in
	return (1);// É um comando built-in
}

