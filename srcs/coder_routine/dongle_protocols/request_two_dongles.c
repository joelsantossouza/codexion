/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:56:47 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/05 19:05:32 by joesanto         ###   ########.fr       */
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
	t_dongle_queue	*first;
	t_dongle_queue	*second;
	uint32_t		head;

	first = &me->left_dongle->queue;
	second = &me->right_dongle->queue;
	if (first > second)
	{
		first = &me->right_dongle->queue;
		second = &me->left_dongle->queue;
	}

	pthread_mutex_lock(&first->mutex);
	head = first->head;
	if (head == first->tail || first->coders[head] != me)
		return (pthread_mutex_unlock(&first->mutex), false);
	pthread_mutex_unlock(&first->mutex);

	pthread_mutex_lock(&second->mutex);
	head = second->head;
	if (head == second->tail || second->coders[head] != me)
		return (pthread_mutex_unlock(&second->mutex), false);
	pthread_mutex_unlock(&second->mutex);

	return (true);
}

static
bool	are_dongles_available(t_coder *me)
{
	t_dongle	*first;
	t_dongle	*second;
	bool		are_available;

	first = me->left_dongle;
	second = me->right_dongle;
	if (first > second)
	{
		first = me->right_dongle;
		second = me->left_dongle;
	}

	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	are_available =
		first->is_being_used == false
		&& second->is_being_used == false;
	pthread_mutex_unlock(&first->mutex);
	pthread_mutex_unlock(&second->mutex);

	return (are_available);
}

static
enum e_simulation_status	wait_my_turn(t_coder *coder)
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
	dequeue(&left_dongle->queue);
	dequeue(&right_dongle->queue);
	pthread_mutex_unlock(&coder->mutex);
	return (SIMULATION_RUNNING);
}

static
enum e_simulation_status	wait_dongle_cooldown(const t_coder *coder, t_dongle *dongle)
{
	uint64_t	dongle_cooldown_end_ms;

	pthread_mutex_lock(&dongle->mutex);
	dongle_cooldown_end_ms = dongle->cooldown_end_ms;
	pthread_mutex_unlock(&dongle->mutex);
	if (millis() >= dongle_cooldown_end_ms)
		return (SIMULATION_RUNNING);
	return (monitored_wait_until(dongle_cooldown_end_ms, coder->deadline_ms));
}

enum e_simulation_status	request_two_dongles(t_coder *coder)
{
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;

	left_dongle = coder->left_dongle;
	right_dongle = coder->right_dongle;

	if (wait_my_turn(coder) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	if (wait_dongle_cooldown(coder, left_dongle) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	if (wait_dongle_cooldown(coder, right_dongle) == SIMULATION_STOPPED)
		return (SIMULATION_STOPPED);
	set_as_being_used(left_dongle);
	set_as_being_used(right_dongle);
	return (SIMULATION_RUNNING);
}
