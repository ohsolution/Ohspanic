
![image](https://user-images.githubusercontent.com/43700074/195869565-27e8feef-a35f-4a7a-8bb4-2dcf8665bd7c.png)


이 프로젝트는 ncurses 라이브러리와 c++ 을 이용하여 개발한 간단한 터미널 게임이며
우분투 18.04 버젼에서 개발되었고 실행됩니다.

OhsPanic 실행파일과 OhsPanic.c,attack.h,monster.h 소스파일
컴파일을 돕기 위한 makefile 과 런타임 중 명령을 지원하기 위한 support 파일로 이루어져 있습니다.

마지막 업데이트 일자는 2020년 06월 14일 입니다.

## 주요 버그 사항

* 다각형 내부 판단 부정확

* 벽에 붙을 시 무적상태

* stone 몬스터 3번 공격 위험 신호가 벽에 막히는 경우 처리


## 개발 취약 사항

* 헤더 소스 분리 안되어있음

* 비효율적인 구현 다수 존재


## 업그레이드 필요한 사항

* 게임의 난이도가 점점 쉬워지는 문제

* 직관적으로 게임을 이해하기 어려움 -> 튜토리얼 구현 필요

## 플레이 영상
https://www.youtube.com/watch?v=njzje-PgPsM
