# MyMineSweeper
```
※ 본 코드는 『게임으로 배우는 C++』 책의 지뢰찾기 예제를 기반으로,
구조와 흐름을 리팩토링하여 재구성한 개인 학습용 프로젝트입니다.
```
![화면 캡처 2025-03-30 074640](https://github.com/user-attachments/assets/40689d8b-244d-4248-b1b8-36a53a7070cd)

<details>
<summary>지뢰 찾기 구현</summary>

## 구현 함수
1. printMap()   
지뢰 맵을 화면에 출력하는 함수
​
2. resetGame()   
게임을 초기화하는 함수,
지뢰 맵을 초기화하고 입력받은 난이도의 맞는 지뢰의 개수만큼 지뢰를 설치한다.

3. isFinish()   
게임 종료 검사 함수
지뢰 찾기 성공 시 gameWin
지뢰 찾기 실패 시 gameLose
게임이 계속 진행되는 경우 gameContinue

4. getLocation()   
키보드로 좌표를 입력받는 함수,
깃발을 꽂는 모드와 그냥 해당 좌표를 Open하는 모드
행(A~I)과 열(1~9)을 입력받는다.

5. dig()   
입력받은 좌표를 여는 함수
​
6. flag()   
입력받은 좌표에 깃발을 꽂는 함수

7. getFlagCount()   
전체 좌표 내의 깃발 수를 계산하는 함수
​
8. countNearMine()   
인근 지뢰의 수 계산 함수

9. palyMineSweeper()   
지뢰 찾기 주 함수
</details>
