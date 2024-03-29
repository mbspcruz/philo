/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:35:14 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/08/18 14:41:34 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_global *global)
{
	print_action(global->philo, DIE);
	global->philo_died = 1;
	usleep(25000);
}

void	is_satisfied(t_global *global)
{
	pthread_mutex_lock(&global->print_lock);
	global->philo_died = 1;
	usleep(25000);
	pthread_mutex_unlock(&global->print_lock);
	pthread_mutex_unlock(&global->dead_lock);
}

void	will_philo_die(t_global *global)
{
	int	count;

	count = 0;
	while (count < global->n_philo && !global->philo_died)
	{
		pthread_mutex_lock(&global->dead_lock);
		if (time_diff(global->time_init) - global->philo[count].last_meal
			> global->t_die)
		{
			die(global);
			pthread_mutex_unlock(&global->dead_lock);
			break ;
		}
		if (global->full == global->n_philo)
		{	
			is_satisfied(global);
			break ;
		}
		pthread_mutex_unlock(&global->dead_lock);
		count++;
		usleep(500);
	}
}

void	check_death(t_global *global)
{
	if (global->n_philo == 1)
	{
		sleepy_time(global->philo, global->t_die);
		die(global);
	}
	else
	{
		while (TRUE)
		{
			will_philo_die(global);
			pthread_mutex_lock(&global->dead_lock);
			if (global->philo_died)
			{
				pthread_mutex_unlock(&global->dead_lock);
				break ;
			}
			pthread_mutex_unlock(&global->dead_lock);
		}
	}
}
