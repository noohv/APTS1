#include<iostream>
#include<stdio.h>
#include<stdlib.h>

struct Node {
    int time;
    char action;
    char code[12];
    char name[51];
    bool status=true;
    Node* next;
};

struct Pair {
    int time;
    char codeA[12];
    char codeB[12];
    Pair* next;
};

// Add elements from text line to linked-list
void addElements(const char *line,Node *&first,Node *&last) {
    Node *p=new Node;
    sscanf(line,"%d %c %s %s",&p->time,&p->action,(char*)&p->code,(char*)&p->name);
    if (first==NULL)
        first=last=p;
    else {
        last->next=p;
        last = p;
        last->next=NULL;
    }
}

void findCD(FILE* out,Node* first, Pair *&start, Pair *&back) {
    Node *p=first;
    Node *x=NULL;
    Node *found=NULL;
    bool isName=false;
    while(p) {
        x=p->next;
        while(x){
            if(p->status!=false && x->status!=false){
                if(p->action=='B' && x->action=='A') {
                    for(int i=0;p->name[i]!='\0' && x->name[i]!='\0' ;i++){
                        if(p->name[i]==x->name[i]) {
                            isName=true;
                        }
                        else{
                            isName=false;
                            break;
                        }
                    }
                    if(isName) {
                        p->status=false;
                        x->status=false;
                        Pair *h=new Pair;
                        sprintf(h->codeA, "%s", x->code);
                        sprintf(h->codeB, "%s", p->code);
                        h->time=x->time;
                        if (start==NULL)
                            start=back=h;
                        else {
                            back->next=h;
                            back = h;
                            back->next=NULL;
                        }

                        found=x;
                        break;

                    }

                }
                else if(p->action=='A' && x->action=='B'){
                    for(int i=0;p->name[i]!='\0' && x->name[i]!='\0' ;i++){
                        if(p->name[i]==x->name[i]) {
                            isName=true;
                        }
                        else{
                            isName=false;
                            break;
                        }
                    }
                    if(isName) {
                        p->status=false;
                        x->status=false;
                        Pair *h=new Pair;
                        sprintf(h->codeA, "%s", p->code);
                        sprintf(h->codeB, "%s", x->code);
                        h->time=x->time;
                        if (start==NULL)
                            start=back=h;
                        else {
                            back->next=h;
                            back = h;
                            back->next=NULL;
                        }
                        found=x;
                        break;
                    }
                }
            }
            
            x=x->next;
        }
        p=p->next;
    }
    if(found==NULL) {
        fprintf(out,"%s\n", "0");
    }
}

//Function declaration
Pair* SortedMerge(Pair* a, Pair* b);
void FrontBackSplit(Pair* source, Pair** frontRef, Pair** backRef);
 
// sorts the linked list by changing pointers
void MergeSort(Pair** headRef) {
    Pair* head = *headRef;
    Pair* a;
    Pair* b;
 
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
 
    FrontBackSplit(head, &a, &b);
 
    MergeSort(&a);
    MergeSort(&b);
 
    *headRef = SortedMerge(a, b);
}
 
Pair* SortedMerge(Pair* a, Pair* b) {
    Pair* result = NULL;
 
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
 
    if (a->time <= b->time) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}
 
void FrontBackSplit(Pair* source,
                    Pair** frontRef, Pair** backRef)
{
    Pair* fast;
    Pair* slow;
    slow = source;
    fast = source->next;
 
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void fileWrite(FILE* out,Pair *start) {
    Pair *h=start;
    while(h) {
    fprintf(out,"%d %s %s\n", h->time, h->codeA, h->codeB);

        h=h->next;
    }
}

//Deletes list objects for first linked list
void rem(Node *&first) {
    while(first) {
        Node *p = first->next;
        delete first;
        first=p;
    }
}

//Deletes list objects for other linked list
void rem2(Pair *&start) {
    while(start) {
        Pair *p = start->next;
        delete start;
        start=p;
    }
}

void print(Node*&first) {
    Node* p=first;
    while(p){
       std::cout<<p->time;
        p=p->next;
    }
}

int main() {
    Node* first=NULL;
    Node* last=NULL;
    Pair* start=NULL;
    Pair* back=NULL;

    FILE* file = fopen("exchange.in", "r"); //Opens file
    FILE* out = fopen("exchange.out", "w");
    char line[100]; //Stores each line
    //Reads lines from file to char array line
    while(fgets(line, sizeof(line), file)) {
        addElements(line,first,last);
    }


    findCD(out,first,start,back);
    fclose(file);
    print(first);
    rem(first);
    MergeSort(&start);
    fileWrite(out,start);
    fclose(out);
    rem2(start);
}
