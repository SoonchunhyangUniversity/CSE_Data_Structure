/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 문제 1
 * 작성일 : 2018 - 05 - 29
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // fprintf함수 사용을 위한 헤더파일 선언
#include <ctype.h> // isdigit함수 사용을 위한 헤더파일 선언
#include <string.h> // strlen함수 사용을 위한 헤더파일 선언
#define MAX 50 // 기호상수 MAX를 50으로 정의
#define TRUE 1 // 기호상후 TRUE를 1으로 정의
#define FALSE 0 // 기호상수 FALSE를 0으로 정의

typedef int element; // typedef로 element키워드로 int형 데이터 선언 가능

/* 배열 기반 스택의 스택 구조체 */
typedef struct
{
	element stack[MAX];
	// 정수형 데이터를 저장하는 MAX길이의 배열
	int top;
	// 스택의 최상위 인덱스의 값
} StackType; // typedef로 StackType 키워드로 선언 가능

/* 스택 초기화 함수 */
void init(StackType *s)
{
	s->top = -1; // 스택의 최상위 인덱스 값을 -1로 저장
}

/* 공백 상태 검출 함수 */
int is_empty(StackType *s)
{
	return (s->top == -1);
	// 스택의 최상위 인덱스가 -1 이면 True 그렇지 않으면 False 반환
}

/* 포화 상태 검출 함수 */
int is_full(StackType *s)
{
	return (s->top == (MAX - 1));
	// 스택의 최상위 인덱스가 MAX - 1이면 True 그렇지 않으면 False 반환
}

/* 삽입 함수 */
void push(StackType *s, element item)
{
	/* 스택이 가득 차 있으면 */
	if (is_full(s))
	{
		fprintf(stderr, "스택 포화 에러\n"); // 에러 메세지 출력
		exit(1); // 프로그램 종료
	}

	/* 스택이 가득 차있지 않으면 */
	else
		s->stack[++(s->top)] = item;
		// 스택의 최상위 인덱스 다음 인덱스에 item 저장
}

/* 삭제 함수 */
element pop(StackType *s)
{
	/* 스택이 비어있으면 */
	if (is_empty(s))
	{
		fprintf(stderr, "스택 공백 에러\n"); // 에러 메세지 출력
		exit(1); // 프로그램 종료
	}

	/* 스택이 비어있지 않으면 */
	else
		return s->stack[(s->top)--];
		// 스택의 최상위 인덱스 값 반환 후 top을 1 빼줌
}

/* 피크 함수 */
element peek(StackType *s)
{
	/* 스택이 비어있으면 */
	if (is_empty(s))
	{
		fprintf(stderr, "스택 공백 에러\n"); // 에러 메세지 출력
		exit(1); // 프로그램 종료
	}

	/* 스택이 비어있지 않으면 */
	else
		return s->stack[s->top];
		// 스택의 최상위 인덱스 값 반환
}

/* 괄호 검사 함수 */
int check_matching(char *in)
{
	StackType s;
	// 스택 구조체 선언
	char ch, open_ch;
	// 문자를 저장할 변수 선언
	int i, n = strlen(in);
	// 반복문에서 사용할 변수 선언
	// 문자열의 길이를 저장할 변수 선언 및 strlen함수로 길이 저장

	init(&s); // 스택의 초기화

	/* 문자열의 길이만큼 반복하는 반복문 */
	for (i = 0; i < n; i++)
	{
		ch = in[i]; // 다음 문자

		switch (ch)
		{
		/* ch가 여는 괄호면 */
		case '(':
		case '[':
		case '{':
			push(&s, ch); // 스택에 삽입
			break;

		/* ch가 닫는 괄호면 */
		case ')':
		case ']':
		case '}':
			if (is_empty(&s)) // 스택이 비어있다면
				return FALSE; // FALSE 반환

			else // 스택이 비어있지 않다면
			{
				open_ch = pop(&s); // 스택의 데이터를 pop해서 저장

				/* 올바른 괄호 쌍이 아니면 */
				if ((open_ch == '(' && ch != ')') ||
					(open_ch == '[' && ch != ']') ||
					(open_ch == '{' && ch != '}'))
					return FALSE; // FALSE 반환
			}
			break;

		/* 괄호가 아니면 */
		default:
			break;
		}
	}

	/* 스택에 남아있으면 오류 */
	if (!is_empty(&s))
		return FALSE; // FALSE 반환

	return TRUE; // TRUE 반환
}

/* 연산자의 우선 순위를 반환하는 함수 */
int prec(char op)
{
	switch (op)
	{
	/* 곱셈, 나눗셈 연산자일 경우 */
	case '*':
	case '/':
		return 2; // 2 반환

	/* 덧셈, 뺄셈 연산자일 경우 */
	case '+':
	case '-':
		return 1; // 1 반환

	/* 괄호일 경우 */
	case '(':
		return 0; // 0 반환
	}

	/* 나머지의 경우 */
	return -1; // -1 반환
}

/* 연산자의 우선순위를 확인하는 함수 */
int prec_check(char op1, char op2)
{
	int op1Prec = prec(op1);
	// op1Prec에 연산자 op1의 우선순위 값 저장
	int op2Prec = prec(op2);
	// op2Prec에 연산자 op2의 우선순위 값 저장

	/* op1의 우선순위가 op2보다 크다면 */
	if (op1Prec > op2Prec)
		return 1; // 1 반환

	/* op2의 우선순위가 op1보다 크다면 */
	else if (op1Prec < op2Prec)
		return -1; // -1 반환

	/* 두 연산자의 우선순위가 같다면 */
	else
		return 0; // 0 반환
}

/* 후위연산식을 중위연산식으로 바꾸는 함수 */
int postfix_to_infix(char exp[])
{
	StackType stack;
	// 스택 구조체 선언
	int expLen = strlen(exp);
	// 후위연산식의 길이를 저장할 변수 선언 및 strlen함수로 초기화
	int convLen;
	// 중위연산식으로 변환한 문자열의 길이를 저장할 변수 선언
	char convExp[MAX] = { 0 };
	// 중위연산식을 저장할 문자열 선언 및 초기화

	int i, j, idx = 0;
	// 반복문에서 사용할 변수 선언, 문자열의 인덱스를 가리키는 변수 선언 및 초기화
	char tok;
	// 문자를 임시로 저장할 변수 선언

	init(&stack); // 스택의 초기화

	/* expLen번 반복하는 반복문 */
	for (i = 0; i < expLen; i++)
	{
		if (i == 1) // i가 1일 경우(무조건 피연산자가 저장)
		{
			tok = pop(&stack); // pop한 데이터를 tok에 저장
			convExp[idx++] = tok; // convExp에 tok 저장
		}

		/* exp[i]가 연산자일 경우 */
		if (exp[i] == '+' || exp[i] == '-' ||
			exp[i] == '*' || exp[i] == '/')
		{
			tok = pop(&stack); // pop한 데이터를 tok에 저장

			convExp[idx++] = exp[i]; // convExp에 연산자 저장 후 idx 1증가
			convExp[idx++] = tok; // convExp에 tok 저장 후 idx 1증가
			convExp[idx++] = ')'; // convExp에 ')' 저장 후 idx 1증가

			convLen = strlen(convExp); // strlen함수로 convExp의 길이를 저장

			/* convLen번 반복하는 반복문 */
			for (j = convLen; j >= 0; j--)
				convExp[j] = convExp[j - 1]; // 한 칸씩 오른쪽으로 이동

			convExp[0] = '('; // convExp의 맨 앞을 '('로 저장
			idx++; // idx 1증가
		}

		/* exp[i]가 연산자가 아닐 경우 */
		else
		{
			push(&stack, exp[i]); // exp[i]를 스택에 push
		}
	}

	/* 스택이 비어있지 않을 경우 */
	if (!is_empty(&stack))
		return FALSE; // FALSE 반환

	/* 괄호 검사에 실패할 경우 */
	if (!check_matching(convExp))
		return FALSE; // FALSE 반환

	strcpy(exp, convExp); // exp에 convExp 복사

	return TRUE; // TRUE 반환
}

/* 후위표기식을 계산하는 함수 */
int eval(char exp[])
{
	StackType stack;
	// 스택 구조체 선언
	int expLen = strlen(exp);
	// 후위연산식의 길이를 저장할 변수 선언 및 strlen함수로 초기화
	int i;
	// 반복문에서 사용할 변수 선언
	char tok, op1, op2;
	// 문자를 임시로 저장할 변수, 피연산자를 임시로 저장할 변수 선언

	init(&stack); // 스택의 초기화

	/* expLen만큼 반복하는 반복문 */
	for (i = 0; i < expLen; i++)
	{
		tok = exp[i]; // tok에 exp[i]를 저장

		/* tok가 숫자라면 */
		if (isdigit(tok))
		{
			push(&stack, tok - '0'); // 스택에 문자를 숫자로 바꿔 삽입
		}

		/* 숫자가 아니라면 */
		else
		{
			op2 = pop(&stack);	// 두 번째 피연산자 pop해서 저장
			op1 = pop(&stack);	// 첫 번째 피연산자 pop해서 저장

			switch (tok)
			{
			/* 덧셈 연산자일 경우 */
			case '+':
				push(&stack, op1 + op2);
				// op1 + op2결과를 스택에 push
				break;

			/* 밸셈 연산자일 경우 */
			case '-':
				push(&stack, op1 - op2);
				// op1 - op2결과를 스택에 push
				break;

			/* 곱셈 연산자일 경우 */
			case '*':
				push(&stack, op1 * op2);
				// op1 * op2결과를 스택에 push
				break;

			/* 나눗셈 연산자일 경우 */
			case '/':
				push(&stack, op1 / op2);
				// op1 / op2결과를 스택에 push
				break;
			}
		}
	}

	return pop(&stack); // 계산 결과를 pop하여 반환
}

/* 결과를 출력하는 함수 */
void display(char exp[])
{
	int result = eval(exp);
	// 후위연산식의 결과를 저장할 변수 선언 및 값 저장

	printf("후위표기식 : %s\n", exp); // 후위 표기식 출력

	/* postfix_to_infix함수로 중위 표기식으로 바꿔 주는데 실패할 경우 */
	if (!postfix_to_infix(exp))
		printf("잘못된 표기식입니다.\n"); // 에러 메세지 출력

	/* 그렇지 않으면 */
	else
	{
		printf("중위표기식 : %s\n", exp); // 중위 표기식 결과 출력
		printf("결      과 : %d\n\n", result); // 수식 계산 결과 출력
	}
}

int main() // 메인 함수 시작
{
	char postfix[MAX] = { 0 };
	// 후위 표기식을 임시로 저장할 문자열 선언 및 초기화

	/* 파일 포인터 fp 선언 및 data1.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data1.txt", "r");

	/* 파일을 여는데 실패했을 경우 */
	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n"); // 에러 메세지 출력
		exit(-1); // 프로그램 종료
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%s", postfix); // 파일에서 문자열을 한 줄 읽어온다.
		display(postfix); // display함수로 값 출력
	}

	fclose(fp); // 열어준 파일 포인터를 닫아준다.

	return 0; // 메인 함수 종료
}
