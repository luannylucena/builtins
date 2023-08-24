/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:33:38 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/17 16:30:14 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//função para contar as variáveis de ambiente
int	env_count_var(char **envp)
{
	int	count;

	count = 0;
	while(envp[count] != NULL)
	{
		count++;
	}
	return (count);
	
	printf("%i\n", count);
}
// função para duplicar as variáveis dentro do env
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
	while(envp_copy[i] != NULL)
	{
		free(envp_copy[i]);
		i++;
	}
	free(envp_copy);
}

void ft_env(t_minishell *minishell) {
    print_export(minishell->export_list);
}
