/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:14:22 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/17 20:41:53 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_unset(char **envp_copy, const char *var_name)
{
    int i;
    int envp_count;

    envp_count = envp_count_var(envp_copy);

    while((*envp_copy[i]) != NULL)
    {
        
    }
    
}

void ft_unset(char ***envp_copy, const char *var_name) {
    int i = 0;
    int envp_count = count_env_vars(*envp_copy);

    // A função ft_unset recebe um ponteiro para um ponteiro para o array de variáveis de ambiente,
    // para que possa modificar o array diretamente (por referência).
    
    while ((*envp_copy)[i] != NULL) {
        // A função itera sobre o array de variáveis de ambiente copiado até encontrar uma entrada nula,
        // que indica o final do array.
        
        if (strstr((*envp_copy)[i], var_name) == (*envp_copy)[i]) {
            // O trecho 'strstr((*envp_copy)[i], var_name) == (*envp_copy)[i]' verifica se o nome da variável
            // (*envp_copy)[i] começa com a string var_name.
            
            // Se encontrarmos uma variável que começa com o nome especificado, faremos as seguintes ações:
            
            free((*envp_copy)[i]); // Libera a memória alocada para a variável
            
            for (int j = i; j < envp_count - 1; j++) {
                // Em seguida, percorremos o array a partir da posição onde encontramos a variável correspondente,
                // movendo todas as variáveis subsequentes uma posição para cima no array.
                
                (*envp_copy)[j] = (*envp_copy)[j + 1];
                // Movemos a variável da posição [j+1] para a posição [j].
            }
            
            (*envp_copy)[envp_count - 1] = NULL;
            // Finalmente, definimos a última entrada do array como NULL para indicar o novo final do array.
            // Isso é necessário porque removemos um elemento e queremos garantir que o array continue terminando com NULL.
            
            break; // Saímos do loop, pois já encontramos e tratamos a variável.
        }
        
        i++; // Passamos para a próxima variável no array.
    }
}