/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_codexion_parser.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:21:57 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/27 17:39:14 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_CODEXION_PARSER_H
# define PRIVATE_CODEXION_PARSER_H

# include <stdbool.h>
# include "public_codexion_parser.h"

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

bool	is_str_numeric(const char *str);
int		nbrcmp(const char *nbr1, const char *nbr2);

#endif
