/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:31:44 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/21 22:21:11 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	assign_rules(t_global *global, int ac, char **av)
{
	if (!(global = (t_global *)malloc(sizeof(t_global))))
		return FALSE;
	global->n_philo = ft_atoi(av[1]);
	global->t_die = ft_atoi(av[2]);
	global->t_eat = ft_atoi(av[3]);
	global->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		global->n_eat = ft_atoi(av[5]);
	else
		global->n_eat = -1;
	return TRUE;
}

int	assign_philo(t_global *global)
{
	int count;
	
	count = 0;
	while()
}

int	check_args(t_global *global, int ac, char **av)
{
	if (!assign_rules (global, ac, av))
		return FALSE;
	if (!assign_philo(global))
		return FALSE;
}

int	main(int ac, char **av)
{
	t_global *global;
	
	if (!check_args(global, ac, av))
	{
		ft_putstr_fd("Error with args", STDERR_FILENO);
		return 1;
	}
}