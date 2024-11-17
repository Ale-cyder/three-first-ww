#ifndef treII
#define treII
#define SIZ 50
#define FILE_WRITE_NAME "file_write.txt"
#define DUMP_FILE "_file.dot"
struct tre_
{
    void* left;
    void* rght;
    char str[SIZ];
};

int defen_world (tre_* tree);
int dump_three (tre_* tree);
int writer_ (tre_* tree);
int do_ (char* argv_1);
void* questioner (tre_* tree);
void* reader (FILE* fp);
int share (tre_* tree);
void* add_link (tre_* tree);
int delet_tree (tre_* tree);

#endif