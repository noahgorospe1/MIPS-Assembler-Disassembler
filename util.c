/**
* @file util.c
* @brief Utility functions
* @author Cameron Hannay
*/


#include "include.h"


uint32_t bin_to_num(char *binary)
{
   uint32_t num = 0;


   while (*binary != '\0') {
       num <<= 1;
       if (*binary == '1')
           num |= 1;
       binary++;
   }


   return num;
}




const uint32_t ARG_AUTO     = 1;
const uint32_t ARG_REVERSE  = 2;


const uint32_t LINE_BUFF_SIZE = 4096;


// TODO: Add in documentation/comments since Old Jim forgot


//this method is used to handle command line arguments.
//It will set the appropriate flags for the program and return them as a bitfield.
//It also sets the input and output filenames if they are provided.
uint32_t command_line_args(int argc, char *argv[], char** in_filename, char** out_filename)
{
   // Initialize the result
   uint32_t result = 0;
   // Loop through the command line arguments
   for (int i = 1; i < argc; i++) {
       // Check for the flags and set the appropriate bits in the result
       if (!strcmp(argv[i], "-a"))
       // If the argument is "-a", set the ARG_AUTO bit
           result = result | ARG_AUTO;
           // If the argument is "-r", set the ARG_REVERSE bit
       else if (!strcmp(argv[i], "-r"))
           result = result | ARG_REVERSE;
           // If the argument is not a flag, check if it is an input or output filename
       else if (*in_filename == NULL)
           *in_filename = argv[i];
           // If the argument is not a flag and the input filename is already set, set the output filename
       else if (*out_filename == NULL)
           *out_filename = argv[i];
   }
   //return the result as a bitfield
   return result;
}
//This method is used to get the next line of input from the user.
//It will handle both interactive and automatic modes based on the flags set in the command line arguments.
//It will also handle input from a file if an input filename is provided.
void get_next_input(char* line, enum InteractiveState* int_state, uint32_t flags, char* in_filename, FILE** file)
{
   // Determine the mode based on the flags
   uint32_t auto_mode = (flags & ARG_AUTO) > 0;
   // Determine the reverse mode based on the flags
   uint32_t reverse_mode = (flags & ARG_REVERSE) > 0;
  
   char* str;
   // If we are in automatic mode and an input filename is provided, read from the file.
   if (auto_mode && in_filename != NULL) {
       // If the file is not already open, open it for reading
       if (*file == NULL)
           *file = fopen(in_filename, "r");
       str = fgets(line, LINE_BUFF_SIZE, *file);
       // If we reached the end of the file, close it and exit
       if (str == NULL && feof(*file)) {
           // If the file is open, close it before exiting
           if (*file != NULL)
               fclose(*file);
           exit(0);
       }
       // If there was an error reading from the file, print an error message, close the file if it is open, and exit
       else if (str == NULL && ferror(*file)) {
           //print an error message indicating that the line is invalid
           printf("Invalid line");
           // If the file is open, close it before exiting
           if (*file != NULL)
               fclose(*file);
           exit(1);
       }
       // If the line read from the file is just a newline character
       else if (*line == '\n') {
           //call get_next_input again to read the next line
           get_next_input(line, int_state, flags, in_filename, file);
       }
       // If the line read from the file does not contain a newline character or if there was an error reading from the file,
        //print an error message, close the file if it is open, and exit
       line[strcspn(line, "\n")] = 0;
       return;
   }
   // If we are in automatic mode and no input filename is provided, read from standard input
   else if (auto_mode && in_filename == NULL) {
       str = fgets(line, LINE_BUFF_SIZE, stdin);
       // If we reached the end of standard input, close it and exit
       if (str == NULL && feof(stdin)) {
           if (stdin != NULL)
               fclose(stdin);
           exit(0);
       }
       // If there was an error reading from standard input,
       else if (str == NULL && ferror(stdin)) {
           //print an error message,
           printf("Invalid line");
       //close standard input if it is open, and exit
           if (stdin != NULL)
               fclose(stdin);
           exit(1);
       }
       // If the line read from the file is just a newline character
       else if (*line == '\n') {
           //call get_next_input again to read the next line
           get_next_input(line, int_state, flags, in_filename, file);
       }
       // If the line read from standard input does not contain a newline character or if there was an error reading from standard input,
       if (strchr(line, '\n') == NULL || str == NULL) {
           //print an error message, close standard input if it is open, and exit
           printf("Invalid line");
           if (*file != NULL)
               fclose(*file);
           exit(1);
       }
       // Remove the newline character from the end of the line
       line[strcspn(line, "\n")] = 0;
       return;
   }
   // If we are not in automatic mode, enter an interactive loop to get input from the user
   else if (!auto_mode) {
       while (1) {
           char choice[10];
           // Based on the current interactive state, display the appropriate menu and get input from the user
           switch (*int_state) {
               // If the current interactive state is ROOT, display the main menu and get the user's choice
               case ROOT:
                   printf("\nPlease enter an option:\n\t(1) Assembly to Machine Code\n\t(2) Machine Code to Assembly\n\t(3) Quit\n\t(4) Corrupted Code Inspector\n");
                   printf("\n> ");
                   choice[0] = 0;
                   str = fgets(choice, sizeof(choice), stdin);
                   // If the user's input does not contain a newline character or if there was an error reading from standard input,
                   //print an error message and return to the main menu
                   if (strchr(choice, '\n') == NULL || str == NULL) {
                       printf("Invalid input");
                       *int_state = ROOT;
                       continue;
                   }
                   // Remove the newline character from the end of the user's input
                   choice[strcspn(choice, "\n")] = 0;
                   // If the user selects option 1, set the interactive state to ASM_TO_MACH
                   if (!strcmp(choice, "1")) {
                       *int_state = ASM_TO_MACH;
                   }
                   // If the user selects option 2, set the interactive state to MACH_TO_ASM
                   else if (!strcmp(choice, "2")) {
                       *int_state = MACH_TO_ASM;
                   }
                   // If the user selects option 3, close any open files and exit the program
                   else if (!strcmp(choice, "3")) {
                       if (*file != NULL)
                           fclose(*file);
                       exit(0);
                   }
                   // If the user selects option 4, set the interactive state to DEBUG
                   else if (!strcmp(choice, "4")) {
                       *int_state = DEBUG;
                   }
                   // If the user enters an invalid option, print an error message and return to the main menu
                   else {
                       printf("Invalid input");
                       *int_state = ROOT;
                   }
                   break;
                   // If the current interactive state is MACH_TO_ASM, display the machine code to assembly menu and get the user's choice
               case MACH_TO_ASM:
                   printf("\nPlease select an option:\n\t(1) Hexadecimal to Assembly\n\t(2) Binary to Assembly\n\t[3] Main Menu\n");
                   printf("\n> ");
                   choice[0] = 0;
                   str = fgets(choice, sizeof(choice), stdin);
                   // If the user's input does not contain a newline character or if there was an error reading from standard input,
                   if (strchr(choice, '\n') == NULL || str == NULL) {
                       printf("Invalid input");
                       *int_state = MACH_TO_ASM;
                       continue;
                   }
                   // Remove the newline character from the end of the user's input
                   choice[strcspn(choice, "\n")] = 0;
                   // If the user selects option 1, set the interactive state to HEX_TO_ASM
                   if (!strcmp(choice, "1")) {
                       *int_state = HEX_TO_ASM;
                   }
                   // If the user selects option 2, set the interactive state to BIN_TO_ASM
                   else if (!strcmp(choice, "2")) {
                       *int_state = BIN_TO_ASM;
                   }
                   // If the user selects option 3, set the interactive state to ROOT
                   else if (!strcmp(choice, "3")) {
                       *int_state = ROOT;
                   }
                   // If the user enters an invalid option, print an error message and return to the machine code to assembly menu
                   else {
                       printf("Invalid input");
                       *int_state = MACH_TO_ASM;
                   }
                   break;
               // If the current interactive state is ASM_TO_MACH, prompt the user to enter a line of assembly code and get the input
               case ASM_TO_MACH:
                   printf("\n Enter a line of assembly:\n> ");
                   str = fgets(line, LINE_BUFF_SIZE, stdin);
                   // If the user's input does not contain a newline character or if there was an error reading from standard input,
                   //print an error message and return to the main menu
                   if (strchr(line, '\n') == NULL || str == NULL) {
                       printf("Invalid input");
                       continue;
                   }
                   // Remove the newline character from the end of the user's input
                   line[strcspn(line, "\n")] = 0;
                   // If the user enters an empty line, return to the main menu
                   if (line[0] == 0) {
                       *int_state = ROOT;
                   }
                   return;
               // If the current interactive state is HEX_TO_ASM, prompt the user to enter a line of hexadecimal machine code and get the input
               case HEX_TO_ASM:
                   printf("\n Enter Hex:\n> ");
                   str = fgets(line, LINE_BUFF_SIZE, stdin);
                   // If the user's input does not contain a newline character or if there was an error reading from standard input,
                   if (strchr(line, '\n') == NULL || str == NULL) {
                       printf("Invalid input");
                       continue;
                   }
                   // Remove the newline character from the end of the user's input
                   line[strcspn(line, "\n")] = 0;
                   // If the user enters an empty line, return to the machine code to assembly menu
                   if (line[0] == 0) {
                       *int_state = MACH_TO_ASM;
                   }
                   return;
               // If the current interactive state is BIN_TO_ASM, prompt the user to enter a line of binary machine code and get the input
               case BIN_TO_ASM:
                   printf("\n Enter Binary:\n> ");
                   str = fgets(line, LINE_BUFF_SIZE, stdin);
                   // If the user's input does not contain a newline character or if there was an error reading from standard input,
                   if (strchr(line, '\n') == NULL || str == NULL) {
                       printf("Invalid input");
                       continue;
                   }
                   // Remove the newline character from the end of the user's input
                   line[strcspn(line, "\n")] = 0;
                   // If the user enters an empty line, return to the machine code to assembly menu
                   if (line[0] == 0) {
                       *int_state = MACH_TO_ASM;
                   }
                   return;
                   // If the current interactive state is DEBUG, prompt the user to enter a line of broken binary code and get the input
               case DEBUG:
                   printf("\n Enter Broken Binary:\n> ");
                   str = fgets(line, LINE_BUFF_SIZE, stdin);
                   // If the user's input does not contain a newline character or if there was an error reading from standard input,
                   if (strchr(line, '\n') == NULL || str == NULL) {
                       printf("Invalid input");
                       continue;
                   }
                   // Remove the newline character from the end of the user's input
                   line[strcspn(line, "\n")] = 0;
                   // If the user enters an empty line, return to the main menu
                   if (line[0] == 0) {
                       *int_state = ROOT;
                   }
                  
                   return;


           }
       }
   }
   // If none of the above conditions are met, simply return without doing anything
   else {
       return;
   }
}
