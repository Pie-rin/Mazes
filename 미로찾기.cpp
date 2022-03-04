#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 15
int treasure_num = 0, trap_num = 0;	//����, ������ ������ �� ����
int treasure_score = 0, trap_score = 0;	//��������, �ս������� ����� ����

//=====�����ڵ� ����=====
#define MAX_STACK_SIZE 100

typedef struct {
	short r;
	short c;
} element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

//���� �ʱ�ȭ �Լ�
void init_stack(StackType* s) {
	s->top = -1;
}

//���� ���� ���� �Լ�
int is_empty(StackType* s) {
	return (s->top == -1);
}

//��ȭ ���� ���� �Լ�
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

//�����Լ�
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

//�����Լ�
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

//��ũ�Լ�
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
//=====���� �ڵ��� ��=====

element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'e','0','0','0','0','1','c','1','1','1','0','1','1','C','1'},
	{'1','1','1','1','0','1','0','0','1','0','0','b','0','0','1'},
	{'1','0','0','c','0','1','1','0','1','1','1','1','0','1','1'},
	{'1','0','1','1','0','1','1','0','0','0','0','0','0','A','1'},
	{'1','0','C','1','0','1','C','0','1','1','1','0','1','1','1'},
	{'1','0','1','1','0','0','0','1','1','0','1','0','a','1','1'},
	{'1','0','0','0','b','1','1','1','c','0','0','B','0','0','1'},
	{'1','b','1','0','1','0','1','0','1','0','1','1','0','1','1'},
	{'1','1','1','0','0','0','a','0','1','0','1','0','0','0','x'},
	{'1','0','0','0','1','0','1','0','1','0','0','C','1','1','1'},
	{'1','0','1','c','1','0','1','0','B','0','1','0','0','1','1'},
	{'1','0','0','0','0','B','1','0','1','0','1','1','0','1','1'},
	{'1','A','1','1','1','0','1','0','1','0','c','1','C','0','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
};

//��ġ�� ���ÿ� ����
void push_loc(StackType* s, int r, int c) {
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

// �̷θ� ȭ�鿡 ����Ѵ�.
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf(" %c", maze[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}

//������ ������ ���� ������ ���� �ø���, ���������� ������ �ջ��Ѵ�.
void  encounter_treasure(char n) {
	(treasure_num)++;

	if (n == 'C') {	//���� ������ C�� ��� 1���� ���Ѵ�.
		treasure_score += 1;
		printf("����!! 1�� ȹ��\n");
	}
	if (n == 'B') {	//���� ������ B�� ��� 2���� ���Ѵ�.
		treasure_score += 2;
		printf("����!! 2�� ȹ��\n");
	}
	if (n == 'A') {	//���� ������ A�� ��� 3���� ���Ѵ�.
		treasure_score += 3;
		printf("����!! 3�� ȹ��\n");
	}

}

//������ ������ ���� ������ ���� �ø���, �ս������� ������ �ջ��Ѵ�.
void  encounter_trap(char n) {
	(trap_num)++;

	if (n == 'c') {	//���� ������ c�� ��� 1���� ���Ѵ�.
		trap_score += 1;
		printf("����!! 1�� ����\n");
	}
	if (n == 'b') {	//���� ������ b�� ��� 2���� ���Ѵ�.
		trap_score += 2;
		printf("����!! 2�� ����\n");
	}
	if (n == 'a') {	//���� ������ a�� ��� 3���� ���Ѵ�.
		trap_score += 3;
		printf("����!! 3�� ����\n");
	}
}

int main(void) {
	int r, c;
	StackType s;
	init_stack(&s);
	here = entry;

	while (maze[here.r][here.c] != 'x') {	//x�� ������ ������ �ݺ�
		r = here.r;
		c = here.c;

		char n = maze[r][c];	//���� ��ġ�� ���ڸ� �޴´�.
		if (n == 'C' || n == 'B' || n == 'A') {	//���� ��ġ�� ������ A,B,C�� ���
			encounter_treasure(n);
		}
		if (n == 'c' || n == 'b' || n == 'a') {	//���� ��ġ�� ������ a,b,c�� ���
			encounter_trap(n);
		}

		maze[r][c] = '.';	//������ ���� .���� ǥ���Ѵ�.
		maze_print(maze);	//�̷� �׸���

		push_loc(&s, r - 1, c);	//��,��,��,�� ĭ�� �˻��ϰ� ���ÿ� �ִ´�.
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		if (is_empty(&s)) {
			printf("����\n");
			return -1;
		}
		else {
			here = pop(&s);
		}
	}
	printf("����\n");
	printf("���� ���� ����: %d, ���� ���� ����: %d\n", treasure_num, trap_num);
	printf("���� ����: %d, �ս� ����: %d\n", treasure_score, trap_score);
	printf("����: %d\n", (treasure_score - trap_score));	//����==��������-�ս�����

	return 0;
}