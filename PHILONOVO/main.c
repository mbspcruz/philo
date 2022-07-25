/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:31:44 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/25 15:04:02 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sleepy_time(t_philo *philo, int time_action)
{
	pthread_mutex_lock(&philo->global->dead_lock);
	int start_time = get_time();
	while (!philo->global->philo_died)
	{
		if (time_diff(start_time) >= time_action)
		{
			//pthread_mutex_unlock(&philo->global->dead_lock);
			break;
		}
		pthread_mutex_unlock(&philo->global->dead_lock);
		usleep(10);
	}
	pthread_mutex_unlock(&philo->global->dead_lock);
}

void	check_death(t_global *global)
{
	if (global->n_philo == 1)
	{
		sleepy_time(global->philo, global->t_die);
		print_action(global->philo, 4);
		pthread_mutex_lock(&global->is_dead_lock);
		global->philo_died = 1;
		pthread_mutex_unlock(&global->is_dead_lock);
	}
	else
	{
		while(!global->all_meals)
		{
			int count = 0;
			while(count < global->n_philo && !global->philo_died)
			{
				pthread_mutex_lock(&global->eat_lock);
				if (time_diff(global->time_init) - global->philo[count].last_meal > global->t_die)
				{
					print_action(global->philo, 4);
					pthread_mutex_lock(&global->dead_lock);
					global->philo_died = 1;
					usleep(25000);
					pthread_mutex_unlock(&global->dead_lock);
				}
				pthread_mutex_unlock(&global->eat_lock);
				count++;
			//pthread_mutex_unlock(&global->is_dead_lock);
			}
			if (global->philo_died)
				break;
			count = 0;
			pthread_mutex_lock(&global->eat_lock);
			while (global->philo[count].n_meals >= global->n_eat && global->n_eat != -1 && count < global->n_philo)
				count++;
			pthread_mutex_unlock(&global->eat_lock);
			if (count == global->n_philo)
			{
			//pthread_mutex_lock(&global->is_dead_lock);
				global->all_meals = 1;
			//pthread_mutex_unlock(&global->dead_lock);
			}
		}
	}
}

void	print_action(t_philo *philo, int key)
{
	pthread_mutex_lock(&philo->global->print_lock);
	if (!philo->global->philo_died)
	{
		if (key == 0)
		{
			printf(PPL"[%d]Philosopher %d took a fork\n" RESET, time_diff(philo->global->time_init), philo->philo_id);
			printf(PPL"[%d]Philosopher %d took a fork\n" RESET, time_diff(philo->global->time_init), philo->philo_id);
		}
		else if (key == 1)
			printf(CYN"[%d]Philosopher %d is eating\n"RESET, time_diff(philo->global->time_init), philo->philo_id);
		else if (key == 2)
			printf(GRN"[%d]Philosopher %d is sleeping\n"RESET, time_diff(philo->global->time_init), philo->philo_id);
		else if (key == 3)
			printf(YEL"[%d]Philosopher %d is thinking\n"RESET, time_diff(philo->global->time_init), philo->philo_id);
		else if (key == 4)
			printf(RED"[%d]Philosopher %d died\n" RESET, time_diff(philo->global->time_init), philo->philo_id);
	}
	pthread_mutex_unlock(&philo->global->print_lock);
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

void	start_eating(t_philo *philo)
{
	print_action(philo, 1);
	pthread_mutex_lock(&philo->global->eat_lock);
	philo->last_meal = time_diff(philo->global->time_init);
	pthread_mutex_unlock(&philo->global->eat_lock);
	pthread_mutex_unlock(&philo->global->is_dead_lock);
	sleepy_time(philo, philo->global->t_eat);
	pthread_mutex_lock(&philo->global->eat_lock);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->global->eat_lock);
	drop_forks(philo);
}

void	start_sleeping(t_philo *philo)
{
	print_action(philo, 2);
	sleepy_time(philo, philo->global->t_sleep);
}

void	*action(void *p)
{
	t_philo *philo;
	philo = (t_philo *)p;
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->global->is_dead_lock);
	while(!philo->global->philo_died && philo->global->n_philo != 1)
	{ 
		
		pick_up_fork(philo);
		start_eating(philo);
		if (philo->global->all_meals)
			break;
		start_sleeping(philo);
		print_action(philo, 3);
		pthread_mutex_unlock(&philo->global->is_dead_lock);
	}
	pthread_mutex_unlock(&philo->global->is_dead_lock);
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
	check_death(global);
	if(!finish_destroy(global))
	{
		ft_putstr_fd("Error finishing", STDERR_FILENO);
		return 4;
	}
}