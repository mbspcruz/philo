/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:31:44 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/27 19:18:39 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simul(t_global *global)
{
	if (!init_simul(global))
	{
		ft_putstr_fd("Error creating threads", STDERR_FILENO);
		finish_destroy(global);
		return (3);
	}
	check_death(global);
	if (!finish_destroy(global))
	{
		ft_putstr_fd("Error finishing", STDERR_FILENO);
		return (4);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_global	*global;

	global = NULL;
	if (!check_args(ac, av))
	{
		ft_putstr_fd("Error with args", STDERR_FILENO);
		return (1);
	}
	global = init_global(global, ac, av);
	if (!global)
	{
		ft_putstr_fd("Error with philo assignement", STDERR_FILENO);
		finish_destroy(global);
		return (2);
	}
	check_simul(global);
	return (0);
}
