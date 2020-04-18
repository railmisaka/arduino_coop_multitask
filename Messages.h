// ACM
// Created by railmisaka (railmisaka@gmail.com)

// Messages for tasks communication

// MessagesQueue have two queues
// In each step we read messages from previous step queue and write to current
// SwapQueue have to be called before step begin

#ifndef __MESSAGES_QUEUE_H__
#define __MESSAGES_QUEUE_H__

#include "CustomTypes.h"
#include "Tools.h"

// Messages enum
#define MESSAGES_LIST enum MESSAGES_TYPES {
#define MESSAGES_LIST_END };
#define DECLARE_MESSAGE( MESSAGE ) MESSAGE,

#include "MessagesTypes.h"

#undef MESSAGES_LIST
#undef MESSAGES_LIST_END
#undef DECLARE_MESSAGE

// Check messages count
#ifndef LONG_MESSAGES
	#if MESSAGES_TYPES_COUNT > 255
		#error Too many messages in MESSAGES_TYPES
	#endif
#else
	#if MESSAGES_TYPES_COUNT > 65535
		#error Too many messages in MESSAGES_TYPES
	#endif
#endif

// Helpers
#define FOREACH_MESSAGES( a ) \
	for( ConstIterator<SimpleMessage> iter = MessagesQueue::GetInstance()->GetConstIterator(); iter.Value(); iter.Next() ) {\
		const SimpleMessage *a = iter.Value();

#define FOREACH_END }

#define ADD_SIMPLE_MESSAGE( CODE ) MessagesQueue::GetInstance()->PushMessageBack( new SimpleMessage( CODE ) );

// Messages and Queue

class TaskDispatcher;

// message base class
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

#endif
