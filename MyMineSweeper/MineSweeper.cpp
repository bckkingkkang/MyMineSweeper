#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
// ��ǥ �Է� ���� �� ��� touuper
#include <ctype.h>
#include <time.h>
#include <windows.h>

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
bool isMine(int x, int y) {
    return isValid(x, y) && nearMine(x, y) == Bomb;
}

int totalBombs = 10;
int Level = 1;

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
        y = toupper(_getch()) - 'A';
    }

    // x ��ǥ �Է¹ޱ�
    x = _getch() - '1';

    return isFlagMode;
}

int getFlagCount() {
    // ��� ���� ���� ���� count
    int count = 0;
    // 0~8���� ��� ��� ���� ��ǥ�� ���ؼ� �ݺ�
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (state(x, y) == Flag) {
                count++;
            }
        }
    }
    return count;
}

// x, y ��ǥ�� ������ 8ĭ�� ���� ���� ���� count
void countNearMine(int x, int y) {
    int count = 0;
    for (int dx = x - 1; dx <= x + 1; dx++) {
        for (int dy = y - 1; dy <= y + 1; dy++) {
            if (isMine(dx, dy)) {
                count++;
            }
        }
    }
    nearMine(x, y) = count;
}

void resetGame(int Level = 1) {
    srand((int unsigned)time(NULL));

    int Bombs = 0;

    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            state(x, y) = Hide;
            nearMine(x, y) = 0;
        }
    }

    switch (Level) {
    case 1:
        Bombs = 10;
        break;
    case 2:
        Bombs = 20;
        break;
    case 3:
        Bombs = 30;
        break;
    default :
		Bombs = 10;
		break;
    }

    totalBombs = Bombs;

    // nearMine(x, y)�� ���ڸ� �����ϰ� ����
    for (int i = 0; i < Bombs; i++) {
        int x, y;
        do {
            x = rand() % 9;
            y = rand() % 9;        
            // �̹� ���ڰ� �ִ� ��� �ٽ� ���� ��ǥ ����
        } while (nearMine(x, y) == Bomb);  // �ش� ���ǽ��� true�̸� do ���� ���� �ٽ� ����
        nearMine(x, y) = Bomb;
    }
        
    // state(x, y)�� ������ ���� �� ����, ��� ��ǥ�� ���ؼ� �ݺ�
    for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
            // �ش� ��ǥ�� ���ڰ� �ƴ� ��쿡��
            if (nearMine(x, y) != Bomb) {
                countNearMine(x, y);
            }
		}
	}
}


// ���� �� print() �Լ�
void print() {
    // ��ü ���ڼ��� �߰��� ���� �� ���
    printf("�߰�(%d)/�� ����(%d)\n", getFlagCount(), totalBombs);

    // �� �� ǥ��
    printf("  �� �� �� �� �� �� �� �� ��\n");

    for (int y = 0; y < 9; y++) {
        // �� �� ǥ��
        printf("%c ", 'A' + y);	// ASCII �ڵ�� ��ȯ�Ͽ� ���

        // [y][x] ��� ��ǥ ���� ����
        for (int x = 0; x < 9; x++) {
            // Hide(���� ����) ������ ���̶��
            if (state(x, y) == Hide) {
                printf("�� ");
            }
            // Flag ����(���� ���� �ڸ�)�� ���
            else if (state(x, y) == Flag) {
                // ���� �ܼ� �ڵ� ������ ����
                UINT oldCP = GetConsoleOutputCP();
                // ���ڵ� �����ڵ�� ����
                SetConsoleOutputCP(65001);
                // ��� ���
                printf(u8"\u2690 ");
                // �ѱ� ���ڵ� ������ �ʵ��� ���� �ڵ� �������� �ǵ������´�
                SetConsoleOutputCP(oldCP);
            }
            // open ������ ���� ���� if
            else {
                // ������ ��ǥ���
                if (nearMine(x, y) == Bomb) {
                    // ���� �ܼ� �ڵ� ������ ����
                    UINT oldCP = GetConsoleOutputCP();
                    // ���ڵ� �����ڵ�� ����
                    SetConsoleOutputCP(65001);
                    // ��ź ���
                    printf(u8"\u2620 ");
                    // �ѱ� ���ڵ� ������ �ʵ��� ���� �ڵ� �������� �ǵ������´�
                    SetConsoleOutputCP(oldCP);
                }
                // ���ڰ� �ƴ� ��ǥ���
                else if (nearMine(x, y)==Empty) {
                    printf("�� ");
                }
                else {
                    printf("%2d ", nearMine(x, y));
                }
            }
        }
        printf("\n");
    }
}