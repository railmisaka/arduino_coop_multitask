// ACM
// Created by railmisaka (railmisaka@gmail.com)

// Messages for tasks communication

// MessagesQueue have two queues
// In each step we read messages from previous step queue and write to current
// SwapQueue have to be called before step begin

#ifndef __MESSAGES_QUEUE_H__
#define __MESSAGES_QUEUE_H__

#include "CustomTypes.h"
#include "MessagesTypes.h"

class TaskDispatcher;

// message base class
class SimpleMessage
{
public:
	SimpleMessage( MESSAGE_INT );
	~SimpleMessage()
	{
		if( next ) {
			delete next;
		}
	}

	MESSAGE_INT Code()
	{
		return code;
	}

private:
	SimpleMessage *next;

	MESSAGE_INT code;
	byte *value;

	friend class MessagesQueue;
};

class MessagesQueue
{
public:
	static MessagesQueue* GetInstance();

	void PushMessageFront( SimpleMessage *m );
	void PushMessageBack( SimpleMessage *m );

	SimpleMessage* GetFirst()
	{
		return prevQueue;
	}

private:
	MessagesQueue();
	static MessagesQueue *instance;

	SimpleMessage *actualQueueBegin;	// current step queue
	SimpleMessage *actualQueueEnd;	// current step queue
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

	byte const* Value()
	{
		return value;
	}

private:
	byte *value;
};

#endif
