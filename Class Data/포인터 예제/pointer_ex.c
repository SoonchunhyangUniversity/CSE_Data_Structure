#include <stdio.h>

void main()
{
	int a;
	int *p;
	int **pp;

	a = 100;
	p = &a;
	pp = &p;

	printf("a = %d\n", a);
	printf("&a = %d %x\n\n", &a, &a);


	printf("*p = %d\n", *p); // 포인터 p가 가리키고 있는곳에 저장된 값
	printf("p = %d %x\n", p, p); // 포인터 p에 저장된 주소값(a의 주소값)
	printf("&p = %d %x\n\n", &p, &p); // 포인터 p의 주소값

	printf("*pp = %d %x\n", *pp, *pp); // 포인터 pp가 가리키고 있는곳에 저장된 값
	printf("pp = %d %x\n", pp, pp); // 포인터 pp에 저장된 주소값(포인터 p의 주소값)
	printf("&pp = %d %x\n\n", &pp, &pp);  // 포인터 pp의 주소값

	printf("&*p = %d %x\n", &*p, &*p); // 포인터 p가 가리키고 있는곳의 주소(a의 주소값)
	printf("&*pp = %d %x\n", &*pp, &*pp); // 포인터 pp가 가W리키고 있는곳의 주소(포인터 p의 주소값)
	printf("&**pp = %d %x\n\n", &**pp, &**pp); // a의 주소값

	// 변수 a에 저장된 값에 접근하는 방법
	printf("a = %d\n", a);
	printf("*p = %d\n", *p);
	printf("**pp = %d\n\n", **pp);

}
