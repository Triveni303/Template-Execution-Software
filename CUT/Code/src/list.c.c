#include "list.h" 

//data structures for template file

char *lines_list[MAX_LINES];
int num_lines=0;

//data structure for data file

char header_row[MAX_VARS][MAX_VAR_LEN];
char data_row_list[MAX_DATA_ROWS][MAX_VARS][MAX_VAR_LEN];
int num_data_rows = 0;
int num_fields = 0; //number of variables

/***********************This function consists replacement of word******************************/

void replace(char *str,const char *old_word,const char *new_word)
{
   char *pos,temp[MAX_LINE_LEN];
   int index = 0;
   int length = strlen(old_word);

   if(!strcmp(old_word,new_word))
   {
     return;
   }

while((pos = strstr(str,old_word)) !=NULL)
   {
     strcpy(temp,str);
     index = pos - str;
     str[index] = '\0';
     strcat(str,new_word);
     strcat(str,temp+index+length);
   }
}

/*******************************This function takes the template text file*********************/

int load_template_file(char *filename)
{
   FILE *fp;
    char line[MAX_LINE_LEN];

    fp = fopen(filename,"r");
    if(fp == NULL)
   {
     printf("%s:failure in opening file\n",filename);
     return FAILURE;
   }
  num_lines = 0;
  while(fgets(line,MAX_LINE_LEN, fp) != NULL)
  {
    //remove newline
    line[strlen(line) - 1] = '\0';
    lines_list[num_lines] = malloc(sizeof(char) * (strlen(line) + 1));
    strcpy(lines_list[num_lines],line);
    num_lines++;
  }
 fclose(fp);
 return SUCCESS;
}
/********************************Return how many fields were read*********************************/

int extract_tokens(char *line, char row[MAX_VARS][MAX_VAR_LEN])
{
  char *token = strtok(line,",");
  int i = 0;
   while(token != NULL)
  {
     strcpy(row[i], token);
     i++;
     token = strtok(NULL,",");
  }
   //printf("debug:extract_tokens:num of fields = %d\n",i);
    return i; // number of fieldsread
  }
/********************************Extract data file content****************************************/

int load_data_file(char *filename)
{
  FILE *fp;
  char line[MAX_LINE_LEN];
  char *ret_str;
  char data_row[MAX_VARS][MAX_VAR_LEN];
  int i,ret;

  fp = fopen(filename,"r");
  if(fp == NULL)
  {
    printf("%s:fail in opening file\n",filename);
    return FAILURE;
  }
  // Read 1st row. Header(names)
 ret_str = fgets(line,MAX_LINE_LEN,fp);
 if(ret_str == NULL)
  {
   //printf("%s:Unable to read header from file\n",filename);
   return FAILURE;
  }
  line[strlen(line) - 1] = '\0';
   num_fields = extract_tokens(line,header_row);
    i = 0;
    while(fgets(line,MAX_LINE_LEN, fp) != NULL)
    {
     // remove newline

    line[strlen(line) - 1] = '\0';
    ret = extract_tokens(line,data_row);
    if(ret != num_fields)
    {
      printf("Number of fields differ in data vs header rows\n");
         exit(1);
    }
   memcpy(data_row_list[i],data_row,sizeof(data_row));
   i++;
    }
   num_data_rows = i;
   fclose(fp);
   return SUCCESS;
   }
/*************************************Output file generation**************************************/

void process_replacements()
{
   
   char buffer[BUFFER_SIZE];
   FILE *fp;
   int i,r,v;
   for( r=0;r<num_data_rows;r++)
{
  char filename[FILE_SIZE];
  sprintf(filename,"template%d.txt",r+1);
  printf("filename = %s",filename);
  fp = fopen(filename,"w");

  //process one line at a time
  
 for( i=0;i<num_lines;i++)
{
  strcpy(buffer,lines_list[i]);

 //search replace all variables on that one line
   for( v=0;v<num_fields;v++)
{
  char dollar_field[MAX_VAR_LEN];
  sprintf(dollar_field, "%s%s", "$", header_row[v]);
  printf("debug:process_replacement: search=[%s],replace=[%s]\n",dollar_field,data_row_list[r][v]);
  replace(buffer,dollar_field,data_row_list[r][v]);
 }
fputs(buffer,fp);
}
fclose(fp);
}
}


