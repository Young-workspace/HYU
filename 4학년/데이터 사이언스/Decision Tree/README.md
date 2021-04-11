# HW2 - Decision Tree

## 실행 환경
> python3


## 목표
>  Decision tree 구현
>  test set을 decision tree로 분류


## 실행 방법
> **파일명: dt.py**  
> 실행 명령어: dt.py training_file test_file output_file  
> > 예) dt.py dt_train.txt dt_test.txt dt_result.txt


## 데이터 셋
> buy_computer test set: 
> > dt_train.txt  
> > dt_test.txt
>  
> car_evaluation:
> > dt_train1.txt
> > dt_test1.txt


### Training set 형식
> 첫번 째 줄(카테고리 명): attribute_name1\t attribute_name2\t .... attribute_nameN\n  
> M 번 줄 (N-1개의 tuple): attribute1\t attribute2\t ... attributeN\n  
> attribute N은 tuple이 속하는 class  
>   
> car_evaluation 의 test set(data_train1.txt) 속성 값
> > Buying: vhigh, high, med, low  
> > Maint: vhigh, high, med, low  
> > Door: 2, 3, 4, 5more  
> > Persons: 2, 4, more  
> > Lug_boot: small, med, big  
> > Safety: low, med, high  
> > class_labels: unacc, acc, good, vgood  

### Test Set 형식
> training set 과 같지만 class 명인 attribute_name인 없음
