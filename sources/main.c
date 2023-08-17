/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:47:34 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/17 13:41:05 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *input_line;
    signal(SIGQUIT, sigquit_handler);
    signal(SIGINT, sigint_handler);

    while(1)
    {
        (void) argv;
        (void) envp;
        
        if(argc != 1)
            return(1);
            
        // Exibir o prompt e aguardar um comando usando readline
        input_line = readline("minishell$ ");

        if (input_line == NULL)
        {
            ctrl_d(input_line);
        }
        
        // if builtins (fazer um arquivo só para isso e compilar em uma linha só aqui)

        // if (builtins?)
        char **token_args = ft_split(input_line, ' ');
        if (strcmp(token_args[0], "exit") == 0)
        {
            ft_exit(token_args);
            free(token_args[0]);
            free(token_args);
        }
        //checando se o usuário digitou pwd.
        if (strcmp(token_args[0], "pwd") == 0)
        {
            ft_pwd(token_args);
            free(token_args[0]);
            free(token_args);
        }
        if (strcmp(token_args[0], "cd") == 0)
        {
            ft_cd(token_args);
            free(token_args[0]);
            free(token_args);
        }
        if (strcmp(token_args[0], "echo") == 0)
        {
            ft_echo(token_args);
            free(token_args[0]);
            free(token_args);
        }
        // if (strcmp(token_args[0], "unset") == 0)
        // {
        //     ft_unset(token_args);
        //     free(token_args[0]);
        //     free(token_args);
        // }
        if (strcmp(token_args[0], "env") == 0)
        {
            ft_env(token_args);
            free(token_args[0]);
            free(token_args);
        }
        if(input_line)
        {
            printf("%s\n", input_line);    
            // Adicionando o comando ao histórico do readline
            if (strlen(input_line) > 0) //adaptar ao ft_strlen
            {
                add_history(input_line);
            }
            free(input_line);
        }
    }
    return(0);
}