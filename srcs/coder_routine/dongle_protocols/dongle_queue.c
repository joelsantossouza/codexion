/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:38:07 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 16:54:18 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "dongle_queue.h"

enum e_enqueue_status	enqueue(t_dongle_queue *queue, t_coder *coder)
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

t_coder	*queue_head(t_dongle_queue *queue)
{
	uint32_t	head;
	t_coder		*head_coder;

	pthread_mutex_lock(&queue->mutex);
	head = queue->head;
	if (head == queue->tail)
	{
		pthread_mutex_unlock(&queue->mutex);
		return (NULL);
	}
	head_coder = queue->coders[head];
	pthread_mutex_unlock(&queue->mutex);
	return (head_coder);
}
