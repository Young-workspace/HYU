#include<iostream>
#include<string>
#include<stdio.h>

using namespace std;

const in NUM_OF_CHAT = 200;

bool addChat(string *_chatList, string _chat);
bool removeChat(string *_chatList, int _index);

int # (){

}
int main(void){
	string *chats = new string [NUM_OF_CHAT];

	addChat(chats, "Hello, Reply Administrator!");
	addChat(chats, "I will be a good programmer");



	while (true){
		string command;
		getline(cin,command);

		if(/*#quit*/){
			break;
		}
		else if (/*#remove*/){
			remove chat;
			if(/*remove is succedded*/){
				printChat(chats);
			}
		}
		else if(addChat(chats, command)){
			printChat(chats);
		}
	
	}
	//delete chatting list
	delete[] chats;
	
}

bool addChat(string *_chatList, string _chat){	//chat = command
    int count = getChatCount(_chatList);
    _chatList[count] = _chat;
    return true;
}

int getChatCount(string *_chatList){
	for(int i=0; i<NUM_OF_CHAT; ++i){
		string s = _chatList[i];
		if(s.empty()==true){
			break;
		}
	}
	return i;
}

void printChat(string *_chatList){
	int count = getChatCount(_chatList);
	for(int i=0; i<count; ++i){
		cout<<i<<" "<<_chatList[i]<<endl;
	}
}


bool removeChat(string *_chatList, int _index){
    int count = getChatCount(_chatList);
    for (int i = 0; i < count; ++i) {
        if (i == _index) {
            for (;_index <count;++_index)
            _chatList[_index] = _chatList[_index + 1];
      }
   }
   return true;
} 
}
