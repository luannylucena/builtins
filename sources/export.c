/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:52:28 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/09/04 21:20:57 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int update_when_exists(char *token_args, int len, t_minishell *minishell)
{
    int j = 0;
    
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
                && (minishell->envp_copy[j][len] == '\0' || minishell->envp_copy[j][len] == '='))
                return (1);
        }
        j++;
    }
    return (0);
}

int check_if_exists_exp(char **token_args, int i, t_minishell *minishell)
{
    int len;

    if (ft_strchr(token_args[i], '='))
        len = ft_strchr(token_args[i], '=') - &token_args[i][0] + 1;
    else
        len = ft_strlen(token_args[i]);
    return (update_when_exists(token_args[i], len, minishell));
}

int check_isname_exp(char **token_args, int i)
{
    int j;
    
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

void print_quotes(int i, int j, t_minishell *minishell)
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

void check_only_export(t_minishell *minishell) {
    // Imprimir as variáveis de ambiente atuais
    int i = 0;
    while (minishell->envp_copy[i] != NULL) {
        printf("%s\n", minishell->envp_copy[i]);
        i++;
    }

    // Atualizar as variáveis de ambiente
    // ...

    // Imprimir as variáveis de ambiente atualizadas
    i = 0;
    while (minishell->envp_copy[i] != NULL) {
        printf("%s\n", minishell->envp_copy[i]);
        i++;
    }
}

void update_env(char **token_args, int j, t_minishell *minishell)
{
    int count;
    
    if (check_if_exists_exp(token_args, j, minishell))
        return ;

    count = env_count_var(minishell->envp_copy);

    char **new_envp = (char **)malloc(sizeof(char *) * (count + 2));
    
    if (new_envp == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    // Copie os valores existentes para a nova lista
    for (int i = 0; i < count; i++)
    {
        new_envp[i] = ft_strdup(minishell->envp_copy[i]);
        if (new_envp[i] == NULL)
        {
            perror("ft_strdup");
            exit(EXIT_FAILURE);
        }
    }
    // Adicione a nova variável à nova lista
    new_envp[count] = ft_strdup(token_args[j]);
    if (new_envp[count] == NULL)
    {
        perror("ft_strdup");
        exit(EXIT_FAILURE);
    }
    new_envp[count + 1] = NULL;

    // Libere a lista antiga
    envp_free(minishell->envp_copy);

    // Atualize a estrutura t_minishell para usar a nova lista
    minishell->envp_copy = new_envp;
}

void ft_export(t_minishell *minishell, char **token_args)
{
    int i;
    
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