/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:52:28 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/09/05 16:02:35 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env(char **token_args, int j, t_minishell *minishell)
{
	int		count;
	int		i;
	char	**new_envp;

	if (check_if_exists_exp(token_args, j, minishell))
		return ;
	count = env_count_var(minishell->envp_copy);
	new_envp = (char **)malloc(sizeof(char *) * (count + 2));
	if (new_envp == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(minishell->envp_copy[i]);
		if (new_envp[i] == NULL)
		{
			perror("ft_strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	new_envp[count] = ft_strdup(token_args[j]);
	if (new_envp[count] == NULL)
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	new_envp[count + 1] = NULL;
	envp_free(minishell->envp_copy);
	minishell->envp_copy = new_envp;
}

void	ft_export(t_minishell *minishell, char **token_args)
{
	int	i;

	i = 1;
	while (token_args[i])
	{
		if (!check_isname_exp(token_args, i))
			printf("export: %s: not a valid identifier\n", token_args[i]);
		else
			update_env(token_args, i, minishell);
		i++;
	}
}
