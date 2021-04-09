#include <iostream>
#include "reply_admin.h"

using namespace std;

ReplyAdmin::ReplyAdmin(){
	string* NewS = new string[NUM_OF_CHAT];
	chats = NewS;
	addChat("Hello, Reply Administrator!");
 	addChat("I will be a good programmer.");
 	addChat("This class is awesome.");
 	addChat("Professor Lim is wise.");
 	addChat("Two TAs are kind and helpful.");
 	addChat("I think male TA looks cool.");
}

ReplyAdmin::~ReplyAdmin(){
		delete[] chats;
	}

int ReplyAdmin::getChatCount(){
	int i;
	for(i=0; i<NUM_OF_CHAT; ++i)
	{string s = chats[i]; 
	if(s.empty() == true) break; 
	} 
	return i;
}

bool ReplyAdmin::addChat(string _chat){
	int nums = ReplyAdmin::getChatCount();
	chats[nums] = _chat;
	if(true) return true;
	else return false;
}

bool ReplyAdmin::removeChat(int _index){
	int nums = ReplyAdmin::getChatCount();
	for(int i=0;i<nums;++i){
		if(i == _index){
			for(; i<nums;++i) {chats[i] = chats[i+1];}
			return true;
		}
		else if(i>nums || i<0)
			return false;		
	}
}

bool ReplyAdmin::removeChat(int*_indices, int _count){
	int nums = ReplyAdmin::getChatCount();
		for(int j=0,k=0;j<_count;++j,++k){
			int number = _indices[j] - k;
		for(int i=0;i<nums;++i){
		if(number==i)
			for(;i<nums;++i){chats[i] = chats[i+1];}
		}
	}
	if(true)return true;
	else return false;
}

bool ReplyAdmin::removeChat(int _start, int _end){
	int nums = ReplyAdmin::getChatCount();
	if(_end>nums) _end = nums;
	if(_start < 0) _start = 0;
	int i = _start;
	for(int k=0;i<=_end;++i,++k){
	for(int j=i;j<nums;++j){chats[j-k] = chats[j-k+1];}
	}
	if(true)return true;
	else return false;
}

void ReplyAdmin::printChat(){
	int count = ReplyAdmin::getChatCount(); 
	for (int i = 0; i<count; ++i) { 
		cout << i << " " << chats[i] << endl;
	} 
}
