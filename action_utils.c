/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:34:13 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/08/18 14:21:50 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	start;
	int				m_s;

	gettimeofday (&start, NULL);
	m_s = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (m_s);
}

int	time_diff(int past)
{
	int	curr;
	int	t_diff;

	curr = get_time();
	t_diff = (curr - past);
	return (t_diff);
}

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
		if (key == TAKE_FORK)
		{
			printf(PPL"[%d]Philosopher %d took a fork\n" RESET,
				time_diff(philo->global->time_init), philo->philo_id);
			printf(PPL"[%d]Philosopher %d took a fork\n" RESET,
				time_diff(philo->global->time_init), philo->philo_id);
		}
		else if (key == EAT)
			printf(CYN"[%d]Philosopher %d is eating\n"RESET,
				time_diff(philo->global->time_init), philo->philo_id);
		else if (key == SLEEP)
			printf(GRN"[%d]Philosopher %d is sleeping\n"RESET,
				time_diff(philo->global->time_init), philo->philo_id);
		else if (key == THINK)
			printf(YEL"[%d]Philosopher %d is thinking\n"RESET,
				time_diff(philo->global->time_init), philo->philo_id);
		else if (key == DIE)
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
