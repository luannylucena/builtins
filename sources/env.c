/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:33:38 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/09/06 16:28:06 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_count_var(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
	{
		count++;
	}
	return (count);
	printf("%i\n", count);
}

char	**env_duplicate(char **envp)
{
	int		count;
	char	**envp_copy;
	int		i;

	count = env_count_var(envp);
	envp_copy = (char **)malloc(sizeof(char *) * (count + 1));
	if (envp_copy == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (envp_copy[i] == NULL)
		{
			perror("ft_strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	envp_copy[count] = NULL;
	return (envp_copy);
}

//função para dar free
void	envp_free(char **envp_copy)
{
	int	i;

	i = 0;
	while (envp_copy[i] != NULL)
	{
		free(envp_copy[i]);
		i++;
	}
	free(envp_copy);
}

void	ft_env()
{
	int	i;

	i = 0;
	while (g_minishell.envp_copy[i] != NULL)
	{
		printf("%s\n", g_minishell.envp_copy[i]);
		i++;
	}
}
