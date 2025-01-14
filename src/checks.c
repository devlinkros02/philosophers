/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:17:46 by dkros             #+#    #+#             */
/*   Updated: 2024/12/12 20:21:13 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_mutex);
	dead = data->dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (dead);
}

int	philo_died(t_data *data, int i)
{
	long	current_time;
	long	time_since_last_meal;
	int		died;

	current_time = get_current_time();
	pthread_mutex_lock(&data->dead_mutex);
	time_since_last_meal = current_time - data->philos[i].last_meal;
	died = (time_since_last_meal > data->time_to_die);
	pthread_mutex_unlock(&data->dead_mutex);
	return (died);
}

void	handle_philo_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
	safe_print(data, i, "died", 1);
}

int	all_philos_ate_enough(t_data *data)
{
	int	i;

	if (data->must_eat <= 0)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	set_dead_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}
