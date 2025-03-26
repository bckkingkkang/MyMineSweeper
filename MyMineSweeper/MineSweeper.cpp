#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

// ����(x,y) : Open/Hide/Flag
// �������ڼ�(x,y) : 0~8, 9�� ���ڸ� ��Ÿ����.

enum State {
    Hide,	// 0
    Open,	// 1
    Flag	//2
};
enum NearMine {
    Empty = 0,
    Bomb = 9
};

// MapState, MapMine ����
// State�� NearMine�� enum �����̱� ������ int�� ������ �迭
int MapState[9][9];	// UI ����
int MapMine[9][9];	// �α� ������ ����

// �� ������ �����ϰ� �ϱ� ���� ������ ���
// Ư�� (x, y)�� ��ǥ�� �����ϸ� �ش� ��ǥ�� UI ����(state(x, y)), �α� ������ ����(nearMine(x, y)) return(��ȯ)
int& state(int x, int y) { return MapState[y][x]; }
int& nearMine(int x, int y) { return MapMine[y][x]; }

bool isValid(int x, int y) {
    return x < 9 && x >= 0 && y < 9 && y >= 0;
}

// �Է¹��� ��ǥ�� ���� �Լ�
void dig(int x, int y)
{
    // �ش� ��ǥ�� ������ �ʾҴٸ�
    if (state(x, y) != Open && isValid(x, y)) {
        // �ش� ��ǥ�� Open���� ����
        state(x, y) = Open;

        // ������ ��ǥ 8ĭ ���� ���ڰ� ���ٸ�(������_����_��(x, y)=0�̸�)
        if (nearMine(x, y) == 0) {
            for (int i = x - 1; i <= x + 1; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    dig(i, j);
                }
            }
        }
    }
}

// �Է¹��� ��ǥ�� ����� �ȴ� �Լ�
void flag(int x, int y) {
    if (isValid(x, y) && state(x, y) == Hide) {
        state(x, y) = Flag;
    }
}

// Flag ��ǥ�� �޴� ����� true�� ��ȯ�ϰ� Open ��ǥ�� �޴� ���� false�� ��ȯ�Ѵ�. - bool
bool getLocation(int& x, int& y) {
    printf("\n(����� ���� ��ġ�� �����Ϸ��� 'F'�� �߰� �Է��ϼ���)\n");
    printf("��(A~I)�� ��(1~9)�� �Է��ϼ��� : \n");
    printf("�Է� : ");

    // 'F' �Է� �� ��� ���(true)�� ��ȯ
    bool isFlagMode = false;

    // �Է¹��� ���ڸ� ������ �빮�ڷ� ��ȯ �� 'A'�� ���� y ��ǥ�� ���� ���Ѵ�.
    y = toupper(_getch()) - 'A';

    // 'F'�� �Է¹��� ���
    if (y == 'F' - 'A') {
        // ��� ���� ��ȯ
        isFlagMode = true;

        // �Է¹��� ù ��° ���ڸ� isFlagMode ���濡 ����߱� ������ �ٽ� y ��ǥ �Է¹ޱ�
        y = toupper(_getche()) - 'A';
    }

    // x ��ǥ �Է¹ޱ�
    x = _getch() - '1';

    return isFlagMode;
}