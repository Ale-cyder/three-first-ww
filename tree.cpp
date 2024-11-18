#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <string.h>
#include <assert.h>

int main (int argc, char** argv)
{
    if (argc == 2)
    {
        do_ (argv[1]);
    }
    else 
    {
        printf ("NO file\n");
    }
}

int do_ (char* argv_1)
{    
    FILE* fp = fopen (argv_1, "r");
    tre_* tree = 0;
    if (fp)
    {
        tree = (tre_*) reader (fp);
    }
    else
    {
        printf ("error open file\n");
        return 1;
    }
    //questioner (tree);

    //printf ("start write\n");
    //writer_ (tree);
    difference_world (tree);
    //defen_world (tree);
    dump_three (tree, "dump 1");

    delet_tree (tree);
    return 0;
}

int delet_tree (tre_* tree)
{
    if (!tree)
        return 1;

    if (tree->left)
        delet_tree ((tre_*) tree->left);

    if (tree->rght)
        delet_tree ((tre_*) tree->rght);

    printf ("%s==\n", tree->str);
    assert (tree);
    free (tree);

    return 0;
}


void* reader (FILE* fp)
{
    char c = 0;

    while (((c = getc (fp)) != '\"')) {}

    tre_* new_tree = (tre_*) calloc (sizeof (tre_), 1);

    fscanf (fp, "%[^\"]", new_tree->str); 

    c = getc (fp);

    while (((c = getc (fp)) != '{') && (c != '}')) {}

    if (c == '{')
        new_tree->rght = (tre_*) reader (fp);
    else if (c == '}')
        return new_tree;

    while (((c = getc (fp)) != '{')) {}

    if (c == '{')
        new_tree->left = (tre_*) reader (fp);

    return new_tree;
}

void* questioner (tre_* tree)
{
    
    printf ("%s\n", tree->str);

    printf ("Answer: Y or N\n");

    char simvol = 0;
    
    scanf ("%s", &simvol);

    if (simvol == 'Y')
    {
        printf ("You answered yes\n");
        if (tree->rght)
        {
            void* local = questioner ((tre_*) tree->rght);
            if (local)
            {
                tree->rght = (tre_*) local;
            }
        }
        else 
        {
            return 0;
        }
    }
    else if (simvol == 'N')
    {
        if (tree->left)
        {
            void *local = questioner ((tre_*) tree->left);
            if (local)
            {
                tree->left = (tre_*) local;
            }
        }
        else 
        {
            return add_link (tree);
        }
    }
    else 
    {
        printf ("No, no, no, bro!\n");
    }
    return 0;
}

void* add_link (tre_* left_sheet)
{
    printf ("What is it?\n");

    tre_* new_left_sheet = (tre_*) calloc (sizeof (tre_), 1);

    char disposable = getchar ();
    scanf ("%[^\n]", new_left_sheet->str);

    printf ("what is the distinguishing feature?\n");

    tre_* new_parent_branch = (tre_*) calloc (sizeof (tre_), 1);
    
    disposable = getchar ();
    scanf ("%[^\n]", new_parent_branch->str);

    printf ("Sheet add\n");
    new_parent_branch->left = new_left_sheet;
    new_parent_branch->rght = left_sheet;
    return new_parent_branch;
}

int dump_three (tre_* tree, char* comment_to_dump)
{

   if (system ("find . -maxdepth 1 -type d -name  folder_log_png > answer_system.txt"))
        static int folder_with_png = system ("mkdir folder_log_png");

    static char generate_name = 'a';
    char file_name[] = DUMP_FILE;
    file_name[POSICION_WITH_NUMBER_PNG] = generate_name++;

    FILE* fp = fopen (file_name, "w");

    fprintf (fp, "digraph structs { \nrankdir=HR;\n");
    //
    write_branch_in_dot (tree, fp);
    //
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

int write_branch_in_dot (tre_* tree, FILE* fp)
{
    fprintf (fp, "_%p [label = \"", tree);
    fputs (tree->str, fp);
    fprintf (fp,"\"];\n");
    if (tree->left)
    {
        write_branch_in_dot ((tre_*) tree->left, fp);
        fprintf (fp, "_%p->_%p [label = \"NO\"];\n", tree, tree->left);
    }
    if (tree->rght)
    {
        write_branch_in_dot ((tre_*) tree->rght, fp);
        fprintf (fp, "_%p->_%p [label = \"YES\"];\n", tree, tree->rght);
    }

    return 0;
}

int writer_ (tre_* tree)
{
    static FILE* fp = fopen (FILE_WRITE_NAME, "w");
    static int number_tab = 0;
    for (int p = 0; p < number_tab; p++)
    {
        fprintf (fp, "\t");
    } 
    number_tab++;
    fprintf (fp, "{\n");

    for (int p = 0; p < number_tab; p++)
    {
        fprintf (fp, "\t");
    }
    fprintf (fp, "\"");
    fputs (tree->str, fp);
    fprintf (fp,"\"\n");
    
    if (tree->rght)
        writer_ ((tre_*) (tree->rght));
    if (tree->left)
        writer_ ((tre_*) (tree->left));

    number_tab--;
    for (int p = 0; p < number_tab; p++)
    {
        fprintf (fp, "\t");
    }
    fprintf (fp, "}\n");

    return 0;
}

int defen_world (tre_* tree)
{
    printf ("Enter the word to find\n");

    static int recursion_depth = 0;
    static char find_world[SIZ] = {};

    if (!recursion_depth++)
    {
        char disposable = getchar ();
        scanf ("%[^\n]", find_world);
    }

    if (tree->left)
    {
        if (defen_world ((tre_*) tree->left))
        {
            int num = 0;
            printf ("not ");
            while (tree->str[num] != '\0') putchar (tree->str[num++]);

            recursion_depth--;
            if (!recursion_depth)
                printf (".\n");
            else    
                printf (", ");
            return 1;
        }
    }

    if (tree->rght)
    {
        if (defen_world ((tre_*) tree->rght))
        {
            int num = 0;
            while (tree->str[num] != '\0') putchar (tree->str[num++]);
            
            recursion_depth--;
            if (!recursion_depth)
                printf (".\n");
            else    
                printf (", ");
            return 1;
        }
        if (!recursion_depth--)
            printf ("word did not find\n");
        return 0;
    }
    if (!strcmp(tree->str, find_world))
    {
        printf ("The ");
        int num = 0;
        while (tree->str[num] != '\0') putchar (tree->str[num++]);
        printf (" is: ");
        recursion_depth--;
        return 1;
    }
    
    recursion_depth--;

    return 0;
}

int difference_world (tre_* tree)
{
    
    static int recursion_depth = 0;
    static char find_world_first[SIZ] = {};
    static char find_world_second[SIZ] = {};

    if (!recursion_depth++)
    {
        printf ("Enter the words to compare\n");
        char One_size_fits_all = scanf ("%[^\n]", find_world_first);

        if (!One_size_fits_all)
        {
            One_size_fits_all = getchar ();
            scanf ("%[^\n]", find_world_first);
        }

        One_size_fits_all = getchar ();
        scanf ("%[^\n]", find_world_second);
    //    PUTS (find_world_first);
    //    PUTS (find_world_second);
    }

    int left = 0, right = 0;

    if (tree->left)
    {
        left = difference_world ((tre_*) tree->left);
        if (left == 2)
        {
            printf ("not ");
            PUTS (tree->str)
            
            if (!--recursion_depth)
                printf (".\n");
            else    
                printf (", ");
            return 2;
        }
        else if (left)
        {
            printf ("not ");
            PUTS (tree->str)
            if (!recursion_depth)
                printf (".\n");
            else    
                printf (", ");
        }
    }

    if (tree->rght)
    {
        right = difference_world ((tre_*) tree->rght);
        
        if (right == 2)
        {
            PUTS (tree->str)
            
            if (!--recursion_depth)
                printf (".\n");
            else    
                printf (", ");
            return 2;
        }
        else if (!right)
        {
            if (!--recursion_depth)
                printf ("both words were not found\n");
            return 0;
        }
        else if (right == left) // == 1
        {
            PUTS (tree->str)
            if (!--recursion_depth)
            {

                printf (". And the words are generally different, they do not have common features\n");
                return 2;
            }
            printf (". And they are similar in that both: ");
            return 2;
        }
        else if (right)
        {
            PUTS (tree->str)
            if (!recursion_depth--)
                printf (".\n");
            else    
                printf (", ");
            return 1;
        }
    }
    if (!strcmp(tree->str, find_world_first))
    {
        printf ("The ");
       PUTS (tree->str);
        printf (" is: ");
        recursion_depth--;
        return 1;
    }
    
    if (!strcmp(tree->str, find_world_second))
    {
        printf ("The ");
       PUTS (tree->str);
        printf (" is: ");
        recursion_depth--;
        return 1;
    }

    recursion_depth--;
    return 0;
}



