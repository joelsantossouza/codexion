/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_fifo_turn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:03:14 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 20:19:01 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "coder.h"
#include "dongle_protocols.h"

static
bool	is_my_turn(t_coder *me)
{
	t_dongle_queue	*left_queue;
	t_dongle_queue	*right_queue;
	uint32_t		head;

	left_queue = &me->left_dongle->queue;
	right_queue = &me->right_dongle->queue;

	pthread_mutex_lock(&left_queue->mutex);
	head = left_queue->head;
	if (head == left_queue->tail || left_queue->coders[head] != me)
		return (false);
	pthread_mutex_unlock(&left_queue->mutex);

	pthread_mutex_lock(&right_queue->mutex);
	head = right_queue->head;
	if (head == right_queue->tail || right_queue->coders[head] != me)
		return (false);
	pthread_mutex_unlock(&right_queue->mutex);

	return (true);
}

enum e_simulation_status	wait_fifo_turn(t_coder *coder)
{
	pthread_mutex_lock();
	enqueue(&coder->left_dongle->queue, coder);
	enqueue(&coder->right_dongle->queue, coder);
	while (is_my_turn(coder) == false)
	{
		if (is_simulation_running() == false)
		{
			pthread_mutex_unlock();
			return (SIMULATION_STOPPED);
		}
		if (pthread_cond_timedwait())
		{
			pthread_mutex_unlock();
			return (SIMULATION_STOPPED);
		}
	}
	pthread_mutex_unlock();
	return (SIMULATION_RUNNING);
}
