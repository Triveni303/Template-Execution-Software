#include "list.h" 

int main(int argc, char *argv[])
{
 
  //calling different functions

  load_template_file(argv[1]);
  load_data_file(argv[2]);
  process_replacements();
}
