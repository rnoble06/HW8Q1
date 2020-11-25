#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

#define to_person(ptr) \
    container_of(ptr, struct person, node)

struct person {
    char name[128];
    int age;
    int salary;
    int years;
    struct list node;
};


/* #This function must do the following:
 * #1. Open the provided filename
 * #2. Return The NULL Pointer if filename could not be opened
 * #3. Allocate a new list head on the heap
 * #4. Populate the list with data from the file
 * #5. Return the head of the populated list  */
struct list *load_database(const char *filename)
{
    FILE *fp; 
    
    struct list *head;
    struct person *item;
    
    /* Rewrite this function! */

    head = malloc(sizeof(*head));
    int ret;
    fp = fopen(filename,"r");
    list_init(head);            /* allocate list head */

    if(fp == NULL)
    {
      return NULL;
    }

    while (1) 
    {
      item = malloc(sizeof(*item));
      ret = fscanf(fp,"%[^,], %d, %d, %d\n", item->name, &item->age, &item->salary, &item->years);

      if (ret == EOF)
      {
        free (item);
        break;
      }
      else
      {
        list_add_before(head, &item->node);
      }

    }
    return head; /* return new list head */
}


/* #This function must do the following:
 * #1. Remove all items from the provided list
 * #2. Free each removed item from the heap */
void unload_database(struct list *head)
{
    struct list *cur, *sav;
    struct person *item;
    
    /* Your code goes here! */

    list_safe_for(head, cur, sav)
    {
      item = to_person(cur);
      list_remove(&item->node);
      free(item);
    }
}


/* This function must do the following:
 * #1. Search the provided list for the item having the provided name
 * #2. Return the item if found
 * #3. Return The NULL Pointer if not found */
struct person *find_person(struct list *head, const char *name)
{
    struct list *cur; 
    struct person *item;


        /* Rewrite this function! */
    list_for(head, cur)
    {
      item = to_person(cur);
      
      if(!strcmp(item->name,name))
      {
        return item;
        break;
      }
    } 
  return NULL;
}


/* This function prints the provided struct person to the screen */
void print_person(struct person *p)
{
    printf("Employee %s:\n", p->name);
    printf("   Age: %d\n", p->age);
    printf("Salary: %d\n", p->salary);
    printf(" Years: %d\n", p->years);
}


int main(int argc, char **argv)
{
    struct list *head;
    struct person *item;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s employee_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    head = load_database("database.txt");
    
    if (!head) {
        fprintf(stderr, "Failed to open database.\n");
        return EXIT_FAILURE;
    }

    item = find_person(head, argv[1]);
    if (item)
        print_person(item);
    else
        printf("Employee NOT FOUND!\n");
    
    unload_database(head);
    free(head);

    return 0;
}