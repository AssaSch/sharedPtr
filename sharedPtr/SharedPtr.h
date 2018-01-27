#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

#include <stddef.h>	// size_t 
#include "Counter.h"
#include <exception>

/*************************************************/
template<class T>
class SharedPtr
{
public:
    ~SharedPtr();																							
	explicit SharedPtr(T* _ptr = 0);							
    SharedPtr(const SharedPtr& _sharedPtr);								
	SharedPtr& operator=(const SharedPtr& _sharedPtr);
				
	bool operator==(const SharedPtr& _sharedPtr) const;
	bool operator!=(const SharedPtr& _sharedPtr) const;			    	
	
	T& operator*() const;
	T* operator->() const;
	
	T* GetRawPtr() const;
	size_t GetCount() const;

	template<class Q> friend class SharedPtr;
	
	template<class Q>
	SharedPtr& operator=(const SharedPtr<Q>& _sharedPtr);
	
private:
    void DecAndDeleteIfNeeded();
    
    T* m_ptr;
    Counter* m_ptrCounter;
};

/*************************************************/
template<class T>
template<class Q>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<Q>& _sharedPtr)
{
	if (this != (SharedPtr<T>*)&_sharedPtr)
    {
        DecAndDeleteIfNeeded();
        m_ptr = _sharedPtr.m_ptr;
        m_ptrCounter = _sharedPtr.m_ptrCounter;
        m_ptrCounter->Increment();
    }
    
    return *this;
}

/*------------Ctor-------------------*/
template<class T>
SharedPtr<T>::SharedPtr(T* _ptr)
:   m_ptr(_ptr)
{ 
   try
   {
        m_ptrCounter= new Counter;
   }
   catch (std::bad_alloc& ex)
   {
        delete _ptr;
        throw;
   }
}

/*------------Dtor-------------------*/
template<class T>
SharedPtr<T>::~SharedPtr()
{
   DecAndDeleteIfNeeded();
}

/*------------DecAndDeleteIfNeeded-------------------*/
template<class T>
void SharedPtr<T>::DecAndDeleteIfNeeded()
{
   m_ptrCounter->Decrement();
   if (!GetCount())
   {
        delete m_ptr;
        delete m_ptrCounter;
        m_ptr = 0;
   }
}

/*------------CopyCtor-------------------*/
template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr& _sharedPtr)
:  m_ptr(_sharedPtr.m_ptr)
,  m_ptrCounter(_sharedPtr.m_ptrCounter)  
{ 
    m_ptrCounter->Increment();
}

/*------------operator=-------------------*/
template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& _sharedPtr)
{
    if (this != &_sharedPtr)
    {
        DecAndDeleteIfNeeded();
        m_ptr = _sharedPtr.m_ptr;
        m_ptrCounter = _sharedPtr.m_ptrCounter;
        m_ptrCounter->Increment();
    }
    
    return *this;
}

/*------------operator==-------------------*/
template<class T>
bool SharedPtr<T>::operator==(const SharedPtr<T>& _sharedPtr) const
{
    return (m_ptr == _sharedPtr.m_ptr);  
}

/*------------operator!=-------------------*/
template<class T>
bool SharedPtr<T>::operator!=(const SharedPtr<T>& _sharedPtr) const
{
    return (m_ptr != _sharedPtr.m_ptr);  
}

/*------------operator*-------------------*/
template<class T>
T& SharedPtr<T>::operator*() const
{
    return *m_ptr;
}

/*------------operator->-------------------*/
template<class T>
T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}

/*------------GetRawPtr-------------------*/
template<class T>
T* SharedPtr<T>::GetRawPtr() const
{
    return m_ptr;
}

/*------------GetCount-------------------*/
template<class T>
size_t  SharedPtr<T>::GetCount() const
{
    return m_ptrCounter->GetCount();
}

/*************************************************/

#endif /* __SHARED_PTR_H__ */

