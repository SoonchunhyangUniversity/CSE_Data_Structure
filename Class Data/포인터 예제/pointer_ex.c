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


	printf("*p = %d\n", *p); // ������ p�� ����Ű�� �ִ°��� ����� ��
	printf("p = %d %x\n", p, p); // ������ p�� ����� �ּҰ�(a�� �ּҰ�)
	printf("&p = %d %x\n\n", &p, &p); // ������ p�� �ּҰ�
	
	printf("*pp = %d %x\n", *pp, *pp); // ������ pp�� ����Ű�� �ִ°��� ����� ��
	printf("pp = %d %x\n", pp, pp); // ������ pp�� ����� �ּҰ�(������ p�� �ּҰ�)
	printf("&pp = %d %x\n\n", &pp, &pp);  // ������ pp�� �ּҰ�

	printf("&*p = %d %x\n", &*p, &*p); // ������ p�� ����Ű�� �ִ°��� �ּ�(a�� �ּҰ�)
	printf("&*pp = %d %x\n", &*pp, &*pp); // ������ pp�� ����Ű�� �ִ°��� �ּ�(������ p�� �ּҰ�)
	printf("&**pp = %d %x\n\n", &**pp, &**pp); // a�� �ּҰ�

	// ���� a�� ����� ���� �����ϴ� ���
	printf("a = %d\n", a);
	printf("*p = %d\n", *p);
	printf("**pp = %d\n\n", **pp);
	
}