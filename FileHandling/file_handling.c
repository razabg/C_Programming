#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A simple struct to use in both text and binary examples */
typedef struct {
    int id;
    char name[50];
    float grade;
} Student;

/* ───────────────────────────────────────────────
   PART 1: Text file (human-readable)
   fopen with "w" creates/overwrites the file.
   fprintf writes formatted text, just like printf.
   fopen with "r" opens for reading.
   fscanf reads formatted text back into variables.
─────────────────────────────────────────────── */
void text_file_example() {
    Student s = {1, "Alice", 95.5f};

    /* --- Write --- */
    FILE *fp = fopen("student.txt", "w");
    if (!fp) {
        perror("fopen write");
        return;
    }
    /* Write each field as plain text separated by newlines */
    fprintf(fp, "%d\n%s\n%.2f\n", s.id, s.name, s.grade);
    fclose(fp);
    printf("[TEXT] Wrote: id=%d name=%s grade=%.2f\n", s.id, s.name, s.grade);

    /* --- Read --- */
    Student loaded = {0};
    fp = fopen("student.txt", "r");
    if (!fp) {
        perror("fopen read");
        return;
    }
    fscanf(fp, "%d %s %f", &loaded.id, loaded.name, &loaded.grade);
    fclose(fp);
    printf("[TEXT] Read:  id=%d name=%s grade=%.2f\n", loaded.id, loaded.name, loaded.grade);
}

/* ───────────────────────────────────────────────
   PART 2: Binary file (raw bytes, not human-readable)
   fopen with "wb" / "rb" — the 'b' flag means binary mode.
   fwrite dumps the raw bytes of the struct directly to disk.
   fread reads those raw bytes back into a struct.
   Binary is faster and preserves exact memory layout,
   but the file can't be opened as text meaningfully.
─────────────────────────────────────────────── */
void binary_file_example() {
    Student students[2] = {
        {2, "Bob",   88.0f},
        {3, "Carol", 76.5f}
    };

    /* --- Write --- */
    /* fwrite(pointer, size_of_one_element, count, file) */
    FILE *fp = fopen("students.bin", "wb");
    if (!fp) {
        perror("fopen binary write");
        return;
    }
    fwrite(students, sizeof(Student), 2, fp);
    fclose(fp);
    printf("[BIN]  Wrote 2 students to binary file.\n");

    /* --- Read --- */
    Student loaded[2] = {0};
    fp = fopen("students.bin", "rb");
    if (!fp) {
        perror("fopen binary read");
        return;
    }
    /* fread returns the number of elements successfully read */
    size_t count = fread(loaded, sizeof(Student), 2, fp);
    fclose(fp);

    printf("[BIN]  Read %zu students:\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("       id=%d name=%s grade=%.2f\n",
               loaded[i].id, loaded[i].name, loaded[i].grade);
    }

    /* Clean up the binary file after demo */
   // remove("students.bin");
    //remove("student.txt");
}

int main() {
    printf("=== Text File Example ===\n");
    text_file_example();

    printf("\n=== Binary File Example ===\n");
    binary_file_example();

    return 0;
}
