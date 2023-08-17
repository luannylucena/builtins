/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedeiro <lmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:33:38 by lmedeiro          #+#    #+#             */
/*   Updated: 2023/08/15 14:43:38 by lmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// essa função lista as variáveis de ambiente
void    ft_env ()
{
	extern	char **environ;
	
	int	i;

	i = 0;
	while(environ[i] != 'NULL')
	{
		printf("%s\n", environ);
		i++;
	}
}