
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "minishell.h"


void ctrl_d(char *input_line);
void ft_exit(char *input_line);
void sigquit_handler(int signal);
void sigint_handler(int signal);

#endif