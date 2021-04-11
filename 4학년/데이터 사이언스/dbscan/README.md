# HW3 - DB Scan

## 실행 환경
> python 
> 

## 목표
> DB scan을 이용한 clustering
> 

## 실행 방법
> **파일명: clustering.py**  
> 실행 명령어: python clustering.py input1.txt n eps minPts  
> > 예) python clustering.py 8 15 22  
> > n: cluster 개수  
> > eps: neighborhood의 max radius  
> > minPts: 주어진 점의 eps-neighborhood의 최소 점의 개수  
>  
> sample data 폴더의 정답과 결과를 비교해서 점수를 낸다.

### input 파일 형식
> [object_id]/t [x_coordinate]\t [y_coordinate]\n  
> 각 행: object의 정보를 저장  
> object_id: object의 identifier  
> x_coordinate, y_coordinate: 2D space에서 object의 위치 
> 

### output 파일 형식
> 각 input data 당 **n개의 output 파일**  
> > input#_cluster_0.txt
> > > [object_id]\n [object_id]\n ...  
>  
> outlier는 무시/제거해도 됨
