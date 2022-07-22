/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:29:29 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/21 22:17:32 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef int t_bool;
#define TRUE 1
#define FALSE 0

typedef struct s_global
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eat;
	t_philo	*philo;
	pthread_mutex_t *forks;
}				t_global;

typedef struct s_philo
{
	int philo_id;
	int fork_left;
	int fork_right;
}				t_philo;

void	ft_putstr_fd(char *str, int fd);
long	ft_atoi(const char *str);
#endif