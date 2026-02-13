#include "../include/stackPostScript.hpp"

/*
Write the implementation for the appropriate methods here
*/
const long double PI = 3.141592653589793238L;

StackPostScript::StackPostScript() {
    vctrstack.clear();
}

void StackPostScript::reverseStack() {
    if(is_empty()) {
        std::cout<<"Empty stack nothing to reverse"<<std::endl;
        return;
    }
    size_t n = vctrstack.size();
    for (size_t i = 0;i < n/2;i++) {
        long double temp=vctrstack[i];
        vctrstack[i]=vctrstack[n-1-i];
        vctrstack[n-1-i] =temp;
    }
}

void StackPostScript::push(long double item) {
    vctrstack.push_back(item);
}

long double StackPostScript::pop() {
    if(is_empty()) {
        std::cout<<"Empty stack nothing to pop"<<std::endl;
        return 0;
    }
    long double top = vctrstack.back();
    vctrstack.pop_back();
    return top;
}

long double StackPostScript::peek() {
    if(is_empty()) {
        std::cout<<"empty stack"<<std::endl;
        return 0;
    }
    return vctrstack.back();
}

long double StackPostScript::add() {
    if(vctrstack.size()<2) {
        std::cout<<"Size of the stack must be atleast 2 for addition"<<std::endl;
        return 0;
    }
    long double a = pop();
    long double b = pop();
    long double c = b+a;
    push(c);
    return c;
}

long double StackPostScript::subtract() {
    if(vctrstack.size()<2) {
        std::cout<<"Size of the stack must be atleast 2 for subtraction"<<std::endl;
        return 0;
    }
    long double a = pop();
    long double b = pop();
    long double c = b-a;
    push(c);
    return c;
}

long double StackPostScript::multiply() {
    if(vctrstack.size()<2) {
        std::cout<<"Size of the stack must be atleast 2 for multiplication"<<std::endl;
        return 0;
    }
    long double a = pop();
    long double b = pop();
    long double c = b*a;
    push(c);
    return c;
}

long double StackPostScript::divide() {
    if(vctrstack.size()<2) {
        std::cout<<"Size of the stack must be atleast 2 for division"<<std::endl;
        return 0;
    }
    long double a = pop();
    long double b = pop();
    if(a==0) {
        std::cout<<"division by 0 not possible"<< std::endl;
        push(b);
        push(a);
        return 0;
    }
    long double c = b/a;
    push(c);
    return c;
}

long double StackPostScript::sin() {
    if(is_empty()) {
        std::cout<<"Empty stack"<<std::endl;
        return 0;
    }
    long double a= pop();
    long double c = std::sin(a * PI / 180.0);
    push(c);
    return c;
}

long double StackPostScript::cos() {
    if(is_empty()) {
        std::cout<<"Empty stack"<<std::endl;
        return 0;
    }
    long double a= pop();
    long double c = std::cos(a * PI / 180.0);
    push(c);
    return c;
}

long double StackPostScript::atan() {
    if(vctrstack.size() < 2) {
        std::cout << "Size of the stack must be at least 2 for atan" << std::endl;
        return 0;
    }
    long double x = pop();  // denominator (second operand)
    long double y = pop();  // numerator (first operand)
    long double c = std::atan2(y, x) * 180.0 / PI;
    push(c);
    return c;
}

long double StackPostScript::mod() {
    if(vctrstack.size()<2) {
        std::cout<<"Size of the stack must be atleast 2 for mod"<<std::endl;
        return 0;
    }
    long double a = pop();
    long double b = pop();
    if(a==0) {
        std::cout<<"division by 0 not possible"<< std::endl;
        push(b);
        push(a);
        return 0;
    }
    long double c = std::fmod(b,a);
    push(c);
    return c;
}

long double StackPostScript::exp() {
    if(vctrstack.size()<2) {
        std::cout<<"Size of the stack must be atleast 2"<<std::endl;
        return 0;
    }
    long double a = pop();
    long double b = pop();
    long double c = std::pow(b,a);
    push(c);
    return c;
}

long double StackPostScript::sqrt() {
    if(is_empty()) {
        std::cout<<"Empty stack"<<std::endl;
        return 0;
    }
    long double a = pop();
    if (a<0) {
        std::cout<<"no square root of negative numbers" << std::endl;
        push(a);
        return 0;
    }
    long double c =std::sqrt(a);
    push(c);
    return c;
}

void StackPostScript::dup() {
    if(is_empty()) {
        std::cout<<"Empty stack"<<std::endl;
        return;
    }
    push(peek());
}

void StackPostScript::exch() {
    if(vctrstack.size()<2) {
        std::cout<<"Size of the stack must be atleast 2 to exchange"<<std::endl;
        return;
    }
    long double a = pop();
    long double b = pop();
    push(a);
    push(b);
}

void StackPostScript::roll(long double n, long double j) {
    int count= static_cast<int>(n);
    int times= static_cast<int>(j);
    if(count<= 0|| count >vctrstack.size()) {
        std::cout <<"Invalid roll operation"<< std::endl;
        return;
    }
    times = times%count;
    if(times<0) {
        times += count;
    }
    for(int t=0;t<times; t++) {
        long double top =vctrstack[vctrstack.size() - 1];
        for(int i = vctrstack.size()-1;i > vctrstack.size()-count; i--) {
            vctrstack[i] = vctrstack[i-1];
        }
        vctrstack[vctrstack.size()-count] = top;
    }
}