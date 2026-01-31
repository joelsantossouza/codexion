/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:41:45 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/31 16:57:28 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "dongle_protocols.h"
#include "codexion_config_control.h"
#include "codexion.h"

int	destroy_dongles(uint32_t ndongles, t_dongle dongles[ndongles])
{
	const uint32_t	last_dongle = ndongles - 1;
	uint32_t		i;

	if (ndongles == 0)
		return (0);
	i = -1;
	while (++i < last_dongle)
	{
		pthread_mutex_destroy(&dongles[i].mutex);
		destroy_dongle_queue(&dongles[i].queue);
	}
	pthread_mutex_destroy(&dongles[i].mutex);
	return (destroy_dongle_queue(&dongles[i].queue));
}

int	init_dongles(uint32_t ndongles, t_dongle dongles[ndongles])
{
	const t_codexion_config	*config = get_codexion_config();
	int						exit_status;
	uint32_t				i;

	i = -1;
	while (++i < ndongles)
	{
		exit_status = pthread_mutex_init(&dongles[i].mutex, NULL);
		if (exit_status != 0)
		{
			destroy_dongles(i, dongles);
			return (exit_status);
		}
		exit_status = init_dongle_queue(&dongles[i].queue);
		if (exit_status != 0)
		{
			pthread_mutex_destroy(&dongles[i].mutex);
			destroy_dongles(i, dongles);
			return (exit_status);
		}
		dongles[i].cooldown = &config->dongle_cooldown;
		dongles[i].cooldown_end_ms = 0;
	}
	return (0);
}
