/**
 * @file parser.c
 * @brief Parses user input of assembly and determines what kind of instruction it is to be converted into
 * @author Cameron Hannay
 */

#include "include.h"

/**
 * @brief Takes the string and turns each character to uppercase
 * @param operand String to convert to uppercase
 */

 /*converts a string into uppercase */
static void uppercase(char *operand);

/**
 * @brief Takes the string compares it with each register type to find a match
 * @param operand String to lookup
 */

 /*looks up a regester name and retunrs its index, or throws an serror on failure */
static uint32_t reg_lookup(char *str, char** error);

/**
 * @brief Removes whitespace from a string
 * @param str String to remove whitespace from
 */

 /*removes all whitespace from the string */
static void remove_space(char* str);

/**
 * @brief Removes pound symbol from string
 * @param str String to remove pound symbol from
 */

 /*removes all # from string */
static void remove_pound(char* str);

// TODO: Add in documentation/comments since Old Jim forgot

uint32_t parse_assembly(char *line, char **error)
{
    struct assm_parse_result result;
    *error = NULL;
    size_t length;
    char* opp_name;

    /*finds the legnth of the opcode */
    length = strcspn(line, " ");

    /*allocates space for the opcode string */
    opp_name = (char*)malloc(sizeof(char) * (length + 1));

    if (opp_name == NULL)
    {
        *error = "Memory not allocated.";
        return UNDEFINED;
    }

    /*copys the opcode into a new buffer */
    strncpy(opp_name, line, length);

    opp_name[length] = '\0';
        
    /*sets the opcode to be uppercase to be consistent */
    uppercase(opp_name);

    result.op_name = opp_name;

    /*advances pointer past the opcode to start operand list */
    line += length;

    /* makes a token with the operands sperated byma comma*/
    char* token = strtok(line, ",");
    size_t arg;
    for (arg = 0; token != NULL; arg++)
    {
        /* removes any whitespace inside the operant*/
        remove_space(token);

        // FIXED: parser now accepts immediates without '#'
        /* makes any operand that begins with # and immediate operand*/
        //added allows for negative immediates and immediates that are just numbers without the #, since some instructions like lui allow for that
        if (token[0] == '#' || isdigit(token[0]) || token[0] == '-')
        {
            result.types[arg] = IMMEDIATE;
            /*removes the # before passing the number */
            remove_pound(token);
            char* end_ptr;
            
	    union signedness_switch_trick signedness;
            /*pass as an signed 16 bit, then make it an unsigned */
            signedness.i = (int16_t) strtol(token, &end_ptr, 10);
            result.vals[arg] = signedness.u;

            /*vailidates that the token is valid */
            if(end_ptr == token || *end_ptr != '\0')
            {
                *error = "Improperly formatted immediate.";
                free(opp_name);
                opp_name = NULL;
                return UNDEFINED;
            }
        }
        /*register openerand begins is $ */
        else if (token[0] == '$')
        {
            result.types[arg] = REGISTER;
            /*look up registers index, throws an error if invalid */
            result.vals[arg] = reg_lookup(token, error);
            if (*error != NULL) {
                free(opp_name);
                opp_name = NULL;
                return UNDEFINED;
            }
        }
        else
        {
            /* throws the error if its an unsupported operand type or if they are not suppored yet*/
            *error = "Argument isn't register or immediate (targets not yet supported).";
            free(opp_name);
            opp_name = NULL;
            return UNDEFINED; 
        }
        /*just moves to the next operand */
        token = strtok(NULL, ",");
    }

    /*fills all the unused operand slots with NONE or UNDEFINED  */
    for (;arg < 4; arg++) {
        result.types[arg] = NONE;
        result.vals[arg] = UNDEFINED;
    }

    /*coverts parsed result into machine code */
    uint32_t new_val = convert_to_machine_code(result, error);
    
    /* frees the opcode string now that its converted*/
    free(opp_name);
    opp_name = NULL;

    return new_val;
}

static void uppercase(char *operand)
{
    size_t length = strlen(operand);
    /* sets every character to uppercase*/
    for (size_t i = 0; i < length; i++)
    {
        operand[i] = toupper((unsigned char) operand[i]);
    }
}

static void remove_pound(char* str)
{
    int count = 0;

    /* compacts string by skipping the #'s*/
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != '#')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

static void remove_space(char* str)
{
    int count = 0;

    /* compacts string by removing all whitespace*/
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

static uint32_t reg_lookup(char *str, char** error)
{
    /*LINEAR SEARCHES through the register name table */
    for (uint32_t i = 0; i < sizeof(registers) / sizeof(char *); i++)
    {
        if (strcmp(registers[i],str) == 0)
        {
            return i;
        }
    }


    /* the register was not found*/
    *error = "Register not found.";
    return UNDEFINED;
}
