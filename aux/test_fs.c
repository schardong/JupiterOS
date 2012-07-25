#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct initrd_file
{
  unsigned int magic;
  unsigned char name[64];
  unsigned int offset;
  unsigned int size;
};
typedef struct initrd_file rd_file;

const char outfile[] = "initrd.img";

void test_img_file()
{
  int i;
  //File opening and sanity checks.
  FILE* img = fopen(outfile, "r");
  if(img == NULL)
    return;

  //Verify the number of files on the filesystem.
  int n_files;
  fread(&n_files, sizeof(int), 1, img);
  printf("Number of files in filesystem: %d\n", n_files);

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

int main(int argc, char** argv)
{
  test_img_file();
  return 0;
}
