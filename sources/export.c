/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:41:01 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/31 20:38:03 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define SUCCESS 0
#define ERROR 1

void	print_export(char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
	{
		ft_putstr_fd(envs[i], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	add_export(char *str, char ***envs, int *count)
{
	(*envs)[*count] = ft_strdup(str);
	(*count)++;
	(*envs)[*count] = NULL;
}

int find_existing_variable(char *str, char **envs)
{
    int i;

    i = 0;
    while (envs[i] != NULL)
    {
        if (!strcmp(envs[i], str))
            return i;
        i++;
    }
    return (-1);
}

void update_variable_value(char *value, char ***envs, int index)
{
    free((*envs)[index]);
    (*envs)[index] = ft_strdup(value);
}

void add_new_variable(char *str, char ***envs)
{
    int count;
    int i;
    
    count = 0;
    while ((*envs)[count] != NULL)
        count++;
    char **new_envs = malloc(sizeof(char *) * (count + 2));
    i = 0;
    while ((*envs)[i] != NULL)
    {
        new_envs[i] = ft_strdup((*envs)[i]);
        i++;
    }
    new_envs[i] = ft_strdup(str);
    new_envs[i + 1] = NULL;
    *envs = new_envs;
}

int find_existing_variable_prefix(char *str, char **envs)
{
    int i;
    
    i = 0;
    while (envs[i] != NULL)
    {
        if (!ft_strncmp(envs[i], str, ft_strlen(str)))
            return i;
        i++;
    }
    return (-1);
}
// verifica se o primeiro caractere é uma letra ou o caractere _
int is_valid_name(char *identifier)
{
    int i;
    
    i = 0;
    if (!ft_isalpha(identifier[0]) && identifier[0] != '_')
        return 0;
    while (identifier[i])
    {
        if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
            return (0);
        i++;
    }
    return (1);
}
// verifica se um argumento está no formato correto (a=b)
int is_valid_format(char *key)
{
    char *equal_sign;

    equal_sign = strchr(key, '=');
    if (equal_sign == NULL || equal_sign == key) {
        printf("Not a valid export format: %s\n", key);
        return (0);
    }
    // Check left side of '='
    *equal_sign = '\0';
    if (!is_valid_name(key)) {
        *equal_sign = '=';
        printf("Not a valid identifier: %s\n", key);
        return (0);
    }
    *equal_sign = '=';
    // Check right side of '='
    if (!is_valid_name(equal_sign + 1))
    {
        printf("Not a valid identifier: %s\n", equal_sign + 1);
        return (0);
    }
    return (1);
}
//A função find_export_index procura por uma variável de ambiente em uma lista de exportações. 
//Ela recebe um array export_list e uma string key representando o nome da variável a ser procurada.
//A função percorre  a lista e compara cada elemento com a chave usando a função strcmp. Se encontrar a
// variável, retorna o índice dela na lista, caso contrário, retorna -1.
int find_export_index(char **export_list, char *key)
{
	int index;

	index = 0;
	while (export_list[index] != NULL) {
		if (strcmp(export_list[index], key) == 0)
			return (index);
		index++;
	}
	return (-1); // Indica que a variável não foi encontrada
}

void copy_previous_list(char **old_list, char **new_list, int count) {
    for (int i = 0; i < count; i++) {
        new_list[i] = old_list[i];
    }
}

void handle_valid_export_format(t_minishell *minishell, char *arg)
{
    int index = find_export_index(minishell->export_list, arg);
    if (index >= 0)
    {
        free(minishell->export_list[index]);
        minishell->export_list[index] = ft_strdup(arg);
        printf("Variable %s updated.\n", arg);
    }
    else
    {
        int count = env_count_var(minishell->export_list);
        char **new_list = (char **)malloc(sizeof(char *) * (count + 2));
        if (!new_list)
        {
            printf("Memory allocation error.\n");
            return;
        }
        copy_previous_list(minishell->export_list, new_list, count);
        add_export(arg, &new_list, &count);
        envp_free(minishell->export_list);
        minishell->export_list = new_list;
        printf("Variable %s added.\n", arg);
    }
}

void handle_valid_identifier(t_minishell *minishell, char *arg)
{
    int index;
    int count; 
    
    index = find_export_index(minishell->export_list, arg);
    if (index >= 0)
    {
        free(minishell->export_list[index]);
        minishell->export_list[index] = ft_strdup(arg);
        printf("Variable %s updated.\n", arg);
    }
    else
    {
        count = env_count_var(minishell->export_list);
        char **new_list = (char **)malloc(sizeof(char *) * (count + 2));
        if (!new_list)
        {
            printf("Memory allocation error.\n");
            return;
        }
        copy_previous_list(minishell->export_list, new_list, count);
        add_export(arg, &new_list, &count);
        envp_free(minishell->export_list);
        minishell->export_list = new_list;
        printf("Variable %s added.\n", arg);
    }
}

void ft_export(t_minishell *minishell, char **token_args)
{
    int i;
    
    i = 1; // skipping the "export" command
    while (token_args[i] != NULL)
    {
        char *arg = token_args[i]; // get the current argument
        if (is_valid_format(arg))
            handle_valid_export_format(minishell, arg);
        else if (is_valid_name(arg))
            handle_valid_identifier(minishell, arg);
        else
            printf("Not a valid identifier or export format: %s\n", arg);
        i++;
    }
}

