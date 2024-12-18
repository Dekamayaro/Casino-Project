#include "../headers/player.h"
#include <iostream>
#include <stdexcept>

const double Player::getLuck() const
{
    return luck;
}

const string Player::getName() const
{
    return name;
}

void Player::setLuck(double newLuck)
{
    luck = newLuck;
}

void Player::setName(string newName)
{
    name = newName;
}

const double Player::getWallet() const
{
    return wallet;
}

void Player::setWallet(double newWallet)
{
    wallet = newWallet;
}

void Player::purchase(double amount) {
    wallet -= amount;
    std::cout << "New balance of: " << wallet << std::endl;
}

void Player::applyBuff(double buff){
    if (buff < 0){
        buff *= -1;
    }
    if(buff > 2){
        throw std::runtime_error("Enter the buff in decimal form");
    }
    
    luck += buff;
    //caps luck at 200%
    if (luck > 2){
        luck = 2;
    }
}

void Player::applyDebuff(double debuff) {
    if (debuff < 0){
        debuff *= -1;
    }
    if(debuff > 2){
        throw std::runtime_error("Enter the debuff in decimal form");
    }

    luck -= debuff;
    if (luck < 0){
        luck = 0;
    }
}

void Player::changeWallet(double amount) {
    wallet += amount;
    
    if(wallet < 0){
        wallet = 0;
    }
}