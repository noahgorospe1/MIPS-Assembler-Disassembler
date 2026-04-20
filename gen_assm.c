/**
 * @file gen_assm.c
 * @brief Code to generate assembly from a parse result
 * @author Cameron Hannay

 */

#include "include.h"

// TODO: Add in documentation/comments since Old Jim forgot


/**
* @brief Generates an assembly instruction string from a parse result.
 * @param buf Buffer to write the assembly instruction to.
 * @param size Size of the buffer.
 * @param parsed The parse result to generate the assembly from.
 * @param error Pointer to string to hold error message if an error occurs. Set to NULL if no error occurs.
*/
void generate_assembly(char *buf, size_t size, struct assm_parse_result parsed, char **error)
{
	// Initialize error to NULL
	*error = NULL;

	// Stores string representation of up to 4 args
	char args[4][8]; 

	// Number of arguments processed
	size_t arg_count;

	// Used to convert unsigned immediates to signed for display
	union signedness_switch_trick signedness;

	/**
	* Convert parsed args into string form
	*/
	for (arg_count = 0; arg_count < 4 && parsed.types[arg_count] != NONE; arg_count++) {
		switch (parsed.types[arg_count]) {
		case REGISTER:
			// Copy Register name from lookup table
			strcpy(args[arg_count], registers[parsed.vals[arg_count]]);
			break;
		case IMMEDIATE:
			// Convert value to signed 16-bit integer and format as "#value"
			signedness.u = (uint16_t) parsed.vals[arg_count];
			sprintf(args[arg_count], "#%d", signedness.i);
			break;
		case TARGET:
			// Target args are not supported
			*error = "Generating assembly with targets is unsupported.";
			return;
		case NONE:
			// No arg (end of args)
			break;
		}
	}

	/**
	* Format strings based on number of args
	* Index corresponds to arg count
	*/
	char *formats[5] = {
		"%s",
		"%s %s",
		"%s %s, %s",
		"%s %s, %s, %s",
		"%s %s, %s, %s, %s"
	};

	/**
	*  Write formatted instruction into buffer
	*/
	int needed = snprintf(buf, size, formats[arg_count], parsed.op_name,
			args[0], args[1], args[2], args[3]);

	/**
	*  Check if buffer was large enough
	*/
	if (needed >= size)
		*error = "Buffer too small for assembly instruction.";
}
