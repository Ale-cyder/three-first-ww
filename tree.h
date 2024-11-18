#ifndef treII
#define treII
#define SIZ 50

#define DUMP_HTML "log.html"
#define DUMP_FILE "folder_log_png/_log.dot"
//                              15^   ^19
#define POSICION_WITH_NUMBER_PNG 15
#define POSITION_WITH_FORMAT_FILE 19
#define SIZE_CMD 100
#define FILE_WRITE_NAME "file_write.txt"
#define PUTS(str) {int once = 0; while (str[once] != '\0') putchar (str[once++]);}
struct tre_
{
    void* left;
    void* rght;
    char str[SIZ];
};

int difference_world (tre_* tree);
int write_branch_in_dot (tre_* tree, FILE* fp);
int defen_world (tre_* tree);
int dump_three (tre_* tree, char* comment_to_dump);
int writer_ (tre_* tree);
int do_ (char* argv_1);
void* questioner (tre_* tree);
void* reader (FILE* fp);
int share (tre_* tree);
void* add_link (tre_* tree);
int delet_tree (tre_* tree);

#endif