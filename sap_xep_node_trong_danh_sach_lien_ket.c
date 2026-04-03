#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
struct rich{
    char cccd[100];
    char ten[100];
    char ma[100];
    long long so_co_phieu;
};
typedef struct rich rich;
struct node{
    rich *data;
    struct node *next;
    struct node *prev;
};
typedef struct node node;
node *makenode(rich *x){
    node *newnode=(node*)malloc(sizeof(node));
    newnode ->data=x;
    newnode ->next=NULL;
    newnode ->prev=NULL;
    return newnode;
}
void nhap(rich *x){
    printf("nhap cccd cua rich:");
    scanf("%s", x->cccd);
    getchar();
    printf("nhap ten cua rich:");
    gets(x->ten);
    printf("nhap ma co phieu cua rich:");
    scanf("%s", x->ma);
    printf("nhap so co phieu cua rich:");
    scanf("%lld", &x->so_co_phieu);
    printf("-----------------------------\n");
}
void xuat(node *head){
    int i=1;
    while(head!=NULL){
        printf("thong tin cua rich [%d]:\n", i++);
        printf("so cccd:%s\nten:%s\nma co phieu:%s\nso co phieu:%lld\n",head->data->cccd, head->data->ten, head->data->ma, head->data->so_co_phieu);
        printf("-----------------------\n");
        head=head->next;
    }
}
void them_cuoi(node **head, rich *x){
    node *newnode=makenode(x);
    if(*head==NULL){
        *head=newnode;
        return;
    }
    node *temp=*head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=newnode;
    newnode->prev=temp;
}
void them_dau(node **head, rich *x){
   node *newnode=makenode(x);
   newnode->next=*head;
   if(*head!=NULL){
    (*head)->prev=newnode;
   }
   (*head)=newnode;
}
int size(node *head){
    int cnt=0;
    while(head!=NULL){
        ++cnt;
        head=head->next;
    }
    return cnt;
}
void them_giua(node **head, rich *x, int k){
    node *newnode=makenode(x);
    int m=size(*head);
    if(k<1 || k>m+1){
        return;
    }
    if(k==1){
        them_dau(head, x);
        return;
    }
    node *temp=*head;
    for(int i=1;i<=k-1;i++){
        temp=temp->next;
    }
    node *truoc=temp->prev;
    truoc->next=newnode;
    newnode->next=temp;
    newnode->prev=truoc;
    temp->prev=newnode;
}
void xoa_dau(node **head){
    if(*head==NULL){
        return;
    }
    node *temp=*head;
    *head=(*head)->next;
    if(temp->next!=NULL){
        (*head)->prev=NULL;
    }
    free(temp->data);
    free(temp);
}
void xoa_cuoi(node **head){
    if(*head==NULL){
        return;
    }
    if((*head)->next==NULL){
        xoa_dau(head);
        return;
    }
    node *temp=*head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    node *truoc=temp->prev;
    truoc->next=NULL;
    free(temp->data);
    free(temp);

}
void xoa_giua(node **head,int k){
    int m=size(*head);
    if(k<1 || k>m){
    return;
    }
    if(k==1){
        xoa_dau(head);
        return;
    }
    node *temp=*head;
    for(int i=1;i<=k-1;i++){
        temp=temp->next;
    }
    node *truoc=temp->prev;
    node *sau=temp->next;
    truoc->next=sau;
    sau->prev=truoc;
    free(temp->data);
    free(temp);
}
void find(node *head, char *c){
   int find=0;
   while(head!=NULL){
    if(strcmp(head->data->ma, c)==0){
       printf("so cccd:%s\nten:%s\nma co phieu:%s\nso co phieu:%lld\n",head->data->cccd, head->data->ten, head->data->ma, head->data->so_co_phieu);
        find=1;
        break;
    }
    head=head->next;
   }
   if(find==0){
    printf("khong tim thay!!");
   }
}
void sap_xep(node **head){
    node *i=*head;
    if(*head==NULL){
        return;
    }
      for(; i!=NULL;i=i->next){
        node *maxnode=i;
        for(node *j=i->next;j!=NULL;j=j->next){
            if(j->data->so_co_phieu<maxnode->data->so_co_phieu){
                maxnode=j;
            }
        }
        rich *temp=maxnode->data;
        maxnode ->data=i->data;
        i->data=temp;
      }
      node *p=*head;
      while(p->next!=NULL){
          p=p->next;
      }
      printf("-----------------------\n");
      printf("thong tin cua rich co so co phieu nhieu nhat la:\n");
       printf("so cccd:%s\nten:%s\nma co phieu:%s\nso co phieu:%lld\n",p->data->cccd, p->data->ten, p->data->ma, p->data->so_co_phieu);
}
void xoa(node **head, char *b){
       if(*head==NULL){
        return;
       }
       node *temp=*head;
       while(temp!=NULL){
        if(strcmp(temp->data->cccd, b)==0){
            if(temp==*head){
                *head=temp->next;
                if(temp->next!=NULL){
                    temp->prev=NULL;
                }
                free(temp->data);
                free(temp);
                return;
            }
            else if(temp->next==NULL){
                node *truoc=temp->prev;
                truoc->next=NULL;
                free(temp->data);
                free(temp);
                return;
            }
            else{
                node *truoc=temp->prev;
                node *sau=temp->next;
                truoc->next=sau;
                sau->prev=truoc;
                free(temp->data);
                free(temp);
                return;
            }
            temp=temp->next;
        }
       }
       printf("khong tim thay de xoa");
}
int main(){
    node *head=NULL;
    int n;
    printf("nhap so luong nguoi giau:");
    scanf("%d", &n);
    printf("\n-------------------------\n");
    for(int i=1;i<=n;i++){
        rich *x=(rich*)malloc(sizeof(rich));
        nhap(x);
        them_cuoi(&head, x);
    }
    printf("\n------------danh sach sau khi nhap-----------\n");
    xuat(head);
    printf("\n---------------------------------------------\n");
    int k=0;
    while(k!=10){
        printf("1.them node dau\n");
        printf("2.them node cuoi\n");
        printf("3.them node o vi tri thu k\n");
        printf("4.xoa node dau\n");
        printf("5.xoa node cuoi\n");
        printf("6.xoa node o vi tri k\n");
        printf("7.tim nguoi co so co phieu cao nhat\n");
        printf("8.xoa nguoi co ma co phieu\n");
        printf("9.tim nguoi theo so cccd\n");
        printf("10.thoat\n");
        printf("=>nhap su lua chon cua ban:");
        scanf("%d", &k);
        switch(k){
            case 1:{
                rich *x=(rich*)malloc(sizeof(rich));
                nhap(x);
                them_dau(&head, x);
                printf("\n------------danh sach sau khi thay doi-----------\n");
                xuat(head);
                printf("-----------------------------------\n");
            }
            break;
            case 2:{
                rich *x=(rich*)malloc(sizeof(rich));
                nhap(x);
                them_cuoi(&head, x);
                printf("\n------------danh sach sau khi thay doi-----------\n");
                xuat(head);
                printf("-----------------------------------\n");
            }
            break;
            case 3:{
                int t;
                printf("nhap vi tri ma ban muon chen:");
                scanf("%d", &t);
                rich *x=(rich*)malloc(sizeof(rich));
                nhap(x);
                them_giua(&head, x,t);
                printf("\n------------danh sach sau khi thay doi-----------\n");
                xuat(head);
                printf("-----------------------------------\n");
            }
            break;
            case 4:{
                xoa_dau(&head);
                printf("\n------------danh sach sau khi thay doi-----------\n");
                if(head==NULL){
                    printf("=>danh sach trong\n");
                }
                xuat(head);
                printf("-----------------------------------\n");
            }
            break;
            case 5:{
                xoa_cuoi(&head);
                printf("\n------------danh sach sau khi thay doi-----------\n");
                if(head==NULL){
                    printf("=>danh sach trong\n");
                }
                xuat(head);
                printf("-----------------------------------\n");
            }
            break;
            case 6:{
                int j;
                printf("nhap vi tri node ma ban muon xoa:");
                scanf("%d", &j);
                xoa_giua(&head, j);
                printf("\n------------danh sach sau khi thay doi-----------\n");
                if(head==NULL){
                    printf("=>danh sach trong\n");
                }
                xuat(head);
                printf("-----------------------------------\n");
            }
            case 7:{
                sap_xep(&head);
                printf("-----------------------------------\n");
            }
            break;
            case 8:{
                char c[100];
                printf("nhap ma co phieu can xoa:");
                scanf("%s", c);
                xoa(&head, c);
                printf("\n------------danh sach sau khi thay doi-----------\n");
                if(head==NULL){
                    printf("=>danh sach trong\n");
                }
                xuat(head);
                printf("-----------------------------------\n");
            }
            break;
            case 9:{
                char b[100];
                printf("nhap so ma co phieu ma ban can tim:");
                scanf("%s", b);
                printf("thong tin ma nguoi ban can tim la:\n");
                find(head, b);
                printf("-----------------------------------\n");
            }
            break;
            case 10:{
               printf("tam biet!!");
               break;
            }
            default:
            printf("khong hop le!!");
    }
}
    return 0;
}
