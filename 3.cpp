#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
#include<stdio.h>

#define MAX_LEN 5

void SetMyString1(char **pp_head);
char** SetMyString2();

int main(void)
{
	char arr[3][5] = {"abcd", "efgh", "ijkl"};
	char*ptr =(char*)malloc(sizeof(char)*MAX_LEN);
	SetMyString1(&ptr);
	char** pptr = NULL;
	pptr = SetMyString2();
	cout << *pptr  << ": *pptr" << endl;

	char** pp = (char**)malloc(sizeof(char*) * 3);
	for (unsigned int i = 0; i < 3; i++) {
		*(pp+i)= (char*)malloc(sizeof(char) * MAX_LEN);
	}
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < MAX_LEN; j++) {
			*(*(pp + 0)+i+0) = i * MAX_LEN + j + 97;
		}
	}
	for (unsigned int i = 0; i < 3; i++) {

		cout << *(*(pp + 0)+i)+0 << ": *(*(pp + 0)+" << i << ")+0 : " << i + 1 << "번째 주소 출력 " << ": " << *(*(pp + 0) + 0)+0 << "+" << i * 5 << "주소가 출력되어야함" << endl;
	}
	//주소출력(배열 : 연속적)
	printf("%p:&arr == %p: arr\n", &arr, arr);
	printf("\n");
	//주소출력(동적할당 : 연속적X)
	for (unsigned int i = 0; i < 3; i++) {
		printf("%p:pp[0]+%d=&arr[%d] %p:pp[0][%d]=arr[%d]\n", *(pp + 0) + i, i,i, *(*(pp + 0) + i) + 0, i,i);
	}
	for (unsigned int i = 0; i < 3; i++) {
		free(*(pp +i));
		cout << i << "번째 동적메모리해제완료" << endl;
	}
	free(pp);
	return 0;
}
void SetMyString1(char **pp_head)
{
	char arr[MAX_LEN] = "abcd";
	memcpy(*pp_head,arr, strlen(arr));
	*(*pp_head + strlen(arr)) = 0;
	cout << *pp_head << ": *pp_head" << endl;
	return;
}
char** SetMyString2()
{
	char* p = (char*)malloc(sizeof(char) * MAX_LEN);
	char arr[MAX_LEN] = "efgh";
	strcpy_s(p, strlen(arr) + 1, arr);
	cout << p << ": p" << endl;
	return &p;
}