/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:56:47 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/05 18:02:10 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "coder.h"
#include "dongle_protocols.h"
#include "simulation_control.h"
#include "time_utils.h"

static
bool	is_first_on_queues(t_coder *me)
{
	t_dongle_queue	*left_queue;
	t_dongle_queue	*right_queue;
	uint32_t		head;

	left_queue = &me->left_dongle->queue;
	right_queue = &me->right_dongle->queue;

	pthread_mutex_lock(&left_queue->mutex);
	head = left_queue->head;
	if (head == left_queue->tail || left_queue->coders[head] != me)
		return (pthread_mutex_unlock(&left_queue->mutex), false);
	pthread_mutex_unlock(&left_queue->mutex);

	pthread_mutex_lock(&right_queue->mutex);
	head = right_queue->head;
	if (head == right_queue->tail || right_queue->coders[head] != me)
		return (pthread_mutex_unlock(&right_queue->mutex), false);
	pthread_mutex_unlock(&right_queue->mutex);

	return (true);
}

static
bool	are_dongles_available(t_coder *me)
{
	t_dongle	*first;
	t_dongle	*second;
	bool		are_available;
	uint64_t	now;

	first = me->left_dongle;
	second = me->right_dongle;
	if (first > second)
	{
		first = me->right_dongle;
		second = me->left_dongle;
	}

	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	now = millis();
	are_available =
		first->is_being_used == false
		&& now >= first->cooldown_end_ms
		&& second->is_being_used == false
		&& now >= second->cooldown_end_ms;
	pthread_mutex_unlock(&first->mutex);
	pthread_mutex_unlock(&second->mutex);

	return (are_available);
}

enum e_simulation_status	request_two_dongles(t_coder *coder)
{
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;

	left_dongle = coder->left_dongle;
	right_dongle = coder->right_dongle;
	pthread_mutex_lock(&coder->mutex);
	coder->enter_on_dongle_queue(&left_dongle->queue, coder);
	coder->enter_on_dongle_queue(&right_dongle->queue, coder);
	while (is_first_on_queues(coder) == false || are_dongles_available(coder) == false)
	{
		if (is_simulation_running() == false)
		{
			pthread_mutex_unlock(&coder->mutex);
			return (SIMULATION_STOPPED);
		}
		if (pthread_cond_timedwait(&coder->cond, &coder->mutex, &coder->deadline_ts) == ETIMEDOUT)
		{
			pthread_mutex_unlock(&coder->mutex);
			return (SIMULATION_STOPPED);
		}
	}
	set_as_being_used(left_dongle);
	set_as_being_used(right_dongle);
	dequeue(&left_dongle->queue);
	dequeue(&right_dongle->queue);
	pthread_mutex_unlock(&coder->mutex);
	return (SIMULATION_RUNNING);
}
