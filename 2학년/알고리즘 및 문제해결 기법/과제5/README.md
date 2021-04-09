# HW 5

## Priority Queue
> 입력
> > 한줄에 최대 3개의 요소를 입력  
> > 첫 번째 요소가 0 -> output 출력 후 프로그램 종료  
> > 첫 번째 요소가 1 -> 두번째 요소를 insert  
> > 첫 번째 요소가 2 -> priority queue로 가장 큰 값 추출  
> > 첫 번째 요소가 3 -> 두 번째 요소와 일치하는 인덱스의 값을 세 번째 요소로 대체  
> > > 대체 후 heap sort를 다시  
> >   
>  Priority Queue의 smallest index는 1이라고 가정한다  
>  만약 2개의 children의 값이 같으면, 오른쪽 child는 parent과 **무조건** swap된다
>  
> 출력  
> > 첫 째줄: 추출된 요소 출력  
> > 두 번째 줄: 현재 heap 출력
>  
> **파일명: PriorityQueue.cpp**
