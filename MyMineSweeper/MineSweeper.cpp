#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

// 상태(x,y) : Open/Hide/Flag
// 인접지뢰수(x,y) : 0~8, 9는 지뢰를 나타낸다.

enum State {
    Hide,	// 0
    Open,	// 1
    Flag	//2
};
enum NearMine {
    Empty = 0,
    Bomb = 9
};

// MapState, MapMine 구현
// State와 NearMine이 enum 형식이기 때문에 int형 이차원 배열
int MapState[9][9];	// UI 상태
int MapMine[9][9];	// 인근 지뢰의 상태

// 값 변경을 가능하게 하기 위해 참조자 사용
// 특정 (x, y)의 좌표를 전달하면 해당 좌표의 UI 상태(state(x, y)), 인근 지뢰의 상태(nearMine(x, y)) return(반환)
int& state(int x, int y) { return MapState[y][x]; }
int& nearMine(int x, int y) { return MapMine[y][x]; }

bool isValid(int x, int y) {
    return x < 9 && x >= 0 && y < 9 && y >= 0;
}

// 입력받은 좌표를 여는 함수
void dig(int x, int y)
{
    // 해당 좌표가 열리지 않았다면
    if (state(x, y) != Open && isValid(x, y)) {
        // 해당 좌표를 Open으로 변경
        state(x, y) = Open;

        // 인접한 좌표 8칸 내에 지뢰가 없다면(인접한_지뢰_수(x, y)=0이면)
        if (nearMine(x, y) == 0) {
            for (int i = x - 1; i <= x + 1; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    dig(i, j);
                }
            }
        }
    }
}

// 입력받은 좌표에 깃발을 꽂는 함수
void flag(int x, int y) {
    if (isValid(x, y) && state(x, y) == Hide) {
        state(x, y) = Flag;
    }
}

// Flag 좌표를 받는 모드라면 true를 반환하고 Open 좌표를 받는 경우는 false를 반환한다. - bool
bool getLocation(int& x, int& y) {
    printf("\n(깃발을 꽂을 위치를 선택하려면 'F'를 추가 입력하세요)\n");
    printf("행(A~I)과 열(1~9)을 입력하세요 : \n");
    printf("입력 : ");

    // 'F' 입력 시 깃발 모드(true)로 전환
    bool isFlagMode = false;

    // 입력받은 문자를 무조건 대문자로 변환 후 'A'를 빼서 y 좌표의 값을 구한다.
    y = toupper(_getch()) - 'A';

    // 'F'를 입력받은 경우
    if (y == 'F' - 'A') {
        // 깃발 모드로 전환
        isFlagMode = true;

        // 입력받은 첫 번째 문자를 isFlagMode 변경에 사용했기 때문에 다시 y 좌표 입력받기
        y = toupper(_getche()) - 'A';
    }

    // x 좌표 입력받기
    x = _getch() - '1';

    return isFlagMode;
}