#include "MineSweeper.h"

void main() {
	int level;

	printf("\t[ MINE SWEEPER ]\n");
	printf("난이도 입력 (초급 1단계 10개 / 중급 2단계 20개 / 고수 3단계 30개\n(1, 2, 3 난이도를 입력하세요) : ");
	scanf_s("%d", &level);
	printf("%d단계의 Mine Sweeper Game 을 시작합니다.\n\n", level);
	playMineSweeper(level);
}