// DEADFISH INTERPRETER

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  // Check arguments
  if (argc == 2) 
  {
    // Read from specified file
    readInputFile(argv[1]);
  }
  else if (argc > 2) 
  {
    printf("Too many arguments!\n");

    return 1;
  }
  else 
  {
    // Enter CMD mode
    printf("Entering cmd mode...\n");
    runCmd();
  }

  return 0;
}

void readInputFile(char filename[])
{
  FILE *input; // Input file

  input = fopen(filename, "r");

  if (input == NULL)
  {
    printf("Could not open file %s", filename);
    return;
  }

  // Initialize runtime values
  long value = 0;
  char c;

  bool comment = false;
  
  // Iterate through file
  for(c = fgetc(input); c != EOF; c = fgetc(input)){
    if(!comment){
      // Do operation corresponding with the current char
      switch (c) {
        case 'i':
          value++;
          break;
        case 'd':
          value--;
          break;
        case 's':
          value = value * value;
          break;
        case 'o':
          printf("%ld\n", value);
          break;
      }
      /*! TODO: Implement comments
       *
       * @todo Make all characters after a comment char (possibly #) be ignored.
       */
      if(value == -1 || value == 256){
        value = 0; // Gotta keep you on your toes :3
      }
    }
  } 

  fclose(input);
}

void runCmd()
{
  printf("Type 'q' to quit...\n");
  // Initialize values
  long value = 0;

  bool running = true;
  char c[1];

  printf("> "); // Print starting prompt

  while (running) {
    scanf("%c", c); // Get next input. ONLY GRABS FIRST CHARACTER EACH LOOP

    // Interpret input
    switch (c[0]) {
      case 'i':
        value++;
        break;
      case 'd':
        value--;
        break;
      case 's':
        value = value * value;
        break;
      case 'o':
        printf("%ld\n", value);
        break;
      case 'q':
        // Special quit condition
        running = false;
        break;
      case '\n':
        // Print new prompt each time a newline appears
        printf("> ");
        break;
    }
    if(value == -1 || value == 256){
      value = 0; // Gotta keep you on your toes again :3
    }
  }
}
