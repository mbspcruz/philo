/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:35:14 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/28 11:54:12 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_global *global)
{
	print_action(global->philo, 4);
	global->philo_died = 1;
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
			usleep(25000);
			pthread_mutex_unlock(&global->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&global->dead_lock);
		count++;
	}
}

void	is_philo_satisfied(t_global *global)
{
	int	count;

	pthread_mutex_lock(&global->dead_lock);
	count = 0;
	while (global->philo[count].n_meals >= global->n_eat
		&& global->n_eat != -1 && count < global->n_philo)
			count++;
	pthread_mutex_unlock(&global->dead_lock);
	if (count == global->n_philo)
	{
		pthread_mutex_lock(&global->dead_lock);
		global->all_meals = 1;
		pthread_mutex_unlock(&global->dead_lock);
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
		while (!global->all_meals)
		{
			will_philo_die(global);
			pthread_mutex_lock(&global->dead_lock);
			if (global->philo_died)
			{
				pthread_mutex_unlock(&global->dead_lock);
				break ;
			}
			pthread_mutex_unlock(&global->dead_lock);
			is_philo_satisfied(global);
		}
	}
}
