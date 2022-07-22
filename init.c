/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:24:44 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/21 20:45:10 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setup_mutex(t_data *data)
{
	int count;
	
	count = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return(0);
	if (pthread_mutex_init(&data->dead_lock, NULL) != EXIT_SUCCESS)
		return(EXIT_FAILURE);
	if (pthread_mutex_init(&data->eat_lock, NULL) != EXIT_SUCCESS)
		return(EXIT_FAILURE);
	while(count < data->n_philo)
	{
		if(pthread_mutex_init(&data->forks[count], NULL) != EXIT_SUCCESS)
			return(EXIT_FAILURE);
		count++;
	}
	return (1);
}

t_philo	*setup_philo(t_data *data)
{
	int count;
	
	count = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	if(!data->philo)
		return 0;
	while (count < data->n_philo)
	{
		data->philo[count].philo_id = count + 1;
		data->philo[count].n_meals = data->n_eat;
		data->philo[count].data = data;
		data->philo[count].left_fork = (count + 1) % data->n_philo;
		data->philo[count].right_fork = count;
		data->philo[count].last_meal = data->init_time;
		count++;
	}
	return (data->philo);
}

t_data	*setup_args(int ac, char **av, t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	if(!data)
		return (0);
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if(ac == 6)
		data->n_eat = ft_atoi(av[5]);
	else
		data->n_eat = -1;
	data->init_time = get_time();
	data->philo_died = 0;
	return (data);
}

int	valid_args(int ac, char **av)
{
	int check = 1;
	if (ac != 5 && ac != 6)
		check = 0;
	else if (!is_digit(ac, av))
		check = 0;
	return (check);
}

t_data	*init_args(int ac, char ** av, t_data *data)
{
	data = setup_args(ac, av, data);
	if (!data)
		return (NULL);
	data->philo = setup_philo(data);
	if (!data->philo)
		return (NULL);
	if (setup_mutex(data) != 1)
		return (NULL);
	return (data);
}