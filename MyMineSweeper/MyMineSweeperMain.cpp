#include "MineSweeper.h"

void main() {
	int level;

	printf("\t[ MINE SWEEPER ]\n");
	printf("���̵� �Է� (�ʱ� 1�ܰ� 10�� / �߱� 2�ܰ� 20�� / ��� 3�ܰ� 30��\n(1, 2, 3 ���̵��� �Է��ϼ���) : ");
	scanf_s("%d", &level);
	printf("%d�ܰ��� Mine Sweeper Game �� �����մϴ�.\n\n", level);
	playMineSweeper(level);
}