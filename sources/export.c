/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:27:35 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/22 21:43:39 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_export(char **envp_copy, char *token_args)
{
	
	char	*equal_sign;
	char	*var_name;
	char	*var_value;
	int		index;
	int		i;
	int		envp_copy_count;
	char	*new_envp_copy;
	int 	j;

	j = 0;
	// Verificar se o argumento está no formato "VARNAME=value"
	equal_sign = ft_strchr("=", token_args[1]);
	if(equal_sign != NULL)
	{
		*equal_sign = '\0'; // Define o caractere '=' como terminador da string var_name
		var_name = ft_strdup(token_args); // var_name recebe o início da string arg
		var_value = ft_strdup(equal_sign + 1); // var_value recebe o que vem após o '=' em arg

		index = -1; //começa em -1 para mostrar que ainda não foi encontrado a variável.
		i = 0;
		while(envp_copy[i] != NULL)
		{
			//ao inves de usar a função, fazer outro while.
			while(envp_copy[i][j] != '\0' && envp_copy[i][j] != '=')
			{
				if(token_args[j] == envp_copy[i][j])
					j++;
				else
					break;
			} 
			if(envp_copy[i][j] == '=' || envp_copy[i][j] == '\0')
			{
				index = i; //se encontramos a variável, atualizamos o index.
				break;
			}
			i++;
		}
		// Atualizar ou adicionar a variável no novo array de strings
		envp_copy_count = env_count_var(envp_copy);
		new_envp_copy = (char *)malloc(sizeof(char *) * (envp_copy_count + 1));
		if(new_envp_copy == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		//j = 0;
		i = 0;
		while(envp_copy[i] != NULL)
		{
			if(i == index)
			{
				//atualizar a variável
				new_envp_copy[j] = *ft_strdup(token_args);
				j++;
			}
			else
			{
				// Copiar variável sem modificação
				strncpy(&new_envp_copy[j], ft_strdup(envp_copy[i]), strlen(envp_copy[i]) + 1); // Correção usando strncpy

				j++;
			}
			i++;	
		}
		// Se a variável não existir, adicionar
		if (index == -1)
		{
			new_envp_copy[j] = *ft_strdup(token_args);
			j++;
		}
		new_envp_copy[envp_copy_count] = '\0';
		// Liberar a memória do antigo array e atualizar o ponteiro
		i = 0;
		while (envp_copy[i] != NULL)
		{
			free(envp_copy[i]);
			i++;
		}
		free(envp_copy);
		*envp_copy = new_envp_copy;
	}
}