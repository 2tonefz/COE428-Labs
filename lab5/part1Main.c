#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

extern char * pop();
extern void push(char *);
extern int isEmpty();

int main(int argc, char * argv[])
{
    int ch;

    while ((ch = getchar()) != EOF) {
        /* ignore everything until a possible tag character */
        if (!(isalpha(ch) || ch == '>' || ch == '<' || ch == '/'))
            continue;

        /* tags only begin with '<' */
        if (ch != '<')
            continue;

        /* read character after '<' */
        ch = getchar();
        if (ch == EOF) {
            printf("Invalid\n");
            exit(0);
        }

        int isEndTag = 0;
        char tag[1000];
        int i = 0;

        /* determine start-tag or end-tag */
        if (ch == '/') {
            isEndTag = 1;

            /* first character of tag name comes after '/' */
            ch = getchar();
            if (ch == EOF || !isalpha(ch)) {
                printf("Invalid\n");
                exit(0);
            }
        }

        /* for start-tag, current ch is already first letter
           for end-tag, current ch is first letter after '/' */
        if (!isalpha(ch)) {
            printf("Invalid\n");
            exit(0);
        }

        tag[i++] = ch;

        /* read rest of tag name until '>' */
        while ((ch = getchar()) != EOF && ch != '>') {
            if (isalpha(ch)) {
                tag[i++] = ch;
            } else {
                /* simplified XML in this lab only allows alphabetic tag names */
                printf("Invalid\n");
                exit(0);
            }
        }

        if (ch != '>') {
            printf("Invalid\n");
            exit(0);
        }

        tag[i] = '\0';

        if (!isEndTag) {
            /* start-tag: push a copy onto the stack */
            char *copy = malloc(strlen(tag) + 1);
            if (copy == NULL) {
                printf("Invalid\n");
                exit(0);
            }
            strcpy(copy, tag);
            push(copy);
        } else {
            /* end-tag: stack must not be empty */
            if (isEmpty()) {
                printf("Invalid\n");
                exit(0);
            }

            char *top = pop();

            if (top == NULL) {
                printf("Invalid\n");
                exit(0);
            }

            if (strcmp(top, tag) != 0) {
                free(top);
                printf("Invalid\n");
                exit(0);
            }

            free(top);
        }
    }

    /* valid only if no unmatched start-tags remain */
    if (isEmpty())
        printf("Valid\n");
    else
        printf("Invalid\n");

    exit(0);
}
