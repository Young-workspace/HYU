# HW1 - Apriori

## 개발 환경
> OS: windows
> Languages: Python

## 구현 목표
> Apriori 알고리즘으로 association 찾기

## 실행 방법
> **파일명: apriori.py**  
> python apirori.py minimum_support input_file output_file  
> 예: python apirori.py 5 input.txt output.txt  

### input file 형식
> item_id \t item_id \n
> > 예) 18\t 2\t 4\n  
>  
> 한 줄에 중복 id는 존재하지 않는다  
> id는 전부 숫자  

### output file 형식
> {item_set}\t {associative_item_set}\t support(%)\t confidence(%)\n
> > 예) {1} {8} 14.4- 51.68
>  
> **순서는 중요하지 않음**  
> support와 confidence는 round 2 decimal로 

