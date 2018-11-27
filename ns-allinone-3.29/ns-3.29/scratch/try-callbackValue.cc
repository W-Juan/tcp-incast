#include<iostream>
#include "ns3/core-module.h"
using namespace ns3;
NS_LOG_COMPONENT_DEFINE("TryCallbackValue");
namespace ns3{
   class A:public Object{
      public:
	      static TypeId GetTypeId(void);
	      A();
	      void calculate();
	      void setCalculator(const Callback<int,int,int>& calculator){
	        m_calculator=calculator;
	      }
      private:
	      Callback<int,int,int> m_calculator;
   };
   A::A(){}
   TypeId A::GetTypeId(void){
	   static TypeId tid=TypeId("ns3::A").AddConstructor<A>()
		      				.SetParent<Object>()
						.AddAttribute("calculator",
							      "help text",
							      CallbackValue(),
							      MakeCallbackAccessor(&A::m_calculator),
							      MakeCallbackChecker());
	   return tid;	
   }
   void A::calculate(){
      if(m_calculator.IsNull()){
         NS_LOG_UNCOND("callback is bind to no function");
      }else{
         int result=m_calculator(3,5);
	 NS_LOG_UNCOND(result);
      }
   }
   int add(int a,int b){
      return a+b;
   }
} 
   //main afunction
   int main(int argc,char * argv[]){
    //  LogComponentEnable("TyrCallbackValue",NS_LOG_LOGIC);
      Ptr<A> a=CreateObject<A>();
      a->SetAttribute("calculator",CallbackValue(MakeCallback(&add)));
      a->calculate();
   }
