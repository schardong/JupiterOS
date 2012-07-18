#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG_MODE

struct initrd_file
{
  unsigned int magic;
  unsigned char name[64];
  unsigned int offset;
  unsigned int size;
};
typedef struct initrd_file rd_file;

const char outfile[] = "initrd.img";

#ifdef DEBUG_MODE
void test_img_file(int n_files)
{
  int i;
  //File opening and sanity checks.
  FILE* img = fopen(outfile, "r");
  if(img == NULL)
    return;

  //Verify the number of files on the filesystem.
  int read_n_files;
  fread(&read_n_files, sizeof(int), 1, img);
  if(n_files != read_n_files)
  {
    printf("Error! The number of files is different!\n\tread = %d\n\tcorrect = %d\n", read_n_files, n_files);
    goto close_file;
  }
  printf("Number of files in filesystem: %d\n", read_n_files);

  //Verify the headers of the files in the filesystem.
  rd_file* files = (rd_file*) malloc(sizeof(rd_file) * n_files);
  if(fread(files, sizeof(rd_file), n_files, img) == 0)
  {
    printf("Error while reading the file headers from the image.\n");
    goto free_data;
  }
  for(i = 0; i < n_files; i++)
    printf("i = %d\n\tfile name = %s\n\tfile offset = %d\n\tfile size = %d\n\tmagic number: %d\n\n", i, files[i].name, files[i].offset, files[i].size, files[i].magic);

  //Prints the content of each file on the screen.
  for(i = 0; i < n_files && !feof(img); i++)
  {
    unsigned char* buffer = (unsigned char*) malloc(sizeof(unsigned char) * files[i].size + 1);
    buffer[files[i].size] = '\0';
    if(fread(buffer, sizeof(unsigned char), files[i].size, img) == 0)
      goto free_buffer;
    printf("file %d contents: \n\t%s\n", i, buffer);
  free_buffer:
    free(buffer);
  }

 free_data:
  free(files);
 close_file:
  fclose(img);
};
#endif /* DEBUG_MODE */

int main(char argc, char **argv)
{
  int n_files = (argc - 1) / 2;
  rd_file* files;
  unsigned int offset = sizeof(unsigned int);
  int i;

  if(n_files == 0)
    return 1;
  files = (rd_file*) malloc(sizeof(rd_file) * n_files);
  printf("Number of files: %d\nSize of each file: %ld\n", n_files, sizeof(rd_file));

  for(i = 0; i < n_files; i++)
  {
    printf("Writing file %s->%s at 0x%x\n", argv[i*2+1], argv[i*2+2], offset);
    strcpy(files[i].name, argv[i * 2 + 2]);
    files[i].offset = offset;

    //Determine the size of the file and the offset of the next one.
    FILE* fp = fopen(argv[i * 2 + 1], "r");
    if(fp == NULL)
    {
      printf("File %s not found.\n", argv[i * 2 + 1]);
      return 1;
    }
    fseek(fp, 0, SEEK_END);
    files[i].size = ftell(fp);
    offset += files[i].size;
    fclose(fp);
    files[i].magic = 0xABCD;
  }

  printf("Offset = %d\n", offset);
  FILE* img = fopen(outfile, "w");
  if(img == NULL)
  {
    printf("Couldn't create the image file.\n");
    return 1;
  }
  fwrite(&n_files, sizeof(unsigned int), 1, img);
  fwrite(files, sizeof(rd_file), n_files, img);
  
  for(i = 0; i < n_files; i++)
  {
    FILE* input = fopen(argv[i * 2 + 1], "r");
    if(input == NULL)
    {
      printf("Error while opening the file %s for copy.\n", argv[i * 2 + 1]);
      return 1;
    }
    unsigned char* buffer = (unsigned char*) malloc(files[i].size);
    fread(buffer, 1, files[i].size, input);
    fwrite(buffer, 1, files[i].size, img);
    fclose(input);
    free(buffer);
  }

  fclose(img);
  free(files);
  
#ifdef DEBUG_MODE
  printf("<DEBUG>\n");
  test_img_file(n_files);
  printf("</DEBUG>\n");
#endif /* DEBUG_MODE */
    
  return 0;
}
