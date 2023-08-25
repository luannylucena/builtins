/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:57:17 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/25 19:02:21 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_minishell *minishell, char *var_name)
{
	int	i;
	int	index; // Índice da variável a ser removida
	index = -1;
	i = 0;
	while (minishell->export_list[i] != NULL)
	{
		if (ft_strncmp(minishell->export_list[i], var_name, ft_strlen(var_name)) == 0)
		{
			if (minishell->export_list[i][ft_strlen(var_name)] == '=' || minishell->export_list[i][ft_strlen(var_name)] == '\0')
			{
				index = i;
				break ;
			}
		}
		i++;
	}
	if (index == -1)
		return ;// A variável não foi encontrada na lista de exportações
	free(minishell->export_list[index]);
	i = index;
	while (minishell->export_list[i] != NULL)
	{
		minishell->export_list[i] = minishell->export_list[i + 1];
		i++;
	}
}
