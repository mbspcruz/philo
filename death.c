/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:04:48 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/21 20:55:33 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//This function prints when a philo dies
//And updates the status of our variable
//So the rest of the actions can also stop
//We need a slight delay to sync

//This helper function tells us the exact time
//Of death of a philo

int	time_of_death(t_philo *philo)
{
	int t_death;
	int l_meal;
	t_death = 0;
	l_meal = philo->last_meal;
	t_death = philo->data->t_die - l_meal;
	//printf("time of death%d of philo %d\n",t_death, philo->philo_id);
	return (t_death);
}


int	will_die(t_philo *philo)
{
	if (time_diff(philo->data->init_time, get_time()) - philo->last_meal > philo->data->t_die)
	{	
		print_status(philo, 4, get_time() - philo->data->init_time);
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->philo_died = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return 1;
	}
	return 0;
}

//Check if any philo has died
int	check_death(t_philo *philo)
{
	//pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->philo_died)
	{
	//	pthread_mutex_unlock(&philo->data->dead_lock);
		return 1;
	}
	if (will_die(philo))
	{
		//pthread_mutex_unlock(&philo->data->dead_lock);
		return 1;
	}
	//pthread_mutex_unlock(&philo->data->dead_lock);
	return 0;
}

void print_status(t_philo *philo, int key, int time)
{
	if (philo->data->philo_died)
		return ;
	if (key == 0)
	{
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, time, philo->philo_id);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, time, philo->philo_id);
	}
	else if (key == 1)
		printf(CYN"[%d]Philosopher %d is eating\n" RESET, time, philo->philo_id);
	else if (key == 2)
		printf(GRN"[%d]Philosopher %d is sleeping\n" RESET, time, philo->philo_id);
	else if (key == 3)
		printf(YEL"[%d]Philosopher %d is thinking\n" RESET, time, philo->philo_id);
	else if (key == 4)
		printf(RED"[%d]Philosopher %d died\n" RESET, time, philo->philo_id);
}