# HW3

## Minimal Fighter
> **주어진 Skeleton code에서 Minimal Fighter 클래스를 구현(인터페이스, 메인 함수는 수정 X)**
> > 규칙을 모두 반영하도록 구현 
> > > 1. 모든 Fighter 체력이 0이하면 status=Dead, 입력 체력이 0이면 아래의 모든 행동할 수 없음  
> > > 2. Hit(H): Fighter가 enemy와 공격을 동시에 한 번씩 교환. 공격력만큼 상대방의 체력 감소
> > > 3. Attack(A): Fighter가 target을 일방적으로 공격. Target의 체력이 공격력만큼 감소, Fighter의 공격력은 0이 된다. Fighter의 체력 변화 X.  
> > > 4. Fight(F): Fighter와 enemy 둘 중 하나가 죽을 때까지 공격 교환. 동시에 죽을 경우 둘 다 죽은 걸로 처리  
> > >   
> > 올바르지 않은 입력 -> 종료  
>  
> 입력: 양의 정수나 0인 Fighter1의 체력 및 공격력, 액션(H,A,F), 양의 정수나 0인 Fighter2의 체력 및 공격력  
> 출력: 액션 이후 두 Fighter의 상태를 출력  


> **파일명: minimal_fighter 폴더 내에 존재**
> > minimal_fighter.cc  
> > minimal_fighter.h  
> > minimal_fighter_main.cc  
