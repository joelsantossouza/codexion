/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_protocols.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:32:28 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 16:40:13 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_PROTOCOLS_H
# define DONGLE_PROTOCOLS_H

# include <unistd.h>
# include <stdint.h>

typedef struct s_coder t_coder;

enum e_queue_config
{
	QUEUE_SIZE = 4,
	QUEUE_MASK = QUEUE_SIZE - 1
};

typedef struct s_dongle_queue
{
	t_coder		*coders[QUEUE_SIZE];
	uint32_t	head;
	uint32_t	tail;
}	t_dongle_queue;

enum e_enqueue_status
{
	ENQUEUE_SUCCESS,
	ENQUEUE_FULL
};

static inline
__attribute__((always_inline))
enum e_enqueue_status	enqueue(t_dongle_queue *queue, t_coder *coder)
{
	const uint32_t	curr_tail = queue->tail;
	const uint32_t	next_tail = (curr_tail + 1) & QUEUE_MASK;

	if (next_tail == queue->head)
		return (ENQUEUE_FULL);
	queue->coders[curr_tail] = coder;
	queue->tail = next_tail;
	return (ENQUEUE_SUCCESS);
}

static inline
__attribute__((always_inline))
t_coder	*dequeue(t_dongle_queue *queue)
{
	const uint32_t	head = queue->head;

	if (head == queue->tail)
		return (NULL);
	queue->head = (head + 1) & QUEUE_MASK;
	return (queue->coders[head]);
}

static inline
__attribute__((always_inline))
t_coder	*queue_head(t_dongle_queue *queue)
{
	const uint32_t	head = queue->head;

	if (head == queue->tail)
		return (NULL);
	return (queue->coders[head]);
}

typedef struct s_dongle
{
	const uint64_t	*cooldown;
	uint64_t		cooldown_end_ms;
	t_dongle_queue	queue;
}	t_dongle;

#endif
