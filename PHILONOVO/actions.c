/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:31:46 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/27 19:05:55 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_sleeping(t_philo *philo)
{
	print_action(philo, 2);
	sleepy_time(philo, philo->global->t_sleep);
}

void	start_eating(t_philo *philo)
{
	print_action(philo, 1);
	pthread_mutex_lock(&philo->global->dead_lock);
	philo->last_meal = time_diff(philo->global->time_init);
	pthread_mutex_unlock(&philo->global->dead_lock);
	sleepy_time(philo, philo->global->t_eat);
	pthread_mutex_lock(&philo->global->dead_lock);
	if (philo->n_meals != philo->global->n_eat)
		philo->n_meals++;
	pthread_mutex_unlock(&philo->global->dead_lock);
	drop_forks(philo);
}

void	pick_up_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->global->forks[philo->fork_right]);
		pthread_mutex_lock(&philo->global->forks[philo->fork_left]);
	}
	else
	{
		pthread_mutex_lock(&philo->global->forks[philo->fork_left]);
		pthread_mutex_lock(&philo->global->forks[philo->fork_right]);
	}
	print_action(philo, 0);
}

void	*action(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (philo->global->n_philo != 1)
	{
		pick_up_fork(philo);
		start_eating(philo);
		pthread_mutex_lock(&philo->global->dead_lock);
		if (philo->global->all_meals || philo->global->philo_died)
		{
			pthread_mutex_unlock(&philo->global->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->global->dead_lock);
		start_sleeping(philo);
		print_action(philo, 3);
	}
	return (NULL);
}
