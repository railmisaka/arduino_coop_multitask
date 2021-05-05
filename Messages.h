// ACM
// Created by railmisaka (railmisaka@gmail.com)

// Messages for tasks communication

// MessagesQueue have two queues
// In each step we read messages from previous step queue and write to current
// SwapQueue have to be called before step begin

#ifndef __MESSAGES_H__
#define __MESSAGES_H__

// for visual studio
#pragma warning( error : 4369 )

#include "Common.h"
#include "Tools.h"

// Messages enum base type
#ifndef LONG_MESSAGES
	typedef byte MESSAGE_INT;
#else
	typedef word MESSAGE_INT;
#endif

// Messages enum
#define MESSAGES_LIST enum MESSAGE : MESSAGE_INT {
#define MESSAGES_LIST_END DECLARE_MESSAGE( MESSAGES_TYPES_COUNT ) };
#define DECLARE_MESSAGE( _MESSAGE ) _MESSAGE,
#include "MessagesConfiguration.h"
#undef MESSAGES_LIST
#undef MESSAGES_LIST_END
#undef DECLARE_MESSAGE

// Check messages count
#ifndef LONG_MESSAGES
#else
#endif

// Helpers
#define FOREACH_MESSAGES( a ) \
	for( ConstIterator<SimpleMessage> iter = MessagesQueue::GetInstance()->GetConstIterator(); iter.Value(); iter.Next() ) { \
		const SimpleMessage* a = iter.Value();
#define FOREACH_END }

#define ADD_SIMPLE_MESSAGE( CODE ) MessagesQueue::GetInstance()->PushMessageBack( new SimpleMessage( CODE ) );

// Messages and Queue

// Message base class
class SimpleMessage : public Iterable<SimpleMessage>
{
public:
	SimpleMessage( MESSAGE_INT );

	MESSAGE_INT Code() const
	{
		return code;
	}

private:
	MESSAGE_INT code;

	friend class MessagesQueue;
};

class CustomMessage : public SimpleMessage
{
public:
	CustomMessage( MESSAGE_INT, byte* );
	~CustomMessage()
	{
		if( value ) {
			delete value;
		}
	}

	const byte* Value()
	{
		return value;
	}

private:
	byte *value;
};

class TaskDispatcher;

class MessagesQueue
{
public:
	static MessagesQueue* GetInstance();

	void PushMessageFront( SimpleMessage *m );
	void PushMessageBack( SimpleMessage *m );

	Iterator<SimpleMessage> GetIterator()
	{
		return prevQueue->CreateIterator();
	}

	ConstIterator<SimpleMessage> GetConstIterator()
	{
		return prevQueue->CreateConstIterator();
	}

private:
	MessagesQueue();
	static MessagesQueue *instance;

	SimpleMessage *actualQueueBegin;	// current step queue
	SimpleMessage *actualQueueEnd;		// current step queue
	SimpleMessage *prevQueue;			// prev step queue (for swap)

	void SwapQueue();

	friend class TaskDispatcher;
};

#endif
