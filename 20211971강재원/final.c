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
//데이터 저장용

typedef struct node {
    DATA data;
    struct node* next;
} NODE;
//연결리스트 저장용

void AddNode(NODE** pp_head, NODE** pp_tail, DATA* p_data) {
    if (*pp_head == NULL) {
        *pp_head = (NODE*)malloc(sizeof(NODE));
        *pp_tail = *pp_head; 
    }
    else {
        (*pp_tail)->next = (NODE*)malloc(sizeof(NODE)); // tail은 자료형에 접근하는거라 2차원으로 접근
        *pp_tail = (*pp_tail)->next;
    }
    (*pp_tail)->data = *p_data;
    (*pp_tail)->next = NULL;
}

void FreeNode(NODE** pp_head, NODE** pp_tail) {
    NODE* p = *pp_head, * save_next; //주소값 임시 저장용 save_next
    while (p != NULL) {
        save_next = p->next;
        free(p);
        p = save_next;
    }
    *pp_head = *pp_tail = NULL; //메모리 할당 해제 후 head, tail 포인터 초기화
}

void UpdateRanking(NODE* pp_head, DATA* p_data) {
    NODE* p = pp_head;
    while (p != NULL) {
        if (p_data->total < p->data.total) {
            p_data->ranking++;
        }
        else if (p_data->total > p->data.total) {
            p->data.ranking++;
        }//점수가 같을 경우 둘다 냅두기위해 else가 아니라 elseif를 사용 냅두면 다음 추가될때 공동 1등일 경우 2등이 반복문 돌면서 자동으로 3등처리 됌
        p = p->next;
    }
}

void InputData(DATA* p_data, int count) {
   
    FILE* fp;
    fp = fopen("students.dat", "wb");
    if (NULL != fp)
    {
        printf("\n%d 번째 학생 이름 : ", count);
        fscanf_s(fp, "%s", p_data->name);
        printf("국어 점수 : ");
        fscanf_s(fp, "%d", &p_data->korean);
        printf("영어 점수 : ");
        fscanf_s(fp, "%d", &p_data->english);
        printf("수학 점수 : ");
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
        printf("\n%d 번째 학생 이름 : ", count);
        scanf("%s", p_data->name);
        printf("국어 점수 : ");
        scanf("%d", &p_data->korean);
        printf("영어 점수 : ");
        scanf("%d", &p_data->english);
        printf("수학 점수 : ");
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
    printf("이름     국어   영어  수학  총점   평균   등수\n");
    printf("\n--------------------------------------------------------\n");
    while (p != NULL) {
        printf("%s   %3d   %3d   %3d    %3d   %3.2f   %2d등\n\n", p->data.name,p->data.korean,
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
        printf("1. 성적 읽기\n");
        printf("2. 성적 확인\n");
        printf("3. 종료\n");
        printf("4. 성적 입력\n");
        printf("5. 파일에 저장\n");
        printf("-----------\n");
        printf("선택(1 ~ 5) : ");
        scanf("%d", &index);
        if (index == 1) {
            InputData(&temp, ++count); //1을 추가한상태로 count를 매개변수에 대입
            UpdateRanking(p_head, &temp); //연결리스트에 집어넣고 정렬하는 방식의 어려움에서 벗어나기 위해 temp에 임시로 저장해놓고 UpdataRanking 함수를 추가할때마다 사용해 등수를 작거나 크면 ++하는 방식으로 정렬 시킨 상태로 연결리스트에 추가하는 방식을 사용
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
            InputData2(&temp, ++count); //1을 추가한상태로 count를 매개변수에 대입
            UpdateRanking(p_head, &temp); //연결리스트에 집어넣고 정렬하는 방식의 어려움에서 벗어나기 위해 temp에 임시로 저장해놓고 UpdataRanking 함수를 추가할때마다 사용해 등수를 작거나 크면 ++하는 방식으로 정렬 시킨 상태로 연결리스트에 추가하는 방식을 사용
            AddNode(&p_head, &p_tail, &temp);
        }
        else if (index == 5)
        {
            SaveData(p_head);
        }
        else {
            printf("\n없는 숫자입니다.\n");
        }
    }
    FreeNode(&p_head, &p_tail);
}