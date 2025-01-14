/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:57:05 by dkros             #+#    #+#             */
/*   Updated: 2024/12/12 19:45:54 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_data *data, int id, const char *msg, int force_print)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (!data->dead || force_print)
	{
		pthread_mutex_lock(&data->write_mutex);
		printf("%lld %d %s\n", get_timestamp(data), id + 1, msg);
		pthread_mutex_unlock(&data->write_mutex);
	}
	pthread_mutex_unlock(&data->dead_mutex);
}
