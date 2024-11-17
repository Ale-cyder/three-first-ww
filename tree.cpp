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
    questioner (tree);

    printf ("start write\n");
    writer_ (tree);

    defen_world (tree);
     

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

int dump_three (tre_* tree)
{
//     static char file_ID = 'a';
//     char* file_name[] = DUMP_FILE;
//     file_name[0] = file_ID++;
//    static FILE* fil = fopen (file_name, "w");


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
    static int is_world = 0;
    static char find_world[SIZ] = {};

    if (!is_world++)
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

            is_world--;
            if (!is_world)
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
            
            is_world--;
            if (!is_world)
                printf (".\n");
            else    
                printf (", ");
            return 1;
        }
    }
    if (!strcmp(tree->str, find_world))
    {
        printf ("The ");
        int num = 0;
        while (tree->str[num] != '\0') putchar (tree->str[num++]);
        printf (" is: ");
        is_world--;
        return 1;
    }
    
    is_world--;
    return 0;
}

