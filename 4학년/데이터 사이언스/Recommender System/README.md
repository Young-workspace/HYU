# Recommender System

## 실행 환경
> python
> 

## 목표
> 영화 평점 예측 프로그램 구현
> > content-based 혹은 collaborative filtering 등을 이용
>   
> **Collaborative Filtering 이용**  
> Test data의 user-item pair에 대해서만 평점을 예측


## 실행 방법
> **파일명: recommender.py**  
> 실형 명령어: python recommender.py training_data_file test_data_file  
> > 예) python recommender.py u1.base u1.test  
> > 

## 확인 방법
> PA4.exe와 모든 파일들을 같은 폴더에 위치 시키면 정확도가 나온다
> > RMSE 사용해서 

### train data 형식
> [u_id]\t [item_id]\t [rating]\t [time_stamp]\n  
> 이미 평가된 item 들이다  


### test data 형식
> train data와 같음  
> 각 줄에 대해 평점 예측 필요  


### output 형식
> traning data file명을 이용해 prediction 파일 생성 
> > 예) u1.base 파일을 이용하면 u1.base_prediction.txt 생성  
> > 
> [u_id]\t [item_id]\t [rating]\n  
> test data의 모든 데이터를 저장해야 함

