#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
// 좌표 입력 받을 때 사용 touuper
#include <ctype.h>
#include <time.h>
#include <windows.h>

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
bool isMine(int x, int y) {
    return isValid(x, y) && nearMine(x, y) == Bomb;
}

int totalBombs = 10;
int Level = 1;

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
        y = toupper(_getch()) - 'A';
    }

    // x 좌표 입력받기
    x = _getch() - '1';

    return isFlagMode;
}

int getFlagCount() {
    // 깃발 수를 세는 변수 count
    int count = 0;
    // 0~8번의 모든 행과 열의 좌표에 대해서 반복
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (state(x, y) == Flag) {
                count++;
            }
        }
    }
    return count;
}

// x, y 좌표와 인접한 8칸에 대해 지뢰 수를 count
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

    // nearMine(x, y)에 지뢰를 랜덤하게 생성
    for (int i = 0; i < Bombs; i++) {
        int x, y;
        do {
            x = rand() % 9;
            y = rand() % 9;        
            // 이미 지뢰가 있는 경우 다시 랜덤 좌표 생성
        } while (nearMine(x, y) == Bomb);  // 해당 조건식인 true이면 do 내부 문장 다시 실행
        nearMine(x, y) = Bomb;
    }
        
    // state(x, y)에 인접한 지뢰 수 저장, 모든 좌표에 대해서 반복
    for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
            // 해당 좌표가 지뢰가 아닌 경우에만
            if (nearMine(x, y) != Bomb) {
                countNearMine(x, y);
            }
		}
	}
}


// 지뢰 맵 print() 함수
void print() {
    // 전체 지뢰수와 발견한 지뢰 수 출력
    printf("발견(%d)/총 지뢰(%d)\n", getFlagCount(), totalBombs);

    // 열 라벨 표시
    printf("  ① ② ③ ④ ⑤ ⑥ ⑦ ⑧ ⑨\n");

    for (int y = 0; y < 9; y++) {
        // 행 라벨 표시
        printf("%c ", 'A' + y);	// ASCII 코드로 변환하여 출력

        // [y][x] 모든 좌표 값에 대해
        for (int x = 0; x < 9; x++) {
            // Hide(파지 않은) 상태인 곳이라면
            if (state(x, y) == Hide) {
                printf("■ ");
            }
            // Flag 상태(지뢰 예상 자리)인 경우
            else if (state(x, y) == Flag) {
                // 현재 콘솔 코드 페이지 저장
                UINT oldCP = GetConsoleOutputCP();
                // 인코딩 유니코드로 변경
                SetConsoleOutputCP(65001);
                // 깃발 출력
                printf(u8"\u2690 ");
                // 한글 인코딩 깨지지 않도록 이전 코드 페이지로 되돌려놓는다
                SetConsoleOutputCP(oldCP);
            }
            // open 상태인 곳에 대해 if
            else {
                // 지뢰인 좌표라면
                if (nearMine(x, y) == Bomb) {
                    // 현재 콘솔 코드 페이지 저장
                    UINT oldCP = GetConsoleOutputCP();
                    // 인코딩 유니코드로 변경
                    SetConsoleOutputCP(65001);
                    // 폭탄 출력
                    printf(u8"\u2620 ");
                    // 한글 인코딩 깨지지 않도록 이전 코드 페이지로 되돌려놓는다
                    SetConsoleOutputCP(oldCP);
                }
                // 지뢰가 아닌 좌표라면
                else if (nearMine(x, y)==Empty) {
                    printf("□ ");
                }
                else {
                    printf("%2d ", nearMine(x, y));
                }
            }
        }
        printf("\n");
    }
}