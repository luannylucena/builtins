/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:15:44 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/11 16:44:13 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int	is_number(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit (char **input_line)
{
	int	arg_count;

	arg_count = count_args(input_line);
	if (arg_count > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return 0;// Não precisa retornar um valor aqui, já que a função é void
	}

    if (arg_count == 1)
    {
        ft_putendl_fd("Bye!!!", 1);
        // Não é recomendado liberar memória que não foi alocada por malloc (input_line foi lido pelo readline)
        exit(EXIT_SUCCESS);
    }

    if (!is_number(input_line[1]))
    {
        ft_putendl_fd("exit: numeric argument required", 2);
        return 0; // Mesmo aqui, não precisa retornar um valor
    }

    int exit_code = atoi(input_line[1]);
    free(input_line); // Lembre-se de liberar a memória antes de sair
    exit(exit_code);
}

