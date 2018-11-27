/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <iostream>
#include <fstream>
#include <string>

#include "ns3/core-module.h"

using namespace std;
using namespace ns3;

namespace ns3 {		//一般建议将所有对象都写在ns3名称空间中

  NS_LOG_COMPONENT_DEFINE ("MyObject");		//定义一个日志组件
  class MyObject : public Object//继承自SimpleRefCount，又继承自ObjectBase
  {
  //
  public:
    static TypeId GetTypeId ();		//必须实现此方法

    MyObject ();
    virtual ~MyObject();

    //业务方法
    virtual void MyMethod();

    uint32_t GetMyValue () const
    {
	NS_LOG_FUNCTION(this);
	return m_myValue;
    }

    void SetMyValue (uint32_t myValue)
    {
       NS_LOG_FUNCTION(this);
       m_myValue = myValue; 	
    }
    bool GetMyBoolValue() const
    {
	NS_LOG_FUNCTION(this);
	return m_myBoolValue;
    }
    void SetMyBoolValue(bool myBoolValue)
    {
	NS_LOG_FUNCTION(this);
	m_myBoolValue=myBoolValue;
    }

   private:
    uint32_t m_myValue;
    bool m_myBoolValue;
	   
   };

  NS_OBJECT_ENSURE_REGISTERED (MyObject);	//不要忘记调用

  TypeId MyObject::GetTypeId ()
  {
      static TypeId tid = TypeId("ns3::MyObject")	//创建TypeId，
  		.SetParent(Object::GetTypeId())
                .SetGroupName("MyExample")
      		.AddConstructor<MyObject>()
		.AddAttribute("MyValue",
			      "an example attribute",
			      TypeId::ATTR_SGC,
			      UintegerValue(100),
			      MakeUintegerAccessor(&MyObject::m_myValue),
			      MakeUintegerChecker<uint32_t>())
		.AddAttribute("MyBoolValue",
			      "an example for BoolValue",
			      BooleanValue(false),
			      MakeBooleanAccessor(&MyObject::GetMyBoolValue,&MyObject::SetMyBoolValue),
			      MakeBooleanChecker());
	      			
      return tid;
  }

  MyObject::MyObject (): m_myValue(0)
  {
  	NS_LOG_FUNCTION(this);
  }

  MyObject::~MyObject ()
  {
  	NS_LOG_FUNCTION(this);
  }

  void MyObject::MyMethod ()	
  {
	NS_LOG_FUNCTION(this);

	NS_LOG_UNCOND("my method is executed");
  }
}
  int main(int argc,char* argv[])
  {
	LogComponentEnable("MyObject",LOG_LEVEL_LOGIC);
	
	//Ptr<MyObject> obj=CreateObjectWithAttributes<MyObject>("MyValue",UintegerValue(250));

	Config::SetDefault("ns3::MyObject::MyValue",UintegerValue(888));
	
	Ptr<MyObject> obj1=CreateObject<MyObject>();
	
	//Ptr<MyObject> obj2=CreateObject<MyObject>();
        UintegerValue myValue;
	BooleanValue myBoolValue;	
	
	obj1->SetAttribute("MyValue",UintegerValue(999));
	obj1->GetAttribute("MyValue",myValue);
	NS_LOG_UNCOND(myValue.Get());

	obj1->SetAttribute("MyBoolValue",StringValue("t"));
	obj1->GetAttribute("MyBoolValue",myBoolValue);
	NS_LOG_UNCOND(myBoolValue.Get());

	DoubleValue value(5.5);
	StringValue str(value.SerializeToString(MakeStringChecker()));
	NS_LOG_UNCOND(str.Get());
	return 0;
  }

