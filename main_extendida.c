#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
    
    char *input_line;

    while(1)
    {
        // Exibir o prompt e aguardar um comando usando readline
        input_line = readline("minishell > ");

        // Verificar se o usuário digitou CTRL+D
        if(input_line == NULL)
        {
            printf("Você apertou CTRL+D, adeus!\n");
            exit(EXIT_SUCCESS);
        }
        // Verificar se o usuário digitou "exit" para sair do minishell
        if(strcmp(input_line, "exit") == 0) //adaptar com a Libft: ft_strcmp.
        {
            printf("Bye!\n");
            free(input_line);
            exit(EXIT_SUCCESS);
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