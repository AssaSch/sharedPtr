#ifndef __COUNTER_H__
#define __COUNTER_H__

#include <stddef.h>	// size_t

class Counter
{
public:
    //~Counter();   provided by compiler																							
	Counter();							
    Counter(const Counter& _counter);								
	Counter& operator=(const Counter& _counter);
	
	void Increment();
	void Decrement();
	size_t GetCount() const;
	
private:
    size_t m_counter;
};

inline Counter::Counter()
:   m_counter(1)
{ 
   
}

inline Counter::Counter(const Counter& _counter)
:    m_counter(_counter.m_counter)
{

}

inline Counter& Counter::operator=(const Counter& _counter)
{
    m_counter = _counter.m_counter;
    return *this;
}

inline void Counter::Increment()
{
    ++m_counter;
}

inline void Counter::Decrement()
{
    --m_counter;
}

inline size_t Counter::GetCount() const
{
    return m_counter;
}

#endif /* __COUNTER_H__ */
