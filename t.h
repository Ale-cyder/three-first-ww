#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


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
struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    char str[SIZ];
};

int test_prog ();
int compareWordsInTree(TreeNode* root);
int write_branch_in_dot (TreeNode* tree, FILE* fp);
int dump_three (TreeNode* tree, char* comment_to_dump);
int writer_ (TreeNode* tree);
TreeNode* questioner (TreeNode* tree);
TreeNode* reader (FILE* fp);
TreeNode* add_link (TreeNode* tree);
int delet_tree (TreeNode* tree);
int searchstrInTree (TreeNode* root);

#endif