/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:57:17 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/09/05 17:26:29 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_isname_unset(char *token_args)
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

void	remove_env_i(char **envp_copy, int j)
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

int	remove_if_exists(char *token_i, int j, int length, t_minishell *minishell)
{
	if (!ft_strncmp(minishell->envp_copy[j], token_i, length)
		&& (!minishell->envp_copy[j][length]
		|| minishell->envp_copy[j][length] == '='))
	{
		remove_env_i(minishell->envp_copy, j);
		return (1);
	}
	return (0);
}

void	ft_unset(t_minishell *minishell, char *var_name)
{
	int	i;
	int	index;

	index = -1;
	i = 0;
	while (minishell->envp_copy[i] != NULL)
	{
		if (ft_strncmp(minishell->envp_copy[i]
				, var_name, ft_strlen(var_name)) == 0)
		{
			if (minishell->envp_copy[i][ft_strlen(var_name)] == '='
			|| minishell->envp_copy[i][ft_strlen(var_name)] == '\0')
			{
				index = i;
				break ;
			}
		}
		i++;
	}
	if (index == -1)
		return ;
	free(minishell->envp_copy[index]);
	i = index;
	while (minishell->envp_copy[i] != NULL)
	{
		minishell->envp_copy[i] = minishell->envp_copy[i + 1];
		i++;
	}
}
