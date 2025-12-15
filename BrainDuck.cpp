#include "BrainDuck.h"
int IncrementInstruction::execute(std::istream &ss, BrainDuckVM &vm) {
    // Your code here
    char tem=vm.getCurrentTape();
    tem++;
    vm.setCurrentTape(tem);
    return 1;
}

int DecrementInstruction::execute(std::istream &ss, BrainDuckVM &vm) {
    // Your code here
    char tem=vm.getCurrentTape();
    tem--;
    vm.setCurrentTape(tem);
    return 1;
}

int MoveLeftInstruction::execute(std::istream &ss, BrainDuckVM &vm) {
    // Your code here
    vm.decreaseTapeIndex();
    return 1;
}

int MoveRightInstruction::execute(std::istream &ss, BrainDuckVM &vm) {
    // Your code here
    vm.increaseTapeIndex();
    return 1;
}

int LoopBeginInstruction::execute(std::istream &ss, BrainDuckVM &vm) {
    // Your code here
    char c=vm.getCurrentTape();
    if(c==0){
        int lc=0,rc=0;
        std::string command=vm.getProgram();
        int now=vm.getProgramCount();
        for(int i=now+1;true;i++){
            if(command[i]=='[') lc++;
            else if(command[i]==']'){
                if(lc==rc){
                    return i-now+1;
                }
                else{
                    rc++;
                }
            }
        }
    }
    else{
        return 1;
    }
}

int LoopEndInstruction::execute(std::istream &ss, BrainDuckVM &vm) {
    // Your code here
    char c=vm.getCurrentTape();
    if(c!=0){
        int lc=0,rc=0;
        std::string command=vm.getProgram();
        int now=vm.getProgramCount();
        for(int i=now-1;true;i--){
            if(command[i]==']') rc++;
            else if(command[i]=='['){
                if(lc==rc){
                    return i-now+1;
                }
                else{
                    lc++;
                }
            }
        }
    }
    else{
        return 1;
    }
}

int InputInstruction::execute(std::istream &ss, BrainDuckVM &vm) {
    // Your code here
    char input;
    ss >> input;
    vm.setCurrentTape(input);
    return 1;
}

int OutputInstruction::execute(std::istream &ss, BrainDuckVM &vm) {
    // Your code here
    std::cout << vm.getCurrentTape();
    return 1;
}