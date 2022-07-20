/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:19:20 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/20 19:30:34 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_fork(t_philo *philo)
{	
	if (check_death(philo))
		return 0;
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
		pthread_mutex_unlock(&philo->data->dead_lock);
	}
	
	else
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
		pthread_mutex_unlock(&philo->data->dead_lock);
	}
	if (check_death(philo))
	{
		let_go_forks(philo);
		return 0;
	}
	return 1;
}

int	philo_eat(t_philo *philo)
{
	if(check_death(philo))
	{
		let_go_forks(philo);
		return 0;
	}
	pthread_mutex_lock(&philo->data->dead_lock);
	printf(CYN"[%d]Philosopher %d is eating\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	philo->last_meal = get_time();
	(philo->n_meals)--;
	pthread_mutex_unlock(&philo->data->dead_lock);
	if (philo->data->n_eat > 0 && philo->n_meals >= philo->data->n_eat)
	{
		philo->data->meals++;
		if (philo->data->meals >= philo->data->n_philo)
		{	
			philo->data->philo_died = 1;
			let_go_forks(philo);
			return 0;
		}
	}
	if (philo->data->t_eat > philo->data->t_die)
	{
		check_death(philo);
		let_go_forks(philo);
		return 0;
	}
	sleepy_time(philo->data->t_eat);
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
	printf("are we here?");
	return 1;
}

int	philo_sleep(t_philo *philo)
{
	int	t_d = 0;
	if (check_death(philo))
		return 0;
	pthread_mutex_lock(&philo->data->dead_lock);
	printf(GRN"[%d]Philosopher %d is sleeping\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->dead_lock);
	t_d = time_of_death(philo);
	if (philo->data->t_sleep > t_d || philo->data->t_sleep > philo->data->t_die)
	{
		check_death(philo);
		return 0;
	}
	else
		sleepy_time(philo->data->t_sleep);
	if (check_death(philo))
		return 0;
	return (1);
}

int	philo_think(t_philo *philo)
{
	if (check_death(philo))
		return 0;
	pthread_mutex_lock(&philo->data->dead_lock);
	printf(YEL"[%d]Philosopher %d is thinking\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->dead_lock);
	if (check_death(philo))
		return 0;
	return 1;
}