//
//  RHObject.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHObject__
#define __TinyRPG__RHObject__

namespace flownet
{

class RHObject
{
private:
    mutable STRING m_ObjectName;
    
public:
    RHObject(const STRING objectName="RHObject");
    virtual ~RHObject();

    const RHObject& operator=(const RHObject& rhs) { /*m_ObjectName = rhs;*/ return *this;}
public:
    inline const STRING& GetObjectName() const { return m_ObjectName; }
};


template<class RHObjectClass>
RHObjectClass* CreateRHObject()
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass();
}

template<class RHObjectClass, class ArgType1>
RHObjectClass* CreateRHObject(const ArgType1& arg1)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1);
}

template<class RHObjectClass, class ArgType1, class ArgType2>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9, class ArgType10>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9, const ArgType10& arg10)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9, class ArgType10, class ArgType11>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9, const ArgType10& arg10, const ArgType11& arg11)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9, class ArgType10, class ArgType11, class ArgType12>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9, const ArgType10& arg10, const ArgType11& arg11, const ArgType12& arg12)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9, class ArgType10, class ArgType11, class ArgType12, class ArgType13>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9, const ArgType10& arg10, const ArgType11& arg11, const ArgType12& arg12, const ArgType13& arg13)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
}


template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9, class ArgType10, class ArgType11, class ArgType12, class ArgType13, class ArgType14>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9, const ArgType10& arg10, const ArgType11& arg11, const ArgType12& arg12, const ArgType13& arg13, const ArgType14& arg14)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9, class ArgType10, class ArgType11, class ArgType12, class ArgType13, class ArgType14, class ArgType15>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9, const ArgType10& arg10, const ArgType11& arg11, const ArgType12& arg12, const ArgType13& arg13, const ArgType14& arg14, const ArgType15& arg15)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9, class ArgType10, class ArgType11, class ArgType12, class ArgType13, class ArgType14, class ArgType15, class ArgType16>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9, const ArgType10& arg10, const ArgType11& arg11, const ArgType12& arg12, const ArgType13& arg13, const ArgType14& arg14, const ArgType15& arg15, const ArgType16& arg16)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9, class ArgType10, class ArgType11, class ArgType12, class ArgType13, class ArgType14, class ArgType15, class ArgType16, class ArgType17>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9, const ArgType10& arg10, const ArgType11& arg11, const ArgType12& arg12, const ArgType13& arg13, const ArgType14& arg14, const ArgType15& arg15, const ArgType16& arg16, const ArgType17& arg17)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9, class ArgType10, class ArgType11, class ArgType12, class ArgType13, class ArgType14, class ArgType15, class ArgType16, class ArgType17, class ArgType18>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9, const ArgType10& arg10, const ArgType11& arg11, const ArgType12& arg12, const ArgType13& arg13, const ArgType14& arg14, const ArgType15& arg15, const ArgType16& arg16, const ArgType17& arg17, const ArgType18& arg18)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18);
}

template<class RHObjectClass, class ArgType1, class ArgType2, class ArgType3, class ArgType4, class ArgType5, class ArgType6, class ArgType7, class ArgType8, class ArgType9, class ArgType10, class ArgType11, class ArgType12, class ArgType13, class ArgType14, class ArgType15, class ArgType16, class ArgType17, class ArgType18, class ArgType19>
RHObjectClass* CreateRHObject(const ArgType1& arg1, const ArgType2& arg2, const ArgType3& arg3, const ArgType4& arg4, const ArgType5& arg5, const ArgType6& arg6, const ArgType7& arg7, const ArgType8& arg8, const ArgType9& arg9, const ArgType10& arg10, const ArgType11& arg11, const ArgType12& arg12, const ArgType13& arg13, const ArgType14& arg14, const ArgType15& arg15, const ArgType16& arg16, const ArgType17& arg17, const ArgType18& arg18, const ArgType19& arg19)
{
    // To Do : memory pool, object counting ...
    return new RHObjectClass(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19);
}



} // namsespace flownet


#endif /* defined(__TinyRPG__RHObject__) */
