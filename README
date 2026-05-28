# xv6 Custom System Call : `setpriority()`

## 프로젝트 개요

본 프로젝트는 xv6 운영체제에 새로운 시스템 콜인 `setpriority()`를 추가하여
프로세스의 실행 우선순위를 동적으로 변경할 수 있도록 구현한 프로젝트이다.

```c
int setpriority(int pid, int priority);
```

기존 xv6는 모든 프로세스를 동일하게 처리하는 Round Robin 기반 스케줄러를 사용한다.
본 프로젝트에서는 프로세스마다 우선순위를 부여하고, scheduler가 높은 우선순위의 프로세스를 먼저 실행하도록 수정하였다.

---

# 프로젝트 목적

기존 xv6의 시스템 콜 예제들은 단순 출력 또는 정보 조회 수준의 기능이 많다.
본 프로젝트는 단순 syscall 추가를 넘어 실제 운영체제의 핵심 요소인 CPU Scheduling 정책을 직접 수정하는 것을 목표로 하였다.

이를 통해 다음 내용을 학습할 수 있다.

* 시스템 콜 구현 구조
* User Mode ↔ Kernel Mode 전환
* Trap 및 ecall 동작 원리
* Process 구조체 관리
* Scheduler 동작 방식
* Priority Scheduling 정책 구현

---

# 주요 기능

## 시스템 콜

```c
setpriority(pid, priority);
```

## 매개변수

| 인자       | 설명                |
| -------- | ----------------- |
| pid      | 우선순위를 변경할 프로세스 ID |
| priority | 변경할 우선순위 값        |

---

# 우선순위 규칙

priority 값이 작을수록 높은 우선순위를 가진다.

| priority 값 | 의미         |
| ---------- | ---------- |
| 0          | 가장 높은 우선순위 |
| 10         | 기본 우선순위    |
| 20         | 낮은 우선순위    |

---

# 구현 내용

## 1. Process 구조체 확장

수정 파일:

```text
kernel/proc.h
```

추가 내용:

```c
int priority;
```

각 프로세스가 자신의 우선순위 값을 저장할 수 있도록 `priority` 필드를 추가하였다.

---

## 2. 기본 우선순위 설정

수정 파일:

```text
kernel/proc.c
```

`allocproc()` 내부에 기본 priority 값을 추가하였다.

```c
p->priority = 10;
```

새롭게 생성되는 모든 프로세스는 기본적으로 priority 10을 가진다.

---

## 3. 시스템 콜 인터페이스 추가

수정 파일:

```text
kernel/syscall.h
kernel/syscall.c
user/user.h
user/usys.pl
```

다음 과정을 통해 시스템 콜을 연결하였다.

* 시스템 콜 번호 등록
* 유저 함수 선언
* ecall stub 자동 생성
* syscall dispatch table 등록

---

## 4. 커널 핸들러 구현

수정 파일:

```text
kernel/sysproc.c
```

구현 함수:

```c
uint64 sys_setpriority(void)
```

`argint()`를 사용하여 유저 영역에서 전달된 pid와 priority 값을 받아오고, 해당 프로세스의 priority 값을 변경하도록 구현하였다.

---

## 5. Scheduler 수정

수정 파일:

```text
kernel/proc.c
```

기존 xv6 scheduler는 RUNNABLE 프로세스를 순차적으로 실행하였다.

기존 방식:

```text
먼저 발견된 RUNNABLE 프로세스 실행
```

수정 후:

```text
priority 값이 가장 작은 RUNNABLE 프로세스 실행
```

즉, 우선순위가 높은 프로세스가 CPU를 먼저 할당받도록 변경하였다.

---

# 시스템 콜 동작 흐름

```text
User Program
    ↓
setpriority()
    ↓
ecall
    ↓
Trap 발생
    ↓
Kernel Mode 진입
    ↓
syscall dispatcher
    ↓
sys_setpriority()
    ↓
scheduler priority 반영
```

---

# 테스트 방법

예시:

```bash
$ ptest 3 0
setpriority success: pid=3 priority=0
```

해당 호출 이후 scheduler는 pid 3 프로세스를 우선적으로 실행하게 된다.

---

# 기존 xv6 시스템 콜과의 차별점

기존 xv6 예제 시스템 콜인:

* hello()
* uptime()
* getpid()

등은 단순 정보 조회 또는 출력 기능 중심이다.

반면 본 프로젝트는:

* Process 구조체 수정
* Scheduler 정책 수정
* Runtime 실행 순서 변경

등 실제 운영체제 핵심 동작에 직접 영향을 주는 기능을 구현하였다.

즉 단순 syscall 추가 수준이 아니라,
운영체제 내부 스케줄링 정책 자체를 확장한 프로젝트라는 점에서 차별성이 있다.

---

# 학습한 내용

본 프로젝트를 통해 다음 내용을 학습하였다.

* xv6 시스템 콜 구현 구조
* syscall dispatcher 동작 원리
* trap 및 ecall 처리 과정
* process table 관리 방식
* scheduler 구현 원리
* synchronization(lock) 사용
* kernel 내부 데이터 구조 수정

---

# 향후 개선 가능성

추가적으로 다음 기능 확장이 가능하다.

* Dynamic Priority Scheduling
* Aging 기법 추가
* Multi-Level Feedback Queue(MLFQ)
* CPU 사용량 기반 priority 조정
* 프로세스 모니터링 시스템 콜 추가

---

# 결론

본 프로젝트는 xv6에 Priority Scheduling 기능을 추가하여 실제 운영체제와 유사한 프로세스 관리 기능을 구현한 프로젝트이다.

단순 syscall 등록을 넘어 scheduler 정책을 직접 수정함으로써 운영체제의 핵심 구조를 이해하고 확장하는 경험을 할 수 있었다.
