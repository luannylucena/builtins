/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:41:01 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/25 18:48:12 by lmedeiro         ###   ########.fr       */
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

int	check_export(char *str, char ***envs)
{
	int		i;
	char	**new;
	char	*equal_sign;

	equal_sign = NULL;
	equal_sign = strchr(str, '=');
	if (str[0] == '\0')
		return (ERROR);
	if (equal_sign != NULL && equal_sign != str && equal_sign[1] != '\0')
	{
		*equal_sign = '\0'; // Temporariamente substitua '=' por '\0'
		i = -1;
		while ((*envs)[++i] != NULL)
		{
			if (!strcmp((*envs)[i], str))
			{
				// Variável já existe, atualizar o valor dela
				free((*envs)[i]); // Liberar memória do valor antigo
				(*envs)[i] = ft_strdup(equal_sign + 1); // Copiar novo valor
				*equal_sign = '='; // Restaurar o caractere '=' para a string
				return (SUCCESS);
			}
		}
		*equal_sign = '='; // Restaurar o caractere '=' para a string
		// Continuar com o código para adicionar a nova variável à lista
		if (!(new = malloc(sizeof(char *) * (i + 2))))
			return (ERROR);
		i = -1;
		while ((*envs)[++i])
			new[i] = ft_strdup((*envs)[i]);
		add_export(str, envs, &i);
		*envs = new;
		return (SUCCESS);
	}
	else
	{
		if (str[0] == '\0')
			return (ERROR);
		i = -1;
		while ((*envs)[++i] != NULL)
		{
			if (!ft_strncmp((*envs)[i], str, ft_strlen(str)))
			{
				(*envs)[i] = ft_strdup(str);
				return (SUCCESS);
			}
		}
		if (!(new = malloc(sizeof(char *) * (i + 2))))
			return (ERROR);
		i = -1;
		while ((*envs)[++i])
			new[i] = ft_strdup((*envs)[i]);
		add_export(str, envs, &i);
		*envs = new;
		return (SUCCESS);
	}
}

int	isvalid_export(char *key)
{
	int	i;

	if (ft_isdigit(key[0]))
	{
		printf("Not a valid identifier: %s\n", key);
		return (0); //retorna zero para dizer que não é um identificador válido
	}
	i = 0;
	while (key[i])
	{	
		// Check for characters that are not allowed in an identifier
		if (!isalnum(key[i]) && key[i] != '_')
		{
			printf("Not a valid identifier: %s\n", key);
			return (0);
		}
		i++;
	}
	return (1);
}

int find_export_index(char **export_list, char *key)
{
	int index;

	index = 0;
	while (export_list[index] != NULL) {
		if (strcmp(export_list[index], key) == 0)
		{
			return index;
		}
		index++;
	}
	return (-1); // Indica que a variável não foi encontrada
}

void	ft_export(t_minishell *minishell, char **token_args)
{
	int	i;
	int	index;
	int	j;

	i = 1; //pulando o comando "export"
	while (token_args[i] != NULL) //enquanto houver argumentos após o export.
	{
		char *arg;

		*arg = token_args[i]; //pega o argumento atual
		if (!isvalid_export(arg)) //verifica se é um argumento válido
		{
			printf("Not a valid identifier: %s\n", arg);
			i++;
			continue ;
		}
		index = find_export_index(minishell->export_list, arg);
		if (index >= 0)
		{
			free(minishell->export_list[index]);
			minishell->export_list[index] = ft_strdup(arg);
			printf("Variable %s updated.\n", arg);
		}
		else
		{
			// Adicione a variável à lista de exportações
			int	count = env_count_var(minishell->export_list);
			char	**new_list = (char **)malloc(sizeof(char *) * (count + 2));
			if (!new_list)
			{
				printf("Memory allocation error.\n");
				return ;
			}
			// Copiar elementos da lista anterior
			j = 0;
			while (j < count)
			{
				new_list[j] = ft_strdup(minishell->export_list[j]);
				j++;
			}
			add_export(arg, &new_list, &count); // Adicionar o novo elemento
			envp_free(minishell->export_list);
			minishell->export_list = new_list;
			printf("Variable %s added.\n", arg);
		}
		i++;
	}
}
