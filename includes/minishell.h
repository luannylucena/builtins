/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:56:52 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/17 16:43:32 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "minishell.h"
#include "../libft/libft.h"

void    ctrl_d(char *input_line);
int     ft_exit(char **input_line);
void    sigquit_handler(int signal);
void    sigint_handler(int signal);
void    ft_pwd();
void    ft_cd(char **args);
void    ft_echo(char **args);
void    ft_env(char **envp);
int     env_count_var(char **envp);
char	**env_duplicate(char **envp);
void	envp_free(char **envp_copy);

#endif
