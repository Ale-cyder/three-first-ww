
#include "t.h"

int main () 
{
    return test_prog ();
}


int test_prog () 
{
    printf ("What do you want?\n to do with tree.\n"\
            "If you want to get definition of the word enter: d\n"\
            "If you want to play akinator enter: p\n"\
            "If you want to compare word in tree enter: c\n"\
            "If you want end the program enter: e\n");

    scanf ("\n");
    char char_what_do = 0;
    char_what_do = getchar ();

    if (char_what_do == 'e') {
        return 0;
    }

    printf ("Enter name file with expression\n");
    const int lenth_file_name = 50;
    char file_name[lenth_file_name] = {};

    while (getchar () != '\n') {};
    scanf ("%s", file_name);

    FILE* fp = fopen (file_name, "r");
    if (fp == 0) {
       printf ("err open file\n");
       return test_prog ();
    }

    TreeNode* tree = 0;
    if ((tree = reader (fp)) == 0) {
        printf ("error read expression\n");
        return test_prog ();
    }
    printf ("success read expression\n");
    dump_three (tree, "dump tree\n");

    if (char_what_do == 'd') 
        searchstrInTree (tree);
    else if (char_what_do == 'c') 
        compareWordsInTree (tree);
    else if (char_what_do == 'p') 
        questioner (tree);
    else 
        printf ("error enter\n");

    writer_ (tree);
    printf ("the tree was written to the file: file_write.txt\n");

    return delet_tree (tree) || test_prog ();
}

int delet_tree (TreeNode* tree)
{
    if (!tree)
        return 1;

    if (tree->left)
        delet_tree ((TreeNode*) tree->left);

    if (tree->right)
        delet_tree ((TreeNode*) tree->right);

    assert (tree);
    free (tree);

    return 0;
}


TreeNode* reader (FILE* fp)
{
    char get_char= 0;

    while (((get_char= getc (fp)) != '\"')) {}

    TreeNode* new_tree = (TreeNode*) calloc (sizeof (TreeNode), 1);

    fscanf (fp, "%[^\"]", new_tree->str); 
    get_char= getc (fp);

    while (((get_char= getc (fp)) != '{') && (get_char!= '}')) {}

    if (get_char== '{')
        new_tree->right = reader (fp);
    else if (get_char== '}')
        return new_tree;

    while (((get_char= getc (fp)) != '{')) {}

    if (get_char== '{')
        new_tree->left = reader (fp);

    return new_tree;
}
TreeNode* questioner (TreeNode* tree)
{
    printf ("It is %s?\n", tree->str);
    printf ("Answer: Y or N\n");

    char simvol = 0;
    
    while ((simvol = getc (stdin)) == '\n') {};


    if (simvol == 'Y') {
        printf ("You answered yes\n");
        if (tree->right) {
            TreeNode* local = questioner ((TreeNode*) tree->right);
            if (local)
                tree->right = (TreeNode*) local;
        }
        else {
            return 0;
        }
    }
    else if (simvol == 'N') {
        if (tree->left) {
            void *local = questioner (tree->left);
            if (local)
                tree->left = (TreeNode*) local;
        }
        else {
            return add_link (tree);
        }
    }
    else {
        printf ("No, no, no, bro!\n");
    }
    return 0;
}



TreeNode* add_link (TreeNode* left_sheet)
{
    printf ("What is it?\n");

    TreeNode* new_left_sheet = (TreeNode*) calloc (sizeof (TreeNode), 1);

    getchar ();
    scanf ("%[^\n]", new_left_sheet->str);

    printf ("what is the distinguishing feature?\n");

    TreeNode* new_parent_branch = (TreeNode*) calloc (sizeof (TreeNode), 1);
    
    getchar ();
    scanf ("%[^\n]", new_parent_branch->str);

    printf ("Sheet add\n");
    new_parent_branch->left = new_left_sheet;
    new_parent_branch->right = left_sheet;
    return new_parent_branch;
}




int dump_three (TreeNode* tree, char* comment_to_dump)
{
    static char generate_name = 'a';
    char file_name[] = DUMP_FILE;
    file_name[POSICION_WITH_NUMBER_PNG] = generate_name++;

    FILE* fp = fopen (file_name, "w");

    fprintf (fp, "digraph structs { \nrankdir=HR;\n");
    
    write_branch_in_dot (tree, fp);

    fprintf (fp, "}");
    fclose (fp);
    
    file_name[POSITION_WITH_FORMAT_FILE] = '\0';
    char comand_to_cmd_generate_png[SIZE_CMD] = {};
    sprintf (comand_to_cmd_generate_png, "dot -Tpng %s.dot -o %s.png", file_name, file_name);
    system (comand_to_cmd_generate_png);

    static FILE* file_html = fopen (DUMP_HTML, "w");

    fprintf (file_html, "<h1>%s<h1>\n <img src=\"%s.png\">\n", comment_to_dump, file_name);

    return 0;
}



int write_branch_in_dot (TreeNode* tree, FILE* fp)
{
    fprintf (fp, "_%p [label = \"", tree);
    fputs (tree->str, fp);
    fprintf (fp,"\"];\n");
    if (tree->left) {
        write_branch_in_dot ((TreeNode*) tree->left, fp);
        fprintf (fp, "_%p->_%p [label = \"NO\"];\n", tree, tree->left);
    }
    if (tree->right) {
        write_branch_in_dot ((TreeNode*) tree->right, fp);
        fprintf (fp, "_%p->_%p [label = \"YES\"];\n", tree, tree->right);
    }

    return 0;
}


int writer_ (TreeNode* tree)
{
    static FILE* fp = fopen (FILE_WRITE_NAME, "w");
    static int number_tab = 0;

    for (int p = 0; p < number_tab; p++)
        fprintf (fp, "\t");

    number_tab++;
    fprintf (fp, "{\n");

    for (int p = 0; p < number_tab; p++)
        fprintf (fp, "\t");

    fprintf (fp, "\"");
    fputs (tree->str, fp);
    fprintf (fp,"\"\n");
    
    if (tree->right)
        writer_ ((TreeNode*) (tree->right));
    if (tree->left)
        writer_ ((TreeNode*) (tree->left));

    number_tab--;
    for (int p = 0; p < number_tab; p++)
        fprintf (fp, "\t");
    
    fprintf (fp, "}\n");

    return 0;
}






char* getstrToFind() 
{
    static char str[SIZ];
    printf("Enter the str to find: ");
    
    fscanf (stdin, "%s", str);
    return str;
}

// Функция для вывода слова
int printstr (const char* str, int* depth) 
{
    printf("%s\n", str);

    if (! --(*depth))
        printf ("The end of defenition\n");

    return 1;
}

// Рекурсивная функция поиска слова в дереве
int findstrInTree(const TreeNode* node, const char* targetstr, int* depth) 
{
    if (node == NULL) {
        return 0;
    }
    (*depth)++;

    if (strcmp (node->str, targetstr) == 0) {
        printf ("The %s is found.\nIt is:\n", targetstr);
        (*depth)--;
        return 1;
    }

    if (findstrInTree(node->left, targetstr, depth)) {
        printf ("Not ");
        return printstr (node->str, depth); //если найдено в левом поддереве
    }

    if (findstrInTree(node->right, targetstr, depth)) {
        return printstr (node->str, depth);; // если найдено в правом поддереве
    }

    if (!--(*depth))
        printf ("It is not found\n");
    return 0; // слово не найдено
}

// Основная функция поиска
int searchstrInTree (TreeNode* root) 
{
    int depth = 0;
    char* targetstr = getstrToFind();
    int found = findstrInTree(root, targetstr, &depth);

    if (!found)
        printf("str not found.\n");
  
    return found;
}


// Функция для получения слов для сравнения
void getWordsToCompare(char* word1, char* word2) 
{
    getchar ();
    printf("Enter the first word to compare: ");
    fgets(word1, SIZ, stdin);
    word1[strcspn(word1, "\n")] = 0;

    printf("Enter the second word to compare: ");
    fgets(word2, SIZ, stdin);
    word2[strcspn(word2, "\n")] = 0;
    return;
}


// Рекурсивная функция для поиска различий
int findDifference(const TreeNode* node, const char* word1, const char* word2, int* depth) 
{
    if (!node)
        return 0;
    
    (*depth)++;

    if (node->left && node->right) {
        int leftResult = 0, rightResult = 0;

        leftResult = findDifference(node->left, word1, word2, depth);
        if (leftResult) {
            printf ("not ");
            printf ("%s", node->str);
            printf ((*depth > 1 ) ? ", " : ".\n");
        }
        
        rightResult = findDifference(node->right, word1, word2, depth);
        if (rightResult) {
            printf  ("%s", node->str);

            if (*depth <= 1) {
                if (rightResult == leftResult) printf(".\nAnd the words are generally different.\n");
                else                           printf(".\n");
            } 
            else {
                if (rightResult == leftResult) printf(".\nAnd they are similar in that both: ");
                else                           printf(", ");
            }
        }
        
        (*depth)--;
        return  (leftResult && rightResult ? 2 : 0) | leftResult | rightResult;
    }

    (*depth)--;

    if (strcmp(node->str, word1) == 0)
        printf ("The %s is ", word1);
    else if (strcmp(node->str, word2) == 0) 
        printf ("The %s is ", word2);
    else 
        return 0;

    return 1;
}



// Основная функция сравнения слов
int compareWordsInTree(TreeNode* root) 
{
    char word1[SIZ], word2[SIZ];
    getWordsToCompare(word1, word2);

    int depth = 0;
    int result = findDifference(root, word1, word2, &depth);

    if (!result)
        printf("Both words were not found.\n");

    return result;
}

