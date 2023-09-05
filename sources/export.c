/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:52:28 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/09/05 19:20:24 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_env_vars(char **src, char **dst, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			perror("ft_strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

char	**add_variable_to_env(char **envp_copy, const char *new_var)
{
	int		env_count;
	char	**new_envp;

	env_count = 0;
	while (envp_copy[env_count])
	{
		env_count++;
	}
	new_envp = (char **)malloc((env_count + 2) * sizeof(char *));
	if (!new_envp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	copy_env_vars(envp_copy, new_envp, env_count);
	new_envp[env_count] = ft_strdup(new_var);
	if (!new_envp[env_count])
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	new_envp[env_count + 1] = NULL;
	return (new_envp);
}

void	update_env(char **token_args, int j)
{
	char	**new_envp;

	if (check_if_exists_exp(token_args, j))
	{
		return ;
	}
	new_envp = add_variable_to_env(g_minishell.envp_copy, token_args[j]);
	envp_free(g_minishell.envp_copy);
	g_minishell.envp_copy = new_envp;
}

void	ft_export(char **token_args)
{
	int	i;

	i = 1;
	while (token_args[i])
	{
		if (!check_isname_exp(token_args, i))
			printf("export: %s: not a valid identifier\n", token_args[i]);
		else
			update_env(token_args, i);
		i++;
	}
}
