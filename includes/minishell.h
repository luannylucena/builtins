/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:56:52 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/09/06 16:09:30 by lmedeiro         ###   ########.fr       */
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

extern t_minishell g_minishell;

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
void	ft_export(char **token_args);
void	ft_env();
int		execute_builtin(char **args);
int		check_and_update_var(char *token_args, int len);
int		check_var(char **token_args, int i);
int		is_valid_name(char **token_args, int i);
void	refresh_env(char **token_args, int j);
void	index_to_remove_env(char **envp_copy, int j);
int		if_exist_remove_unset(char *token_i, int j, int length);
void	ft_unset(char *var_name);
void	add_quotes(int i, int j);
void	copy_env_vars(char **src, char **dst, int count);
void	free_minishell();
int		is_name_unset(char *token_args);

#endif
