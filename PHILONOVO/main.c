/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:31:44 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/22 17:55:29 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dying(t_philo *philo, int time_to_die)
{
	usleep(time_to_die * 1000);
	pthread_mutex_lock(&philo->global->dead_lock);
	printf(RED"[%d]Philosopher %d died\n" RESET, time_diff(philo->global->time_init), philo->philo_id);
	philo->global->philo_died = 1;
	pthread_mutex_unlock(&philo->global->dead_lock);
}

int	get_time_until_death(t_philo *philo)
{
	int time_until_dead = 0;
	int time_since_last_meal = 0;
	time_since_last_meal = time_diff(philo->last_meal);
	time_until_dead = philo->global->t_die - time_since_last_meal;
	return (time_until_dead);
}

t_bool	will_die_before_fork(t_philo *philo)
{
	int time_to_die = 0;
	time_to_die = get_time_until_death(philo);
	if (philo->global->n_philo == 1 || philo->global->philo_died)
	{
		start_dying(philo, time_to_die);
		return TRUE;
	}

	return (FALSE);
}

t_bool	pick_up_fork(t_philo *philo)
{
	int time = 0;
	if (will_die_before_fork(philo))
		return FALSE;
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->global->forks[philo->fork_right]);
		pthread_mutex_lock(&philo->global->forks[philo->fork_left]);
		time = time_diff(philo->global->time_init);
	}
	else
	{
		pthread_mutex_lock(&philo->global->forks[philo->fork_left]);
		pthread_mutex_lock(&philo->global->forks[philo->fork_right]);
		time = time_diff(philo->global->time_init);
	}
	pthread_mutex_lock(&philo->global->dead_lock);
	printf(PPL"[%d]Philosopher %d took a fork\n" RESET, time, philo->philo_id);
	printf(PPL"[%d]Philosopher %d took a fork\n" RESET, time, philo->philo_id);
	pthread_mutex_unlock(&philo->global->dead_lock);
	return(TRUE);
}

t_bool	drop_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->global->forks[philo->fork_right]);
		pthread_mutex_unlock(&philo->global->forks[philo->fork_left]);
	}
	else
	{
		pthread_mutex_lock(&philo->global->forks[philo->fork_left]);
		pthread_mutex_lock(&philo->global->forks[philo->fork_right]);
	}
}

t_bool	start_eating(t_philo *philo)
{
	if (philo->global->philo_died)
	{
		drop_forks(philo);
		return FALSE;
	}
}

void	*action(void *p)
{
	t_philo *philo;
	philo = (t_philo *)p;
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while(philo->n_meals != 0)
	{ 
		if (!pick_up_fork(philo))
			break;
		if (!start_eating(philo))
			break;
	}
		
	return NULL;
}

int	main(int ac, char **av)
{
	t_global *global;
	global = NULL;

	if (!check_args(ac, av))
	{
		ft_putstr_fd("Error with args", STDERR_FILENO);
		return 1;
	}
	if (!init_global(global, ac, av))
	{
		ft_putstr_fd("Error with philo assignement", STDERR_FILENO);
		return 2;
	}
	global = init_global(global, ac, av);
	if (!init_simul(global))
	{
		ft_putstr_fd("Error creating threads", STDERR_FILENO);
		return 3;
	}
}