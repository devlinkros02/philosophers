/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:57:32 by dkros             #+#    #+#             */
/*   Updated: 2024/12/12 20:22:27 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (is_simulation_dead(data))
			{
				safe_print(data, i, "died", 1);
				return (cleanup(data), NULL);
			}
			if (philo_died(data, i))
				return (handle_philo_death(data, i), NULL);
			i++;
		}
		if (all_philos_ate_enough(data))
			return (set_dead_flag(data), NULL);
		usleep(1000);
	}
	return (NULL);
}
