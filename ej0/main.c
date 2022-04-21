#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

char *read_path(int argc, char *argv[]) {
  char *result = NULL;
  if (argc < 2) {
    printf("Faltan argumentos en el path");
    exit(EXIT_SUCCESS);
  }
  result = argv[1];
  return result;
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size) {
    FILE *file=NULL;
    file = fopen(path,"r");

    if(file == NULL) {
      printf("No existe el archivo a leer");
      exit(EXIT_FAILURE);
    }

    unsigned int i=0u;
    while (!feof(file) || i+1 > max_size) {
      fscanf(file,"%u '%c'\n", &(indexes[i]), &(letters[i]));
      i++;
    }
    if (i+1 > max_size) {
      printf("Array invalido");
      exit(EXIT_FAILURE);
    }
    fclose(file);
    return i;
}

void fill_array_sorted(unsigned int indexes[], char letters[], char sorted[], unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        for (unsigned int j = 0; j < length; j++) {
            if (indexes[j] == i) {
              sorted[i] = letters[j];
              j = length;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char *filepath=NULL;
    filepath = read_path(argc,argv);

    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0;

    length = data_from_file(filepath, indexes, letters, MAX_SIZE);
    printf("Cada arreglo contiene: %u elementos\n", length-1);
    printf("Un total de elementos: %u\n\n", (length*2)-2);

    fill_array_sorted(indexes, letters, sorted, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}
