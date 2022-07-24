/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:39:24 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/24 13:12:10 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	assign_rules(t_global *global, int ac, char **av)
{
	global->n_philo = ft_atoi(av[1]);
	global->t_die = ft_atoi(av[2]);
	global->t_eat = ft_atoi(av[3]);
	global->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		global->n_eat = ft_atoi(av[5]);
	else
		global->n_eat = -1;
	global->philo_died = 0;
	global->all_meals = 0;
	global->time_init = get_time();
	return TRUE;
}

t_bool	assign_philo(t_global *global)
{
	int count;
	count = 0;
	global->philo = NULL;
	if (!(global->philo = (t_philo *)malloc(sizeof(t_philo) * global->n_philo)))
		return FALSE; 
	while(count < global->n_philo)
	{
		global->philo[count].fork_left = (count + 1) % global->n_philo;
		global->philo[count].fork_right = count;
		global->philo[count].last_meal = global->time_init;
		global->philo[count].n_meals = 0;
		global->philo[count].global = global;
		global->philo[count].philo_id = count + 1;
		count++;
	}
	return TRUE;
}

t_global *init_global(t_global *global, int ac, char **av)
{
	if (!(global = (t_global *)malloc(sizeof(t_global))))
		return NULL;
	if (!assign_rules (global, ac, av))
		return NULL;
	if (!assign_philo(global))
		return NULL;
	return (global);
}

t_bool	check_args(int ac, char **av)
{
	
	if (ac != 5 && ac != 6)
		return FALSE;
	if (!is_digit(ac, av))
		return FALSE;
	return TRUE;
}