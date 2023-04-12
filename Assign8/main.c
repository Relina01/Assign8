#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef char element;
typedef struct
{
	element data[MAX_SIZE];
	int capacity;
	int count;
	int top;
} StackType;

void init_stack(StackType* s)
{
	for (int i = 0; i < MAX_SIZE; i++)
		s->data[i] = 32;
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return (s->top == (MAX_SIZE - 1));
}

void push(StackType* s, element op)
{
	if (is_full(s))
	{
		fprintf(stderr, "Error : Full\n");
		return;
	}
	else s->data[++(s->top)] = op;
}

element pop(StackType* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "Error : Empty\n");
		return 'e';
	}
	else return s->data[(s->top)--];
}

int peek(StackType* s)
{
	if (s->capacity == MAX_SIZE)
	{
		return s->data[s->capacity - 1];
	}
	return -1;
}

int prec(char op)
{
	switch (op)
	{
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}

StackType infix_to_postfix(char exp[])
{
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		switch (ch)
		{
		case '+': case '-': case '*': case '/':
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				printf("%c", pop(&s));
			push(&s, ch);
			s.count++;
			break;
		case '(': 
			push(&s, ch);
			s.count++;
			break;
		case ')':
			top_op = pop(&s);
			while (top_op != '(')
			{
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		default:
			printf("%c", ch);
			push(&s, ch - '0');
			break;
		}
	}
	return s;
}

int eval(StackType* s)
{
	int op1, op2, value, i = 0;
	int len = s->count;
	char ch;

	for (i = 0; i < len; i++)
	{
		ch = s->data[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
		{
			if (ch == 32)
				continue;
			else if (ch >= 48 && ch <= 57)
			{
				value = ch - '0';
				push(s, value);
			}
			else
				return -1;
		}
		else
		{
			op2 = pop(s);
			op1 = pop(s);
			switch (ch)
			{
			case '+': push(s, op1 + op2); break;
			case '-': push(s, op1 - op2); break;
			case '*': push(s, op1 * op2); break;
			case '/': push(s, op1 / op2); break;
			}
		}
	}
	return pop(s);
}

int main()
{
	StackType s2;
	char s[MAX_SIZE];
	char c;
	int i = 0, result;
	init_stack(&s2);
	printf("Enter infix exp : ");
	while ((c = getchar()) != '\n' && i < sizeof(s) - 1)
		s[i++] = c;
	s[i] = '\0';

	printf("Postfix exp : ");
	s2 = infix_to_postfix(s);
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (s2.data[i] == 32)
			break;
		else
			printf("%c", s2.data[i]);
	}
	printf("\n");
	result = eval(&s2);
	printf("Result : %d\n", result);
}