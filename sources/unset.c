#include "../includes/minishell.h"

void ft_unset(t_minishell *minishell, char *var_name)
{
    int index = -1; // Índice da variável a ser removida
 
    for (int i = 0; minishell->export_list[i] != NULL; i++)
    {
        if (ft_strncmp(minishell->export_list[i], var_name, ft_strlen(var_name)) == 0)
        {
            if (minishell->export_list[i][ft_strlen(var_name)] == '=' || minishell->export_list[i][ft_strlen(var_name)] == '\0')
            {
                index = i;
                break;
            }
        }
    }
    if (index == -1)
    {
        // A variável não foi encontrada na lista de exportações
        return;
    }
    free(minishell->export_list[index]);
    for (int i = index; minishell->export_list[i] != NULL; i++)
    {
        minishell->export_list[i] = minishell->export_list[i + 1];
    }
}
