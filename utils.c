/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:30:20 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/19 15:51:32 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (res > 9223372036854775807UL && sign == 1)
		return (-1);
	else if (res > 9223372036854775808UL && sign == -1)
		return (0);
	return (sign * res);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	get_time()
{
	struct timeval start;
		if(gettimeofday(&start, NULL))
			return (0);
	return((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

void	sleepy_time(int time)
{
	int current = 0;
	current = get_time();
	while((get_time() - current) < time)
		usleep (time / 10);
}

void	free_clean(t_data *data)
{
	int i = 0;
	if (data->philo && data->n_philo > 0)
	{
		i = 0;
		while(i < data->n_philo)
		{
			pthread_mutex_destroy(&(data->forks[i]));
			i++;
		}
		free(data->forks);
		free(data->philo);
		pthread_mutex_destroy(&data->dead_lock);
		pthread_mutex_destroy(&data->eat_lock);
		free(data);
	}
}