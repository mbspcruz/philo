/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:19:20 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/19 20:18:50 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_fork(t_philo *philo)
{	
	if (!will_not_die_bf_fork(philo))
		return 0;
	if (philo->philo_id % 2 == 0 && !check_death(philo))
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	}
	
	else if (!check_death(philo))
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	}
	if (check_death(philo))
		return 0;
	return 1;
}

int	philo_eat(t_philo *philo)
{
	int t_d = 0;
	if(!check_death(philo))
		printf(CYN"[%d]Philosopher %d is eating\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_meal = get_time();
	(philo->n_meals)++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	if (philo->data->n_eat > 0 && philo->n_meals >= philo->data->n_eat)
	{
		pthread_mutex_lock(&philo->data->eat_lock);
		philo->data->meals++;
		if (philo->data->meals >= philo->data->n_philo)
		{	
			pthread_mutex_lock(&philo->data->dead_lock);
			philo->data->philo_died = 1;
			let_go_forks(philo);
			pthread_mutex_unlock(&philo->data->dead_lock);
			return 0;
		}
		pthread_mutex_unlock(&philo->data->eat_lock);
	}
	t_d = time_of_death(philo);
	if (philo->data->t_eat > philo->data->t_die)
	{
		let_go_forks(philo);
		start_dying(philo, t_d);
		return 0;
	}
	else
		sleepy_time(philo->data->t_eat);
	let_go_forks(philo);
	return 1;
}

void let_go_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);

}

int	philo_sleep(t_philo *philo)
{
	int	t_d = 0;
	if (philo->data->philo_died == 0)
		printf(GRN"[%d]Philosopher %d is sleeping\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	t_d = time_of_death(philo);
	if (philo->data->t_sleep > t_d || philo->data->t_sleep > philo->data->t_die)
	{
		start_dying(philo, t_d);
		return 0;
	}
	else
		sleepy_time(philo->data->t_sleep);
	return (1);
}

int	philo_think(t_philo *philo)
{
	if (!check_death(philo))
		printf(YEL"[%d]Philosopher %d is thinking\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	return 1;
}