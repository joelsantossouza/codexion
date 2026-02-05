/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:41:45 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/05 18:33:22 by joesanto         ###   ########.fr       */
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

void	set_as_being_used(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_being_used = true;
	pthread_mutex_unlock(&dongle->mutex);
}

void	bubble_up_priority(t_dongle_queue *queue, uint32_t curr_idx)
{
	const uint32_t	head = queue->head;
	uint32_t		prev_idx;
	uint32_t		prev_deadline_ms;
	t_coder			*coder_temp;

	while (curr_idx != head)
	{
		prev_idx = (curr_idx - 1 + QUEUE_SIZE) & QUEUE_MASK;
		pthread_mutex_lock(&queue->coders[prev_idx]->mutex);
		prev_deadline_ms = queue->coders[prev_idx]->deadline_ms;
		pthread_mutex_unlock(&queue->coders[prev_idx]->mutex);
		if (queue->coders[curr_idx]->deadline_ms >= prev_deadline_ms)
			break ;
		coder_temp = queue->coders[curr_idx];
		queue->coders[curr_idx] = queue->coders[prev_idx];
		queue->coders[prev_idx] = coder_temp;
		curr_idx = prev_idx;
	}
}
