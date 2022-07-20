/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:04:48 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/20 19:38:32 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//This function prints when a philo dies
//And updates the status of our variable
//So the rest of the actions can also stop
//We need a slight delay to sync

void	start_dying(t_philo *philo, int time_to_die)
{
	//pthread_mutex_lock(&philo->data->dead_lock);
	printf(RED"[%d]Philosopher %d died\n" RESET, get_time() - philo->data->init_time + time_to_die, philo->philo_id);
	philo->data->philo_died = 1;
	//pthread_mutex_unlock(&philo->data->dead_lock);
}

//This helper function tells us the exact time
//Of death of a philo

int	time_of_death(t_philo *philo)
{
	int t_death;
	int l_meal;
	t_death = 0;
	l_meal = get_time() - philo->last_meal;
	t_death = philo->data->t_die - l_meal;
	return (t_death);
}

//Before taking up a fork we need to know
//If it's even worth it to pick it up
//By comparing the last time it ate with the time to die
int	will_die(t_philo *philo)
{
	int time_to_die = 0;
	time_to_die = time_of_death(philo);
	if ((get_time() - philo->last_meal) > philo->data->t_die)
	{	
		printf("%d", get_time() - philo->last_meal);
		start_dying(philo, time_to_die);
		return 1;
	}
	return 0;
}

//Check if any philo has died
int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->philo_died)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return 1;
	}
	if (will_die(philo))
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return 1;
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return 0;
}