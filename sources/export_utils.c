/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:57:34 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/09/06 12:48:38 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_and_update_var(char *token_args, int len)
{
	int	j;

	j = 0;
	while (g_minishell.envp_copy[j])
	{	
		if (ft_strchr(token_args, '='))
		{
			if (!ft_strncmp(g_minishell.envp_copy[j], token_args, len)
				|| (!ft_strncmp(g_minishell.envp_copy[j], token_args, len - 1)
					&& g_minishell.envp_copy[j][len - 1] == '\0'))
			{
				free(g_minishell.envp_copy[j]);
				g_minishell.envp_copy[j] = ft_strdup(token_args);
				return (1);
			}
		}
		else if (!ft_strncmp(g_minishell.envp_copy[j], token_args, len)
			&& (g_minishell.envp_copy[j][len] == '\0'
			|| g_minishell.envp_copy[j][len] == '='))
			return (1);
		j++;
	}
	return (0);
}

int	check_var(char **token_args, int i)
{
	int	len;

	if (ft_strchr(token_args[i], '='))
		len = ft_strchr(token_args[i], '=') - &token_args[i][0] + 1;
	else
		len = ft_strlen(token_args[i]);
	return (update_when_exists(token_args[i], len));
}

int	is_valid_name(char **token_args, int i)
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

void	add_quotes(int i, int j)
{
	if (g_minishell.export_list[i][j] != '\0')
	{
		ft_putstr_fd("=\"", 1);
		j++;
		while (g_minishell.export_list[i][j])
		{
			ft_putchar_fd(g_minishell.export_list[i][j], 1);
			j++;
		}
		ft_putchar_fd('\"', 1);
	}
}
