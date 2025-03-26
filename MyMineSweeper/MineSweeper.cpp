#include <stdio.h>
#include <stdlib.h>

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