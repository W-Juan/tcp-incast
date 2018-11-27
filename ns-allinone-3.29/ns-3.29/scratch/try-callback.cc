#include<iostream>
#include"ns3/core-module.h"
using namespace ns3;
NS_LOG_COMPONENT_DEFINE("TryCallback");
// definition of class Complex
class Complex{
   public:
	   Complex(int a,int b);
	   Complex add(Complex & another);
	   friend std::ostream & operator <<(std::ostream & out, Complex & c);
   private:
	   int m_a;
	   int m_b;
};
//the function of Complex
Complex::Complex(int a,int b){
   m_a=a;
   m_b=b;
}
Complex Complex::add(Complex & another){
   int a=m_a+another.m_a;
   int b=m_b+another.m_b;
   return Complex(a,b);
}
std::ostream & operator <<(std::ostream & out, Complex & c){
   out<<c.m_a<<"+"<<c.m_b<<"i";
   return out;
}
//definition of class A
class A{
   public:
	   A();
	   A(Callback<int,int> calculator);
	   A(Callback<Complex,Complex &> complexCalculator);
	   
	   void calculate();
	   void complexCalculate(Complex b);
   private:
	   Callback<int,int> m_calculator;
	   Callback<Complex,Complex &> m_complexCalculator;
};
A::A(){};
A::A(Callback<int,int> calculator){
	m_calculator=calculator;
}
A::A(Callback<Complex,Complex &> complexCalculator){
	m_complexCalculator=complexCalculator;
}
void A::calculate(){
   if(m_calculator.IsNull()){
  	NS_LOG_UNCOND("callback is not bind to any function."); 
   }else{
	int result=m_calculator(6);
   	NS_LOG_UNCOND(result);
   }
}
void A::complexCalculate(Complex b){
   Complex result=m_complexCalculator(b);
   std::cout<<result<<std::endl;
}
int add(int a,int b){
   return a+b;
}
int main(int argc,char *argv[]){
   Complex first(1,3);
   Complex second(2,5);

   //A one(MakeCallback(&add));
   
   A one(MakeBoundCallback(&add,8));
   one.calculate();

   A two;
   two.calculate();
   
//   A two(MakeCallback(&Complex::add,&first));
//   two.complexCalculate(second);
}
