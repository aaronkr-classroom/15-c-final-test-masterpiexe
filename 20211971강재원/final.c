#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>

typedef struct Data {
    char name[14];
    int korean, english, math;
    int ranking;
    int total;
    float average;
} DATA;
//������ �����

typedef struct node {
    DATA data;
    struct node* next;
} NODE;
//���Ḯ��Ʈ �����

void AddNode(NODE** pp_head, NODE** pp_tail, DATA* p_data) {
    if (*pp_head == NULL) {
        *pp_head = (NODE*)malloc(sizeof(NODE));
        *pp_tail = *pp_head; 
    }
    else {
        (*pp_tail)->next = (NODE*)malloc(sizeof(NODE)); // tail�� �ڷ����� �����ϴ°Ŷ� 2�������� ����
        *pp_tail = (*pp_tail)->next;
    }
    (*pp_tail)->data = *p_data;
    (*pp_tail)->next = NULL;
}

void FreeNode(NODE** pp_head, NODE** pp_tail) {
    NODE* p = *pp_head, * save_next; //�ּҰ� �ӽ� ����� save_next
    while (p != NULL) {
        save_next = p->next;
        free(p);
        p = save_next;
    }
    *pp_head = *pp_tail = NULL; //�޸� �Ҵ� ���� �� head, tail ������ �ʱ�ȭ
}

void UpdateRanking(NODE* pp_head, DATA* p_data) {
    NODE* p = pp_head;
    while (p != NULL) {
        if (p_data->total < p->data.total) {
            p_data->ranking++;
        }
        else if (p_data->total > p->data.total) {
            p->data.ranking++;
        }//������ ���� ��� �Ѵ� ���α����� else�� �ƴ϶� elseif�� ��� ���θ� ���� �߰��ɶ� ���� 1���� ��� 2���� �ݺ��� ���鼭 �ڵ����� 3��ó�� ��
        p = p->next;
    }
}

void InputData(DATA* p_data, int count) {
   
    FILE* fp;
    fp = fopen("students.dat", "wb");
    if (NULL != fp)
    {
        printf("\n%d ��° �л� �̸� : ", count);
        fscanf_s(fp, "%s", p_data->name);
        printf("���� ���� : ");
        fscanf_s(fp, "%d", &p_data->korean);
        printf("���� ���� : ");
        fscanf_s(fp, "%d", &p_data->english);
        printf("���� ���� : ");
        fscanf_s(fp, "%d", &p_data->math);
        fclose(fp);
    }
    
    p_data->ranking = 1;
    p_data->total = p_data->korean + p_data->english + p_data->math;
    p_data->average = p_data->total / 3.0f;
}
void InputData2(DATA* p_data, int count)
{
    int proceed;
    printf("write on your own? type 1to proceed");
    scanf("%d", &proceed);
    if (proceed == 1)
    {
        printf("\n%d ��° �л� �̸� : ", count);
        scanf("%s", p_data->name);
        printf("���� ���� : ");
        scanf("%d", &p_data->korean);
        printf("���� ���� : ");
        scanf("%d", &p_data->english);
        printf("���� ���� : ");
        scanf("%d", &p_data->math);
        printf("\n\n");
    }
    p_data->ranking = 1;
    p_data->total = p_data->korean + p_data->english + p_data->math;
    p_data->average = p_data->total / 3.0f;
}
void CheckData(NODE* p_head) {
    NODE* p = p_head;
    printf("\n--------------------------------------------------------\n");
    printf("�̸�     ����   ����  ����  ����   ���   ���\n");
    printf("\n--------------------------------------------------------\n");
    while (p != NULL) {
        printf("%s   %3d   %3d   %3d    %3d   %3.2f   %2d��\n\n", p->data.name,p->data.korean,
            p->data.english, p->data.math, p->data.total, p->data.average, p->data.ranking);
        p = p->next;
    }
}
void SaveData(NODE* p_head)
{
    NODE* p = p_head;
    FILE* fp;
    fp = fopen("students.dat", "wb");
    if (NULL != fp)
    {
        fwrite(p, sizeof(DATA), 10, fp);
        fclose(fp);
    }
}


void main() {
    NODE* p_head = NULL, * p_tail = NULL;
    DATA temp;
    int index, count = 0;
    while (1) {
        printf("[MENU]\n");
        printf("1. ���� �б�\n");
        printf("2. ���� Ȯ��\n");
        printf("3. ����\n");
        printf("4. ���� �Է�\n");
        printf("5. ���Ͽ� ����\n");
        printf("-----------\n");
        printf("����(1 ~ 5) : ");
        scanf("%d", &index);
        if (index == 1) {
            InputData(&temp, ++count); //1�� �߰��ѻ��·� count�� �Ű������� ����
            UpdateRanking(p_head, &temp); //���Ḯ��Ʈ�� ����ְ� �����ϴ� ����� ����򿡼� ����� ���� temp�� �ӽ÷� �����س��� UpdataRanking �Լ��� �߰��Ҷ����� ����� ����� �۰ų� ũ�� ++�ϴ� ������� ���� ��Ų ���·� ���Ḯ��Ʈ�� �߰��ϴ� ����� ���
            AddNode(&p_head, &p_tail, &temp);
        }
        else if (index == 2) {
            CheckData(p_head);
        }
        else if (index == 3) {
            break;
        }
        else if (index == 4)
        {
            InputData2(&temp, ++count); //1�� �߰��ѻ��·� count�� �Ű������� ����
            UpdateRanking(p_head, &temp); //���Ḯ��Ʈ�� ����ְ� �����ϴ� ����� ����򿡼� ����� ���� temp�� �ӽ÷� �����س��� UpdataRanking �Լ��� �߰��Ҷ����� ����� ����� �۰ų� ũ�� ++�ϴ� ������� ���� ��Ų ���·� ���Ḯ��Ʈ�� �߰��ϴ� ����� ���
            AddNode(&p_head, &p_tail, &temp);
        }
        else if (index == 5)
        {
            SaveData(p_head);
        }
        else {
            printf("\n���� �����Դϴ�.\n");
        }
    }
    FreeNode(&p_head, &p_tail);
}