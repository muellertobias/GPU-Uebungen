// POXISTestApp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <pthread.h> 
#define _UWIN

void* foo(void* vp) {
	int* p = (int*)vp;

	for (int i = 0; i < 10000; i++) {
		*p += i;
	}

	return p;
}

int main(int argc, char *argv[])
{
	int a = 0;
	pthread_t thr;
	pthread_create(&thr, NULL, foo, (void*)&a);

	pthread_join(thr, NULL);

	printf("Result: %d\n", a);

	scanf_s("%d", &a);
	return 0;
}