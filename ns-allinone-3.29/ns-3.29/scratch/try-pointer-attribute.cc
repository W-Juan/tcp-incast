/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <iostream>
#include <fstream>
#include <string>

#include "ns3/core-module.h"

using namespace std;
using namespace ns3;

namespace ns3 {		//一般建议将所有对象都写在ns3名称空间中

  NS_LOG_COMPONENT_DEFINE ("MyObject");		//定义一个日志组件

  //=================MyAnotherObject=================
  class MyAnotherObject : public Object 
  {
    public:
	static TypeId GetTypeId ();		//必须实现此方法

	MyAnotherObject();		
	virtual ~MyAnotherObject();

	void SetValue(int value)
	{
	   m_value = value;
	}

	uint32_t GetValue()
	{
	   return m_value;
        }

	private:
		uint32_t m_value;
};

NS_OBJECT_ENSURE_REGISTERED (MyAnotherObject);		//不要忘记调用

TypeId MyAnotherObject::GetTypeId ()
{
    static TypeId tid = TypeId("ns3::MyAnotherObject")		//创建TypeId，
			.SetParent(Object::GetTypeId())
			.SetGroupName("MyExample")
			.AddConstructor<MyAnotherObject>()
		        .AddAttribute ("myValue", "help text",
                  		       UintegerValue (0),
                     		       MakeUintegerAccessor (&MyAnotherObject::m_value),
                     		       MakeUintegerChecker<uint32_t> ())
			;
		return tid;
	}

MyAnotherObject::MyAnotherObject ()
{
	NS_LOG_FUNCTION(this);
}
MyAnotherObject::~MyAnotherObject ()
{
	NS_LOG_FUNCTION(this);
}

	//================MyObject==================
 class MyObject : public Object	//继承自SimpleRefCount，又继承自ObjectBase
 {
  public:
    static TypeId GetTypeId ();				//必须实现此方法

    MyObject ();
    virtual ~MyObject();

    //业务方法
    virtual void MyMethod();

    void SetObj(Ptr<MyAnotherObject> object) 
    {
    	m_object = object;
    }

    Ptr<MyAnotherObject> GetObj() 
    {
    	return m_object;
    }

  private:
    Ptr<MyAnotherObject> m_object;
  };

  NS_OBJECT_ENSURE_REGISTERED (MyObject);		//不要忘记调用

  TypeId
  MyObject::GetTypeId ()
  {
      static TypeId tid = TypeId("ns3::MyObject")		//创建TypeId，
  		.SetParent(Object::GetTypeId())
      		.SetGroupName("MyExample")
      		.AddConstructor<MyObject>()
     		.AddAttribute ("myObject", 
				"help text",
				 PointerValue(0),
              			 MakePointerAccessor (&MyObject::m_object),
	                         MakePointerChecker <MyAnotherObject>());
  	return tid;
  }

  MyObject::MyObject ()
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

Ptr<const AttributeChecker> getCheckerByName(TypeId typeId, std::string attributeName)
{
    TypeId::AttributeInformation * info = new TypeId::AttributeInformation();
    typeId.LookupAttributeByName(attributeName, info);
    Ptr<const AttributeChecker> checker = info->checker;
    delete info;
    return checker;
}

int main (int argc, char *argv[])
{
   LogComponentEnable("MyObject", LOG_LEVEL_LOGIC);
   Ptr<MyAnotherObject> aObj = CreateObject<MyAnotherObject>();
   aObj->SetAttribute("myValue", StringValue("5"));

   Ptr<MyObject> obj = CreateObject<MyObject>(); 
   obj->SetAttribute("myObject", PointerValue(aObj));

   PointerValue pointerValue;
   obj->GetAttribute("myObject", pointerValue);

   Ptr<MyAnotherObject> aObj2 = pointerValue.Get<MyAnotherObject>();	
   UintegerValue myValue;
   aObj2->GetAttribute("myValue", myValue);
   uint32_t value = myValue.Get();

   NS_LOG_UNCOND(value);
}
