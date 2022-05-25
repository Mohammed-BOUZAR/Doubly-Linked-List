#include <stdio.h>
#include <stdlib.h>

struct NODE{
    int data;
    struct NODE * next;
    struct NODE * prev;
};
typedef struct NODE NODE;

struct LIST{
    NODE * head;
    NODE * end;
};
typedef struct LIST DLC;

void printList(DLC * l)
{
    NODE * tmp;
    if(l->head == NULL)
        printf("The list is empty.\n");
    else{
        tmp = l->head;
        while(tmp != NULL){
            printf(" %d ",tmp->data);
            tmp = tmp->next;
        }
        printf("\n");
        tmp = l->end;
        while(tmp != NULL){
            printf(" %d ",tmp->data);
            tmp = tmp->prev;
        }
        printf("\n");
    }
}
NODE * lastNode(DLC * l)
{
    NODE * tmp;
    if(l->head == NULL)
        return NULL;
    else{
        tmp = l->head;
        while(tmp->next != NULL)
            tmp = tmp->next;
        return tmp;
    }
}

void insertFront(DLC * l)
{
    NODE * newNode, * help;

    help = l->head;
    newNode = malloc(sizeof(NODE));
    printf("Data : ");
    scanf("%d",&newNode->data);
    newNode->prev = NULL;
    newNode->next = l->head;
    if(help != NULL)
        help->prev = newNode;
    l->head = newNode;
    l->end = lastNode(l);
}

void insertMiddle(DLC * l)
{
    NODE * newNode, *tmp;
    int i, position;

    printf("Position : ");
    scanf("%d",&position);
    if(position < 1)
        insertFront(l);
    else{
        newNode = malloc(sizeof(NODE));
        printf("Data : ");
        scanf("%d",&newNode->data);
        tmp = l->head;
        for(i = 0; i < position-1; i++)
            tmp = tmp->next;
        newNode->prev = tmp;
        newNode->next = tmp->next;
        tmp->next->prev = newNode;
        tmp->next = newNode;
        l->end = lastNode(l);
    }
}

void insertEnd(DLC * l)
{
    NODE * tmp, * newNode;
    if(l->head == NULL)
        insertFront(l);
    else{
        tmp = l->head;
        while(tmp->next != NULL)
            tmp = tmp->next;

        newNode = malloc(sizeof(NODE));
        printf("Data : ");
        scanf("%d",&newNode->data);
        newNode->next = NULL;
        newNode->prev = tmp;
        tmp->next = newNode;
        l->end = newNode;
    }
}

void deleteFront(DLC * l)
{
    NODE * del;
    if(l->head == NULL)
        printf("The list is empty.\n");
    else{
        del = l->head;
        l->head = l->head->next;
        if(l->head != NULL)
            l->head->prev = NULL;
        l->end = lastNode(l);
        free(del);
    }
}

void deleteMiddle(DLC * l)
{
    NODE * del, * tmp;
    int i, position;
    if(l->head == NULL)
        printf("The list is empty.\n");
    else{
        printf("Position : ");
        scanf("%d",&position);
        if(position < 1)
            deleteFront(l);
        else{
            tmp = l->head;
            for(i = 0; i < position-1; i++)
                tmp = tmp->next;
            del = tmp->next;
            tmp->next = tmp->next->next;
            tmp->next->prev = tmp;
            l->end = lastNode(l);
            free(del);
        }
    }
}

void deleteEnd(DLC * l)
{
    NODE * del, * tmp;
    if(l->head == NULL)
        printf("The list is empty.\n");
    else{
        if(l->head == l->end)
            deleteFront(l);
        else{
            tmp = l->head;
            while(tmp->next->next != NULL)
                tmp = tmp->next;
            del = tmp->next;
            tmp->next = tmp->next->next;
            l->end = lastNode(l);
            free(del);
        }
    }
}

void deleteList(DLC * l)
{
    NODE * del;
    while(l->head != NULL){
        del = l->head;
        l->head = l->head->next;
        free(del);
    }
}

void swap(DLC * l, NODE * n1, NODE * n2)
{
    NODE *i, *j, *help;

    if(l->head == n1){
        if(n1->next == n2){
            n1->next = n2->next;
            n2->next = n1;
            n1->prev = n2;
            n2->prev = NULL;
            l->head = n2;
        }
        else{
            i = l->head;
            while(i->next != n2)
                i = i->next;
            help = n1->next;
            n1->next = n2->next;
            n1->next->prev = n1;
            n2->next = help;
            help->prev = n2;
            i->next = n1;
            l->head = n2;
            n1->prev = i;
            n2->prev = NULL;
        }

    }
    else{
        if(n1->next == n2){
            i = l->head;
            while(i->next != n1)
                i = i->next;
            n1->next = n2->next;
            n2->next = n1;
            i->next = n2;
            n2->prev = i;
            if(n1->next != NULL)
                n1->next->prev = n1;
            n1->prev = n2;
        }
        else{
            i = l->head;
            while(i->next != n1)
                i = i->next;
            j = l->head;
            while(j->next != n2)
                j = j->next;
            help = n1->next;
            n1->next = n2->next;
            n2->next = help;
            j->next = n1;
            i->next = n2;
            n1->prev = j;
            n2->prev = i;
            help->prev = n2;
            if(n1->next != NULL)
                n1->next->prev = n1;
        }

    }
}

void sortList(DLC * l)
{
    NODE *i, *j, *min;
    int k, position = 0;
    if(l->head == NULL)
        printf("The list is empty.\n");
    else{
        i = l->head;
        while(i->next != NULL){
            min = i;
            j = i->next;
            while(j != NULL){
                if(min->data > j->data)
                    min = j;
                j = j->next;
            }
            if(min != NULL)
                if(i->data > min->data)
                    swap(l, i, min);
            position++;
            i = l->head;
            for(k = 0; k < position; k++)
                i = i->next;
        }
    }
    l->end = lastNode(l);
}

int main()
{
    DLC * l;
    int menu;
    while(1){
        printf("1 - Initializer.\n");
        printf("2 - Print.\n");
        printf("3 - Insert at the front.\n");
        printf("4 - Insert at the middle.\n");
        printf("5 - Insert at the end.\n");
        printf("6 - Delete at the front.\n");
        printf("7 - Delete at the middle.\n");
        printf("8 - Delete at the end.\n");
        printf("9 - Delete the list.\n");
        printf("10- Sort the list.\n");
        printf("11- Exit.\n");
        printf("Enter your choice : ");
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            l = malloc(sizeof(DLC));
            l->head = NULL;
            l->end = NULL;
            break;
        case 2:
            printList(l);
            break;
        case 3:
            insertFront(l);
            break;
        case 4:
            insertMiddle(l);
            break;
        case 5:
            insertEnd(l);
            break;
        case 6:
            deleteFront(l);
            break;
        case 7:
            deleteMiddle(l);
            break;
        case 8:
            deleteEnd(l);
            break;
        case 9:
            deleteList(l);
            break;
        case 10:
            sortList(l);
            break;
        case 11:
            free(l);
            exit(0);
            break;
        }
    }
    return 0;
}
