/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:30:14 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/28 18:40:21 by mda-cruz         ###   ########.fr       */
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

t_bool	is_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	get_time(void)
{
	struct timeval	start;
	int				m_s;

	gettimeofday (&start, NULL);
	m_s = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (m_s);
}

int	time_diff(int past)
{
	int	curr;
	int	t_diff;

	curr = get_time();
	t_diff = (curr - past);
	return (t_diff);
}

void	*ft_calloc(size_t num, size_t size)
{
	size_t *ptr;

	ptr = malloc(num * size);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, num * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}
