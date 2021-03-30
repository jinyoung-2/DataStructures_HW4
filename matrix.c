#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [jinyounglee]  [2020039063] -----]\n");

    int row, col;
    srand((unsigned)time(NULL));     //시드값 설정                      

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    //2차원배열 동적할당하여 행렬 생성 
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    /* check post conditions */
    if (matrix_a == NULL || matrix_b == NULL) { return -1; }  //동적할당이 되지 않았다면, 비정상적 종료하기 

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);   //command 선택하기           

        /* switch case를 이용해 각각의 명령에 대한 함수호출*/
        switch (command) {
        case 'z': case 'Z':                         /* Z or z입력시, fill_data함수 호출*/
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':                         /* P or p입력시, print_matrix 함수 호출*/
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);      /* A or a입력시, addition_matrix 함수 호출*/
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);   /* S or s입력시, subtraction_matrix 함수 호출*/
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);    /* T or t입력시, transpose_matrix 함수 호출*/
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);    /* M or m입력시, transpose_matrix 함수 호출 후, multiply_matrix 함수 호출*/
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);                  /* Q or q입력시, free_matrix 함수 호출*/
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:                                                /* 그 이외 입력시, "Concentration!"출력 */
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');                 //반복 종료 조건

    return 1;   //정상적인 종료 
}


/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /*check pre conditions*/
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return NULL;                // 동적할당 실패를 NULL로 표현                   
    }

    /* 2차원 배열 동적할당 */
    int** matrix = (int**)malloc(sizeof(int*) * row);       //2차원 배열의 행부분 동적할당    
    /* check post conditions */
    if (matrix == NULL)
        return NULL;                // 동적할당 실패를 NULL로 표현    
    for (int i = 0; i < row; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * col);        //2차원 배열의 열부분 동적할당
        /* check post conditions */
        if (matrix[i] == NULL)
            return NULL;            // 동적할당 실패를 NULL로 표현
    }
    return matrix;      //생성된 행렬(2차원 배열) 반환
}


/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return;
    }
    else if (matrix == NULL)
        return;

    else {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++)
                printf("%4d", matrix[i][j]); //matrix[i][j]를 이중for문을 통해 출력         //printf("%d ",*(matrix[i])+j); 맞나?
            printf("\n");
        }
        printf("\n");
    }
}

/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    if (matrix == NULL) {           //동적할당 실패시, 비정상적 종료하기
        return -1;
    }

    //동적할당 해제
    for (int i = 0; i < row; i++) {
        free(matrix[i]);            //2차원배열의 열부분 동적할당 해제 
        /* check post conditions */
        matrix[i] = NULL;
        if (matrix[i] != NULL) {     /*부연설명: 에러가 발생되면 자료형이 손상되어, 값을 대입하려고 하는 시도가 있으면 알아서 차단된다.*/
            printf("Error\n");
            free_matrix(matrix, col, row);
            return -1;              //비정상적 종료
        }
    }
    free(matrix);                   //2차원배열의 행부분 동적할당 해제 
     /* check post conditions */
    matrix = NULL;
    if (matrix != NULL) {            /*부연설명: 에러가 발생되면 자료형이 손상되어, 값을 대입하려고 하는 시도가 있으면 알아서 차단된다.*/
        printf("Error\n");
        free_matrix(matrix, col, row);
        return -1;                  //비정상적 종료
    }
    return 1;   //정상적 종료
}

/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)                                    //Q. matrix 이름만으로 다르게 풀 수는 없을까?
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    if (matrix == NULL)
        return -1;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix[i][j] = rand() % 20;                  //rand()함수 이용하여 초기화
            /* check post conditions */
            if (matrix[i][j] < 0 || matrix[i][j]>19) {   //값이 0~19로 한정되어 있어, 0보다 작거나 19보다 클 수 없다. 
                fill_data(matrix, row, col);            //후처리검사에서 오류발생시, 함수 재호출
                return -1; //비정상종료                     
            }
        }
    }
    return 1;   //정상적 종료 
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    if ((matrix_a == NULL) || (matrix_b == NULL))
        return -1;

    int** matrix_c = create_matrix(row, col);       //새로운 행렬(2차원배열) 선언
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            /* check post conditions */
            if ((matrix_a[i][j] + matrix_b[i][j] < 0) || (matrix_a[i][j] + matrix_b[i][j] > 38)) {      //값이 0~19로 한정되어 있어, 더한 값이 0보다 작을 수 없고 38보다 클 수 없다.
                printf("The added value must not be less than 0.\n");
                addition_matrix(matrix_a, matrix_b, row, col);      //후처리검사에서 오류발생시, 함수 재호출
                return -1;  //비정상종료
            }
            matrix_c[i][j] = matrix_a[i][j] + matrix_b[i][j];       //정상작동시, matrix_c에 더한 값 대입 
        }
    }
    print_matrix(matrix_c, row, col);     //matrix_c 출력
    return 1;   //정상종료
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    if ((matrix_a == NULL) || (matrix_b == NULL)) {
        return -1;
    }
    int** matrix_c = create_matrix(row, col);        //새로운 행렬(2차원배열) 선언
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            /* check post conditions */
            if ((matrix_a[i][j] - matrix_b[i][j] > 19) || (matrix_a[i][j] - matrix_b[i][j] < -19)) {       //값이 0~19로 한정되어 있어, 뺀 값이 -19보다 작을 수 없고 19보다 클 수 없다.
                printf("The subtracted value must not be greater than 19.\n");
                subtraction_matrix(matrix_a, matrix_b, row, col);   //후처리검사에서 오류발생시, 함수 재호출
                return -1;  //비정상종료
            }
            matrix_c[i][j] = matrix_a[i][j] - matrix_b[i][j];       //정상작동시, matrix_c에 뺀 값 대입 
        }
    }
    print_matrix(matrix_c, row, col);       //matrix_c 출력
    return 1;   //정상종료
}

/* transpose the matrix to matrix_t */
//전치행렬 
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    if (matrix == NULL || matrix_t == NULL) {
        return -1;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix_t[i][j] = matrix[j][i];                          /*전치행렬은 기존 행렬의 행과 열이 바뀐 행렬이다
                                                                        행과 열의 인덱스를 바꿔 matrix_t에 값을 대입한다.*/
                                                                        /* check post conditions */
            if ((matrix_t[i][j] < 0) || (matrix_t[i][j] > 19)) {    //기존행렬의 행과 열을 바꾼 값을 대입한 것으로, 값의 조건인 0~19는 동일하게 작용한다
                printf("The component values ​​of the matrix are 0-19.\n");
                transpose_matrix(matrix, matrix_t, row, col);        //후처리검사에서 오류발생시, 함수 재호출
                return -1;  //비정상종료
            }
        }
    }
    return 1;   //정상종료
}



/* matrix_axt - matrix_a x matrix_t */
//행렬의 곱
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    if ((matrix_a == NULL) || (matrix_t == NULL)) {
        return -1;
    }
    /* 행렬과 전치행렬에 따른 각각의 행과 열
       원본 행렬 matrix_a의 행과 열은 row1,col1
       전치 행렬 matrix_t의 행과 열은 row2,col2*/
    int row1 = row;3
    //int col1 = col;
    int row2 = col; //전치행렬이므로, 행은 원본행렬의 열과 같다
    int col2 = row; //전치행렬이므로, 열은 원본행렬의 행과 같다
    int** matrix_c = create_matrix(row1, col2);               //두 행렬의 곱의 값을 저장할 행렬 생성위해 create_matrix 호출 
    //matrix_a의 행과 matrix_t의 열로 이루어진 matrix_c
    for (int i = 0; i < row1; i++)                          /* 행렬의 곱인 matrix_c의 행만큼 반복*/
    {
        for (int j = 0; j < col2; j++)  //col2=row1         /* 행렬의 곱인 matrix_c의 열만큼 반복*/
        {
            matrix_c[i][j] = 0; //값을 0으로 초기화
            for (int k = 0; k < row2; k++)  //row2=col1     /* 행렬 matrix_a의 열, matrix_t의 행만큼 반복*/
            {
                /* check post conditions */
                if ((matrix_a[i][k] * matrix_t[k][j] < 0) || (matrix_a[i][k] * matrix_t[k][j] > 361))  //두 행렬의 값이 0~19로, 곱이 0보다 작을 수 없고 361보다 클 수 없다.
                {
                    printf("The multiplied value must not be less than zero.\n");
                    multiply_matrix(matrix_a, matrix_t, row, col);                                  //후처리검사에서 오류발생시, 함수 재호출
                    return -1;  //비정상종료
                }
                matrix_c[i][j] += matrix_a[i][k] * matrix_t[k][j];   //한 행과 한 열의 곱을 모두 더한 값을 matrix_c[i][j]에 대입 
            }
        }
    }
    print_matrix(matrix_c, row1, col2); //matrix_c 출력
    return 1;   //정상종료
}