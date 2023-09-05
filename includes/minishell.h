/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:56:52 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/09/05 18:25:31 by lmedeiro         ###   ########.fr       */
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
	int		exit_status;
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
int		is_valid_export_format(char *str);
void	add_export(char *str, char ***envs, int *count);
void	print_export(char **envs);
void	ft_export(t_minishell *minishell, char **token_args);
void	ft_env(t_minishell *minishell);
int		execute_builtin(char **args, t_minishell *minishell);
int		update_when_exists(char *token_args, int len, t_minishell *minishell);
int		check_if_exists_exp(char **token_args, int i, t_minishell *minishell);
int		check_isname_exp(char **token_args, int i);
void	update_env(char **token_args, int j, t_minishell *minishell);
void	remove_env_i(char **envp_copy, int j);
int		remove_if_exists(char *token_i, int j, int length, t_minishell *minishell);
void	ft_unset(t_minishell *minishell, char *var_name);
void	print_quotes(int i, int j, t_minishell *minishell);
void	copy_env_vars(char **src, char **dst, int count);

#endif
