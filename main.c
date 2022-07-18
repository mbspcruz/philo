/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:18:53 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/18 00:50:11 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function for the philo to grab a fork
//Needs to first check if it will have time to eat before dying
//If philo dies he won't pick up the fork
//If he has the time he will pick up the fork and depends if its an odd
//Or even ID
void	sleepy_time(int time)
{
	int current = 0;
	current = get_time();
	while((get_time() - current) < time)
		usleep (time / 10);
}

int	time_of_death(t_philo *philo)
{
	int t_death;
	int l_meal;
	t_death = 0;
	l_meal = get_time() - philo->last_meal;
	t_death = philo->data->t_die - l_meal;
	if (t_death < 0)
		t_death = 0;
	return (t_death);
}

void	start_dying(t_philo *philo, int time_to_die)

{
	pthread_mutex_lock(&philo->data->dead_lock);
	sleepy_time(time_to_die);
	printf(RED"[%d]Philosopher %d died\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	philo->data->philo_died = 1;
	pthread_mutex_unlock(&philo->data->dead_lock);
}

int	will_not_die_bf_fork(t_philo *philo)
{
	int time_to_die = 0;
	if(philo->data->philo_died > 0)
		return 0;
	time_to_die = time_of_death(philo);
	
	if (philo->data->n_philo == 1 || time_to_die == 0)
	{
		start_dying(philo, time_to_die);
		return 0;
	}
	
	return 1;
}

int	pick_up_fork(t_philo *philo)
{	
	if (!will_not_die_bf_fork(philo))
		return 0;
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	}
	
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		printf(PPL"[%d]Philosopher %d took a fork\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	}
	
	return 1;
}

int	philo_eat(t_philo *philo)
{
	if(philo->data->philo_died > 0)
		return 0;
	printf(CYN"[%d]Philosopher %d is eating\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_meal = get_time();
	(philo->n_meals)++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	if (philo->data->n_eat > 0 && philo->n_meals >= philo->data->n_eat)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->eat_lock);
		philo->data->meals++;
		if (philo->data->meals >= philo->data->n_philo)
		{
			philo->data->philo_died = 1;
			return 0;
		}
		pthread_mutex_unlock(&philo->data->eat_lock);
	}
	sleepy_time(philo->data->t_eat);
	return 1;
}



int	philo_sleep(t_philo *philo)
{
	int	t_d = 0;
	if(philo->data->philo_died > 0)
		return 0;
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	printf(GRN"[%d]Philosopher %d is sleeping\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	t_d = time_of_death(philo);
	if (philo->data->t_sleep > t_d)
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
	if(philo->data->philo_died > 0)
		return 0;
	printf(YEL"[%d]Philosopher %d is thinking\n" RESET, get_time() - philo->data->init_time, philo->philo_id);
	return 1;
}

void *action(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	if(philo->philo_id % 2 == 0)
		usleep(100);
	while(1)
	{
		if (pick_up_fork(philo) != 1)
			break;
		if (philo_eat(philo) != 1)
			break;
		if (philo_sleep(philo) != 1)
			break;
		if (philo_think(philo) != 1)
			break;
	}
	return 0;
}

int	start_sim(t_data *data)
{
	int i;

	i = 0;
	while(i < data->n_philo)
	{
		if(pthread_create(&data->philo[i].thread, NULL, &action, &data->philo[i]))
			return (0);
		i++;
	}
	i = 0;
	while(i < data->n_philo)
	{

		if(pthread_join(data->philo[i].thread, NULL))
			return (0);
		i++;
	}
	return(1);
}

int	main(int ac, char **av)
{
	t_data *data = NULL;
	
	if (!init_args(ac, av, data))
	{
		ft_putstr_fd("Error\nInvalid arguments\n", STDERR_FILENO);
		return(1);
	}
	data = init_args(ac, av, data);
	if (!start_sim(data))
	{
		ft_putstr_fd("Error\nProblem creating threads\n", STDERR_FILENO);
		return(2);
	}
	return 0;
}