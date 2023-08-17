/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:40:38 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/08 20:19:08 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
A função getcwd() recebe dois parâmetros:

    Um ponteiro para um buffer de caracteres onde o caminho do diretório de trabalho atual será armazenado.
    Um valor do tipo size_t que representa o tamanho do buffer passado no primeiro parâmetro.

A assinatura da função getcwd() é a seguinte:

c

char *getcwd(char *buf, size_t size);

    buf: Um ponteiro para um buffer de caracteres (ou uma sequência de caracteres) que será preenchido com 
    o caminho absoluto do diretório de trabalho atual. Este buffer deve ser grande o suficiente para conter o 
    caminho completo, caso contrário, pode ocorrer um estouro de buffer.
    size: O tamanho do buffer fornecido em bytes.
*/

#include "../includes/minishell.h"

void ft_pwd()
{
    char current_dir[1024];

    if(getcwd(current_dir, sizeof(current_dir)) != NULL)
    {
        printf("%s\n", current_dir);
    }
    else
        perror("getcwd");
}
