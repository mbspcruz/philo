/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:19:20 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/21 20:52:20 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_fork(t_philo *philo)
{	
	int time = 0;
	if (check_death(philo))
		return 0;
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		time = get_time() - philo->data->init_time;
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		time = get_time() - philo->data->init_time;
	}
	if (check_death(philo))
	{
		let_go_forks(philo);
		return 0;
	}
	print_status(philo, 0, time);
	return 1;
}

int	philo_eat(t_philo *philo)
{
	if(check_death(philo))
	{
		let_go_forks(philo);
		return 0;
	}
	philo->last_meal = time_diff(philo->last_meal, get_time());
	print_status(philo, 1, time_diff(philo->data->init_time, get_time()));
	(philo->n_meals)--;
	if (philo->data->n_eat > 0 && philo->n_meals == 0)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->meals++;
		if (philo->data->meals >= philo->data->n_philo)
		{	
			philo->data->philo_died = 1;
			pthread_mutex_unlock(&philo->data->dead_lock);
			let_go_forks(philo);
			return 0;
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
	}
	if (philo->data->t_eat > philo->data->t_die)
	{
		check_death(philo);
		let_go_forks(philo);
		return 0;
	}
	while(time_diff(philo->data->init_time, get_time()) - philo->last_meal < philo->data->t_eat)
	{
		if(check_death(philo))
		{
			let_go_forks(philo);
			return(0);
		}
	}
	return 1;
}

int let_go_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	}
	if (check_death(philo))
		return 0;
	return 1;
}

int	philo_sleep(t_philo *philo)
{
	if (check_death(philo))
		return 0;
	print_status(philo, 2, get_time() - philo->data->init_time);
	int get_sleep = 0;
	get_sleep = time_diff(philo->data->init_time, get_time());
	if (philo->data->t_sleep > philo->data->t_die)
	{
		check_death(philo);
		return 0;
	}
	while(time_diff(philo->data->init_time, get_time()) - get_sleep < philo->data->t_sleep)
	{
		if (check_death(philo))
			return 0;
	}
	
	return (1);
}

int	philo_think(t_philo *philo)
{
	if (check_death(philo))
		return 0;
	print_status(philo, 3, get_time() - philo->data->init_time);
	if (check_death(philo))
		return 0;
	return 1;
}