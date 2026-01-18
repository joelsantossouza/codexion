/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:10:53 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 01:27:11 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ZERO		"0"
# define INT_MAX	"2147483647"

# define PROGRAM_USAGE \
	"Usage:\n" \
	" - <number_of_coders>\n" \
	" - <time_to_burnout>\n" \
	" - <time_to_compile>\n" \
	" - <time_to_debug>\n" \
	" - <time_to_refactor>\n" \
	" - <number_of_compiles_required>\n" \
	" - <dongle_cooldown>\n" \
	" - <scheduler (\'fifo\' | \'edf\')>\n"

# define SUCCESS				0

// PARSING
# define ARGC_ERROR				1
# define ARGC_ERROR_MSG			"ERROR [1]: Invalid number of parameters (8 expected)\n"

# define SCHEDULER_ERROR		2
# define SCHEDULER_ERROR_MSG	"ERROR [2]: Invalid scheduler option <\'fifo\'|\'edf\'>\n"

# define NONNUMERIC_ERROR		3
# define NONNUMERIC_ERROR_MSG	"ERROR [3]: Non-integer input passed as parameter\n"

# define NEGATIVE_INT_ERROR		4
# define NEGATIVE_INT_ERROR_MSG	"ERROR [4]: Passed a negative number\n"

# define INT_OVERFLOW_ERROR		5
# define INT_OVERFLOW_ERROR_MSG	"ERROR [5]: Passed a number greater then INT_MAX\n"

// QUEUE
# define FULL_QUEUE_ERROR		6
# define FULL_QUEUE_ERROR_MSG	"ERROR [6]: Cannot add more data in full queue\n"

# define EMPTY_QUEUE_ERROR		7
# define EMPTY_QUEUE_ERROR_MSG	"ERROR [7]: Cannot get data from empty queue\n"

#endif
