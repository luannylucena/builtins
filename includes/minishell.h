/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:56:52 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/30 17:55:15 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include "minishell.h"
# include "../libft/libft.h"

typedef struct s_minishell{
	char	**envp_copy;
	char	**export_list;
	char	**export_copy;
}	t_minishell;

typedef struct {
    char *command;
    void (*function)(char **args);
} BuiltInCommand;

void	ctrl_d(char *input_line);
void	ft_exit(char **args);
void	sigquit_handler(int signal);
void	sigint_handler(int signal);
void	ft_pwd(void);
void	ft_cd(char **args);
void	ft_echo(char **args);
int		env_count_var(char **envp);
char	**env_duplicate(char **envp);
void	envp_free(char **envp_copy);
int		isvalid_export(char *key);
int		check_export(char *str, char ***envs);
void	add_export(char *str, char ***envs, int *count);
void	print_export(char **envs);
void	ft_export(char **args);
void	ft_env(void);
void	ft_unset(char *arg);
int		execute_builtin(char **args)

#endif
