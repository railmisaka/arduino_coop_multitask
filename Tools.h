// ACM
// Created by railmisaka (railmisaka@gmail.com)

#ifndef __TOOLS_H__
#define __TOOLS_H__

template<typename T> class ConstIterator;
template<typename T> class Iterator;

template<typename T>
class Iterable
{
public:
	Iterable();
	~Iterable()
	{
		if( next ) {
			delete next;
		}
	}

	Iterator<T> CreateIterator()
	{
		return Iterator<T>( static_cast<T*>( this ) );
	}

	ConstIterator<T> CreateConstIterator()
	{
		return ConstIterator<T>( static_cast<T*>( this ) );
	}

protected:
	T* next;

	friend class ConstIterator<T>;
	friend class Iterator<T>;
};

template<typename T>
class ConstIterator
{
public:
	const T* Next();
	const T* Value()
	{
		return current;
	}

private:
	ConstIterator( const T* );

	const T* prev;
	const T* current;

	friend class Iterable<T>;
};

template<typename T>
class Iterator
{
public:
	T* Next();
	T* Value()
	{
		return current;
	}

	void Remove();

private:
	Iterator( T* );

	T* prev;
	T* current;

	friend class Iterable<T>;
};

template<typename T>
Iterable<T>::Iterable() :
	next( nullptr )
{}

template<typename T>
ConstIterator<T>::ConstIterator( const T* obj ) :
	prev( nullptr ), current( obj )
{}

template<typename T>
const T* ConstIterator<T>::Next()
{
	prev = current;

	if( current ) {
		current = current->next;
	}

	return current;
}

template<typename T>
Iterator<T>::Iterator( T* obj ) :
	prev( nullptr ), current( obj )
{}

template<typename T>
T* Iterator<T>::Next()
{
	prev = current;

	if( current ) {
		current = current->next;
	}

	return current;
}

template<typename T>
void Iterator<T>::Remove()
{
	if( current ) {
		prev = current->next;
		delete current;
		current = prev;
	}
}

#endif
