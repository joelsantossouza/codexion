/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 00:13:44 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/21 10:10:43 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include <stdint.h>
# include "errors.h"

#define BUFFER_SIZE	1024 // TODO: CHANGABLE WITH COMPILATION

typedef struct s_queue
{
	uint64_t		data[BUFFER_SIZE];
	uint32_t		first;
	uint32_t		last;
}	t_queue;

static inline
__attribute__((always_inline))
int	enqueue(t_queue *queue, uint64_t data)
{
	const uint32_t	next = (queue->last + 1) % BUFFER_SIZE;

	if (next == queue->first)
		return (FULL_QUEUE_ERROR);
	queue->data[queue->last] = data;
	queue->last = next;
	return (SUCCESS);
}

static inline
__attribute__((always_inline))
int	queue_peek(t_queue *queue, uint64_t *data)
{
	const uint32_t	first = queue->first;

	if (first == queue->last)
		return (EMPTY_QUEUE_ERROR);
	*data = queue->data[first];
	return (SUCCESS);
}

#endif
