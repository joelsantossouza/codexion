/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:38:07 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/10 12:01:25 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "dongle_queue.h"

int	init_dongle_queue(t_dongle_queue *queue)
{
	queue->head = 0;
	queue->tail = 0;
	return (pthread_mutex_init(&queue->mutex, NULL));
}

int	destroy_dongle_queue(t_dongle_queue *queue)
{
	return (pthread_mutex_destroy(&queue->mutex));
}

enum e_enqueue_status	fifo_enqueue(t_dongle_queue *queue, t_coder *coder)
{
	uint32_t	curr_tail;
	uint32_t	next_tail;

	pthread_mutex_lock(&queue->mutex);
	curr_tail = queue->tail;
	next_tail = (curr_tail + 1) & QUEUE_MASK;
	if (next_tail == queue->head)
	{
		pthread_mutex_unlock(&queue->mutex);
		return (ENQUEUE_FULL);
	}
	queue->coders[curr_tail] = coder;
	queue->tail = next_tail;
	pthread_mutex_unlock(&queue->mutex);
	return (ENQUEUE_SUCCESS);
}

enum e_enqueue_status	edf_enqueue(t_dongle_queue *queue, t_coder *coder)
{
	uint32_t	curr_tail;
	uint32_t	next_tail;

	pthread_mutex_lock(&queue->mutex);
	curr_tail = queue->tail;
	next_tail = (curr_tail + 1) & QUEUE_MASK;
	if (next_tail == queue->head)
	{
		pthread_mutex_unlock(&queue->mutex);
		return (ENQUEUE_FULL);
	}
	queue->coders[curr_tail] = coder;
	queue->tail = next_tail;
	bubble_up_priority(queue, curr_tail);
	pthread_mutex_unlock(&queue->mutex);
	return (ENQUEUE_SUCCESS);
}

t_coder	*dequeue(t_dongle_queue *queue)
{
	uint32_t	head;
	t_coder		*dequeued_coder;

	pthread_mutex_lock(&queue->mutex);
	head = queue->head;
	if (head == queue->tail)
	{
		pthread_mutex_unlock(&queue->mutex);
		return (NULL);
	}
	dequeued_coder = queue->coders[head];
	queue->head = (head + 1) & QUEUE_MASK;
	pthread_mutex_unlock(&queue->mutex);
	return (dequeued_coder);
}
