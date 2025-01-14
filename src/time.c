/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:07:16 by dkros             #+#    #+#             */
/*   Updated: 2024/12/12 19:43:39 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead)
		status = 1;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (status);
}

int	ft_usleep(long int time, t_philo *philo)
{
	long int	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time)
		< time && !check_dead(philo))
	{
		usleep(100);
	}
	return (1);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	get_timestamp(t_data *data)
{
	return (get_current_time() - data->start_time);
}
