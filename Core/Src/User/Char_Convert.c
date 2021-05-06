/*
 * Char_Convert.c
 *
 *  Created on: May 5, 2021
 *      Author: Tom HSieh
 */

#include "Char_Convert.h"

// Character to integer.
uint8_t Char_to_Int( uint8_t char_in )
{
	uint8_t ret_value;

	ret_value = 0;

	// '0' ~ '9'.
	if( char_in > 0x2f && char_in < 0x3a )
	{
		ret_value = char_in;
		ret_value -= 0x30;
	}
	// 'A' ~ 'F'
	else if( char_in > 0x40 && char_in < 0x47 )
	{
		ret_value = char_in;
		ret_value -= 0x41;
		ret_value += 10;
	}
	// 'a' ~ 'f'
	else if( char_in > 0x60 && char_in < 0x67 )
	{
		ret_value = char_in;
		ret_value -= 0x61;
		ret_value += 10;
	}

	return ret_value;
}
