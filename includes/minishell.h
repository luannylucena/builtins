/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:56:52 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/22 21:34:23 by lmedeiro         ###   ########.fr       */
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

void	ctrl_d(char *input_line);
int		ft_exit(char **input_line);
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
void	ft_export(t_minishell *minishell, char **token_args);
void	ft_env(t_minishell *minishell);
void	ft_unset(t_minishell *minishell, char *var_name);
int		execute_builtin (char **args, t_minishell *minishell);

#endif
