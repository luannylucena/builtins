/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:57:17 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/09/06 16:09:48 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_name_unset(char *token_args)
{
	int	j;

	j = 0;
	if (token_args[j] != '_' && !ft_isalpha(token_args[j]))
		return (0);
	j++;
	while (token_args[j] == '_' || ft_isalnum(token_args[j]))
		j++;
	if (!token_args[j] || token_args[j] == '=')
		return (1);
	return (0);
}

void	index_to_remove_env(char **envp_copy, int j)
{
	while (envp_copy[j])
	{
		free(envp_copy[j]);
		envp_copy[j] = ft_strdup(envp_copy[j + 1]);
		if (!envp_copy[j][0])
		{
			free(envp_copy[j]);
			envp_copy[j] = NULL;
		}
		j++;
	}
}

int	if_exist_remove_unset(char *token_i, int j, int length)
{
	if (!ft_strncmp(g_minishell.envp_copy[j], token_i, length)
		&& (!g_minishell.envp_copy[j][length]
		|| g_minishell.envp_copy[j][length] == '='))
	{
		index_to_remove_env(g_minishell.envp_copy, j);
		return (1);
	}
	return (0);
}

void	ft_unset(char *var_name)
{
	int	i;
	int	index;

	index = -1;
	i = 0;
	while (g_minishell.envp_copy[i] != NULL)
	{
		if (ft_strncmp(g_minishell.envp_copy[i]
				, var_name, ft_strlen(var_name)) == 0)
		{
			if (g_minishell.envp_copy[i][ft_strlen(var_name)] == '='
			|| g_minishell.envp_copy[i][ft_strlen(var_name)] == '\0')
			{
				index = i;
				break ;
			}
		}
		i++;
	}
	if (index == -1)
		return ;
	free(g_minishell.envp_copy[index]);
	i = index;
	while (g_minishell.envp_copy[i] != NULL)
	{
		g_minishell.envp_copy[i] = g_minishell.envp_copy[i + 1];
		i++;
	}
}
