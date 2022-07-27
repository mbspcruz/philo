/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:34:13 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/27 19:16:51 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleepy_time(t_philo *philo, int time_action)
{
	int	start_time;

	start_time = get_time();
	while (time_diff(start_time) < time_action)
	{	
		pthread_mutex_lock(&philo->global->dead_lock);
		if (philo->global->philo_died)
		{
			pthread_mutex_unlock(&philo->global->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->global->dead_lock);
		usleep(10);
	}
}

void	print_action(t_philo *philo, int key)
{
	pthread_mutex_lock(&philo->global->print_lock);
	if (!philo->global->philo_died)
	{
		if (key == 0)
		{
			printf(PPL"[%d]Philosopher %d took a fork\n" RESET,
				time_diff(philo->global->time_init), philo->philo_id);
			printf(PPL"[%d]Philosopher %d took a fork\n" RESET,
				time_diff(philo->global->time_init), philo->philo_id);
		}
		else if (key == 1)
			printf(CYN"[%d]Philosopher %d is eating\n"RESET,
				time_diff(philo->global->time_init), philo->philo_id);
		else if (key == 2)
			printf(GRN"[%d]Philosopher %d is sleeping\n"RESET,
				time_diff(philo->global->time_init), philo->philo_id);
		else if (key == 3)
			printf(YEL"[%d]Philosopher %d is thinking\n"RESET,
				time_diff(philo->global->time_init), philo->philo_id);
		else if (key == 4)
			printf(RED"[%d]Philosopher %d died\n" RESET,
				time_diff(philo->global->time_init), philo->philo_id);
	}
	pthread_mutex_unlock(&philo->global->print_lock);
}

void	drop_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->global->forks[philo->fork_right]);
		pthread_mutex_unlock(&philo->global->forks[philo->fork_left]);
	}
	else
	{
		pthread_mutex_unlock(&philo->global->forks[philo->fork_left]);
		pthread_mutex_unlock(&philo->global->forks[philo->fork_right]);
	}
}
