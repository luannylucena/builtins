/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:57:34 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/09/05 17:51:16 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_when_exists(char *token_args, int len, t_minishell *minishell)
{
	int	j;

	j = 0;
	while (minishell->envp_copy[j])
	{	
		if (ft_strchr(token_args, '='))
		{
			if (!ft_strncmp(minishell->envp_copy[j], token_args, len)
				|| (!ft_strncmp(minishell->envp_copy[j], token_args, len - 1)
					&& minishell->envp_copy[j][len - 1] == '\0'))
			{
				free(minishell->envp_copy[j]);
				minishell->envp_copy[j] = ft_strdup(token_args);
				return (1);
			}
		}
		else
		{
			if (!ft_strncmp(minishell->envp_copy[j], token_args, len)
				&& (minishell->envp_copy[j][len] == '\0'
				|| minishell->envp_copy[j][len] == '='))
				return (1);
		}
		j++;
	}
	return (0);
}

int	check_if_exists_exp(char **token_args, int i, t_minishell *minishell)
{
	int	len;

	if (ft_strchr(token_args[i], '='))
		len = ft_strchr(token_args[i], '=') - &token_args[i][0] + 1;
	else
		len = ft_strlen(token_args[i]);
	return (update_when_exists(token_args[i], len, minishell));
}

int	check_isname_exp(char **token_args, int i)
{
	int	j;

	j = 0;
	if (token_args[i][j] != '_' && !ft_isalpha(token_args[i][j]))
		return (0);
	j++;
	while (token_args[i][j] == '_' || ft_isalnum(token_args[i][j]))
		j++;
	if (!token_args[i][j] || token_args[i][j] == '=')
		return (1);
	return (0);
}

void	print_quotes(int i, int j, t_minishell *minishell)
{
	if (minishell->export_list[i][j] != '\0')
	{
		ft_putstr_fd("=\"", 1);
		j++;
		while (minishell->export_list[i][j])
		{
			ft_putchar_fd(minishell->export_list[i][j], 1);
			j++;
		}
		ft_putchar_fd('\"', 1);
	}
}
