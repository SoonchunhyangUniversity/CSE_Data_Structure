/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 이진 트리 연습
 * 작성일 : 2018-09-18
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

typedef struct
{
    char word[MAX_WORD_SIZE];
    char meaning[MAX_MEANING_SIZE];
} element;

typedef struct TreeNode
{
    element key;
    struct TreeNode *left, *right;
} TreeNode;

int compare(element e1, element e2)
{
    return strcmp(e1.word, e2.word);
}

void display(TreeNode *p)
{
    if(p != NULL)
    {
        printf("(");
        display(p->left);
        printf("%s", p->key.word);
        display(p->right);
        printf(")");
    }
}

TreeNode *search(TreeNode *root, element key)
{
    TreeNode *p = root;

    while(p!=NULL)
    {
        switch(compare(key, p->key))
        {
        case -1 :
            p = p->left;
            break;

        case 0 :
            return p;

        case 1 :
            p = p->right;
            break;
        }
    }

    return p;
}

void insert_node(TreeNode **root, element key)
{
    TreeNode *p, *t;
    TreeNode *n;

    t = *root;
    p = NULL;

    while(t != NULL)
    {
        if(compare(key, t->key) == 0)
            return;

        p = t;

        if(compare(key, t->key) < 0)
            t = t->left;

        else
            t = t->right;
    }

    n = (TreeNode *)malloc(sizeof(TreeNode));

    if(n == NULL)
        return;

    n->key = key;
    n->left = n->right = NULL;

    if(p != NULL)
    {
        if(compare(key, p->key) < 0)
            p->left = n;

        else
            p->right = n;
    }

    else
        *root = n;
}

void delete_node(TreeNode **root, element key)
{
    TreeNode *p, *child, *succ, *succ_p, *t;

    p = NULL;
    t = *root;

    while(t!= NULL & compare(t->key, key) != 0)
    {
        p = t;
        t = (compare(key, t->key) < 0) ? t->left : t->right;
    }

    if(t == NULL)
    {
        printf("Key is not in the tree");
        return;
    }

    if((t->left == NULL) && (t->right == NULL))
    {
        if(p != NULL)
        {
            if(p->left == t)
                p->left = NULL;

            else
                p->right = NULL;
        }

        else
            *root = NULL;
    }

    else if((t->left == NULL) || (t->right == NULL))
    {
        child = (t->left != NULL) ? t->left : t->right;

        if(p != NULL)
        {
            if(p->left == t)
                p->left = child;

            else
                p->right = child;
        }

        else
            *root = child;
    }

    else
    {
        succ_p = t;
        succ = t->right;

        while(succ->left != NULL)
        {
            succ_p = succ;
            succ = succ->left;
        }

        if(succ_p->left == succ)
            succ_p->left = succ->right;

        else
            succ_p->right = succ->right;

        t->key = succ->ket;
        t = succ;
    }

    free(t);
}

void help()
{
    printf("");
    printf("i : 입력\n");
    printf("d : 삭제\n");
    printf("s : 탐색\n");
    printf("p : 출력\n");
    printf("q : 종료\n");
    printf("");
}

int main()
{
    
}
