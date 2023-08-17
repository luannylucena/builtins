/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:57:29 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/10 16:10:36 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../includes/minishell.h"

void	ctrl_d(char *input_line)
{	
	if (input_line == NULL)
	{
		printf("Você digitou ctrl+d, adeus!\n");
		exit(EXIT_SUCCESS);
	}
}

void	sigquit_handler(int signal)
{
	printf("\rVocê pressionou Ctrl + \\, mas esse sinal foi ignorado.\n");
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
}

void	sigint_handler(int signal)
{
	printf("\rVocê pressionou Ctrl + C, mas esse sinal foi ignorado.\n");
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
}
