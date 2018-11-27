/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <iostream>
#include <fstream>
#include <string>

#include "ns3/core-module.h"

using namespace std;
using namespace ns3;

namespace ns3 {		//一般建议将所有对象都写在ns3名称空间中

  class MyObject : public ObjectBase	//继承自ObjectBase
  {
  public:
    static TypeId GetTypeId ();				//必须实现此方法

    MyObject ();
    virtual ~MyObject();

    virtual TypeId GetInstanceTypeId () const;	//必须实现此方法

    //业务方法
    virtual void MyMethod();
  };

  NS_LOG_COMPONENT_DEFINE ("MyObject");			//定义一个日志组件
  NS_OBJECT_ENSURE_REGISTERED (MyObject);		//不要忘记调用

  TypeId
  MyObject::GetTypeId ()
  {
  	static TypeId tid = TypeId("ns3::MyObject")		//创建TypeId，
  		.SetParent(ObjectBase::GetTypeId())
      .SetGroupName("MyExample")
      .AddConstructor<MyObject>();
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

  TypeId
  MyObject::GetInstanceTypeId () const
  {
  	return MyObject::GetTypeId();
  }

	void
	MyObject::MyMethod ()
	{
		NS_LOG_FUNCTION(this);

		NS_LOG_UNCOND("my method is executed");
	}

	class MyObject2 : public MyObject {
		public:
  		 	 static TypeId GetTypeId ();
   			 virtual void MyMethod();
	};

	  NS_OBJECT_ENSURE_REGISTERED (MyObject2);

 	 TypeId MyObject2::GetTypeId ()
 	 {
  		static TypeId tid = TypeId("ns3::MyObject2")
  			.SetParent(MyObject::GetTypeId())
  			.SetGroupName("MyExample")
  			.AddConstructor<MyObject2>();
  		return tid;
 	 }

   void
  MyObject2::MyMethod ()
  {
	  NS_LOG_FUNCTION(this);
          NS_LOG_UNCOND("in MyObject2");
  }

  class MyObject3 : public MyObject {
	public:
	    static TypeId GetTypeId ();
    	    virtual void MyMethod();
};

  NS_OBJECT_ENSURE_REGISTERED (MyObject3);

  TypeId
  MyObject3::GetTypeId ()
  {
  	static TypeId tid = TypeId("ns3::MyObject3")
  			.SetParent(MyObject::GetTypeId())
  			.SetGroupName("MyExample")
			.AddConstructor<MyObject3>();
  	return tid;
  }

   void MyObject3::MyMethod ()
  {
    NS_LOG_FUNCTION(this);

    NS_LOG_UNCOND("in MyObject3");
  }
}

int
main (int argc, char *argv[])
{
	LogComponentEnable("MyObject", LOG_LEVEL_LOGIC);

  ifstream infile("MyObjectConfig.ini");
  std::string line;
  getline(infile, line);
  if(!line.empty()) {
    NS_LOG_INFO("config from file is " << line);
    TypeId tid = TypeId::LookupByName(line);
    MyObject * obj = dynamic_cast<MyObject *>(tid.GetConstructor()());
    obj->MyMethod();
    delete obj;
    obj = 0;
  }
}
