#include <iostream>
#include <string>
#include <stdio.h>

#include "minimal_fighter.h"

MinimalFighter::MinimalFighter (){
	mHp = 0, mPower =0, mStatus = Invalid;
}

MinimalFighter::MinimalFighter(int _hp, int _power){
	this -> mHp = _hp;
	this -> mPower = _power;

	if(_hp <= 0){		
		mStatus = Dead;
}
	else 
		mStatus = Alive;
 }
 
int MinimalFighter::hp() const{
	return mHp;
}

int MinimalFighter::power() const{
	return mPower;
}

FighterStatus MinimalFighter::status() const{
	if(this -> mHp <= 0){
		return Dead;
	}
	else
		return Alive;
}
void MinimalFighter::setHp(int _hp){
	this -> mHp = _hp;
}
void MinimalFighter::hit(MinimalFighter* _enemy){
	_enemy->mHp -= this -> mPower;
	this -> mHp -= _enemy->mPower;
}

void MinimalFighter::attack(MinimalFighter* _target){
	_target->mHp -= this->mPower;
	this -> mPower = 0;
}

void MinimalFighter::fight(MinimalFighter* _enemy){
	while(_enemy->mHp > 0 || this->mHp > 0){
	_enemy -> mHp -= this->mPower;
	this->mHp -= _enemy -> mPower;
		if(_enemy->mHp <= 0 || this->mHp <= 0)
			break;
	}
}
