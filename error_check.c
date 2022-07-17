/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:41:37 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/08 13:45:53 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//error check to see if arguments are valid
//check the number of arguments, if there's
//invalid characters and if it's positive


int	is_digit(int ac, char **av)
{
	int i = 1;
	int j = 0;
	
	while(i < ac)
	{
		while(av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				return 0;
				break;
			}
			j++;
		}
		i++;
	}
	return 1;
}