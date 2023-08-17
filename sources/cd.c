/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:32:01 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/11 16:51:13 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../includes/minishell.h"
 
/*Para implementar a função cd em seu minishell, você precisa definir uma função que manipule a 
mudança de diretório atual. Aqui está um guia passo a passo sobre como fazer isso:

    Definir a função execute_cd: Crie uma função que execute o comando cd. Você pode usar a função chdir 
    para mudar o diretório atual. Certifique-se de verificar se a função chdir 
    retorna 0 (sucesso) ou -1 (erro). Você também deve verificar se a quantidade de argumentos fornecidos é correta. 
    Aqui está um exemplo: */

void   ft_cd(char **args) //recebe um array de strings 'args'                       
{
    //nenhum argumento passado além do cd, então vamos para HOME
    if (args[1] == NULL)
    {
        const char *go_home = getenv("HOME");
        if (go_home != NULL) //Verificamos se conseguimos obter o caminho do diretório HOME (ou seja, se não é NULL)
        {
            if (chdir(go_home) != 0) //Se retornar um valor diferente de zero, significa que ocorreu um erro durante a mudança de diretório.
            {
                perror("cd");
            }
        }
        else
        {
            ft_putendl_fd("cd: could not determine home directory\n", 2);
        }
    }
    else if (args[1] != NULL && chdir(args[1]) != 0) //se a função chdir retornar um valor diferente de zero, isso significa que ocorreu um erro 
    {
        perror("cd");
    }
}
