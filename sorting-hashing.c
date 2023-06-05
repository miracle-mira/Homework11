/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*기호상수 선언*/
#define MAX_ARRAY_SIZE			13	      
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/*함수원형*/

/*배열 정리*/
int initialize(int **a);        //배열 초기화 함수 
int freeArray(int *a);          //동적 할당 해제 함수
void printArray(int *a);        //배열 출력 함수

/*정렬함수*/
int selectionSort(int *a);      //선택정렬
int insertionSort(int *a);      //삽입정렬
int bubbleSort(int *a);         //버블정렬
int shellSort(int *a);          //쉘정렬
int quickSort(int *a, int n);   //퀵정렬: 재귀함수 사용

/*hasing*/
int hashCode(int key);            //hash code generator, key % MAX_HASH_TABLE_SIZE 
int hashing(int *a, int **ht);    //array a에대 한 hash table을 만든다.
int search(int *ht, int key);     //hash table에서 key를 찾아 hash table의 index return 


int main()
{

	printf("\n\n----- [Park Mira] [2020069006] -----\n\n");


	char command;

	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


/*배열 초기화 함수*/
int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}


/*동적 할당 해제 함수*/
int freeArray(int *a)
{
	if(a != NULL)
		free(a);

	return 0;
}


/*배열 출력 함수*/
void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


/*선택정렬*/
int selectionSort(int* a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  // 주어진 배열을 출력하는 함수 호출

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;  // 현재 인덱스를 최소값 인덱스로 초기화
		min = a[i];  // 현재 인덱스의 값을 최소값으로 초기화

		for (j = i + 1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])  // 최소값보다 작은 값을 찾았을 때
			{
				min = a[j];  // 최소값 업데이트
				minindex = j;  // 최소값의 인덱스 업데이트
			}
		}

		// 현재 인덱스와 최소값 인덱스의 값 교환
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  // 정렬된 배열을 출력하는 함수 호출
	return 0;
}

/*삽입정렬*/
int insertionSort(int *a)
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);  // 주어진 배열을 출력하는 함수 호출

    for (i = 1; i < MAX_ARRAY_SIZE; i++)
    {
        t = a[i];  // 현재 인덱스의 값을 임시 변수에 저장
        j = i;

        // 현재 인덱스 이전의 원소들과 비교하여 삽입 위치를 찾음
        while (a[j - 1] > t && j > 0)
        {
            a[j] = a[j - 1];  // 현재 원소보다 큰 값들을 오른쪽으로 이동시킴
            j--;
        }

        a[j] = t;  // 삽입 위치에 임시 변수의 값을 저장
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);  // 정렬된 배열을 출력하는 함수 호출

    return 0;
}

/*버블정렬*/
int bubbleSort(int* a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  // 주어진 배열을 출력하는 함수 호출

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j - 1] > a[j])  // 인접한 두 원소를 비교하여 순서가 잘못되어 있다면
			{
				t = a[j - 1];  // 임시 변수에 현재 원소를 저장
				a[j - 1] = a[j];  // 현재 원소와 다음 원소의 위치를 교환
				a[j] = t;  // 다음 원소에 임시 변수의 값을 저장
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  // 정렬된 배열을 출력하는 함수 호출

	return 0;
}

/*셀 정렬*/
int shellSort(int* a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  // 주어진 배열을 출력하는 함수 호출

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];  // 현재 원소를 임시 변수에 저장
				k = j;

				// 삽입 정렬을 응용하여 h 간격의 원소들을 정렬
				while (k > h - 1 && a[k - h] > v)
				{
					a[k] = a[k - h];  // 현재 원소보다 큰 값들을 h 간격만큼 오른쪽으로 이동
					k -= h;
				}

				a[k] = v;  // 삽입 위치에 임시 변수의 값을 저장
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  // 정렬된 배열을 출력하는 함수 호출

	return 0;
}

/*퀵정렬: 재귀함수 사용*/
int quickSort(int* a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n - 1];  // 피벗으로 사용할 마지막 원소 선택
		i = -1;
		j = n - 1;

		// 피벗을 기준으로 분할하는 과정
		while (1)
		{
			while (a[++i] < v);  // 피벗보다 큰 값을 찾을 때까지 i를 증가
			while (a[--j] > v);  // 피벗보다 작은 값을 찾을 때까지 j를 감소

			if (i >= j) break;  // i와 j가 교차하면 분할을 종료

			t = a[i];  // a[i]와 a[j]를 교환
			a[i] = a[j];
			a[j] = t;
		}

		t = a[i];  // 피벗의 위치를 변경
		a[i] = a[n - 1];
		a[n - 1] = t;

		// 분할된 두 부분 배열에 대해 재귀적으로 퀵 정렬을 수행
		quickSort(a, i);  // 피벗의 왼쪽 부분 배열에 대해 퀵 정렬
		quickSort(a + i + 1, n - i - 1);  // 피벗의 오른쪽 부분 배열에 대해 퀵 정렬
	}

	return 0;
}

/*Hasing코드*/

/*hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

/*array a에대 한 hash table을 만든다.*/
int hashing(int* a, int** ht)
{
	int* hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);  // 해시 테이블 크기만큼 메모리 할당
		*ht = hashtable;  // 할당된 메모리의 주소를 복사하여 main 함수에서 배열을 제어할 수 있도록 함
	}
	else {
		hashtable = *ht;  // hash table이 NULL이 아닌 경우, 테이블 재활용 및 초기화
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;  // 해시 테이블을 -1로 초기화

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];  // 현재 원소를 key로 설정
		hashcode = hashCode(key);  // key를 해시코드로 변환

		if (hashtable[hashcode] == -1)  // 해당 해시 테이블 위치가 비어있는 경우
		{
			hashtable[hashcode] = key;  // key를 해당 위치에 저장
		}
		else
		{
			index = hashcode;

			while (hashtable[index] != -1)  // 충돌 발생 시 해시 충돌을 해결하기 위해 선형 탐색
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;  // 다음 위치로 이동 (선형 탐색)
			}
			hashtable[index] = key;  // 충돌이 발생하지 않는 위치에 key를 저장
		}
	}

	return 0;
}

/*hash table에서 key를 찾아 hash table의 index return */
int search(int* ht, int key)
{
	int index = hashCode(key);  // key의 해시코드를 계산하여 인덱스로 설정

	if (ht[index] == key)  // 해당 인덱스에 저장된 값이 key와 일치하는 경우
		return index;

	while (ht[++index] != key)  // 일치하는 값이 나올 때까지 다음 위치로 이동 (선형 탐색)
	{
		index = index % MAX_HASH_TABLE_SIZE;  // 배열의 처음 위치로 이동하여 계속 탐색
	}
	return index;  // 일치하는 값이 저장된 인덱스 반환
}



