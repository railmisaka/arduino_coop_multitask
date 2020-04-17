// ACM
// Created by railmisaka (railmisaka@gmail.com)

#include "Messages.h"

MessagesQueue* MessagesQueue::instance = nullptr;

SimpleMessage::SimpleMessage( MESSAGE_INT c ) :
	next( nullptr ), code( c )
{}

CustomMessage::CustomMessage( MESSAGE_INT c, byte *v ) :
	SimpleMessage( c ), value( v )
{}

MessagesQueue::MessagesQueue() :
	actualQueueBegin( nullptr ), actualQueueEnd( nullptr ), prevQueue( nullptr )
{}

MessagesQueue* MessagesQueue::GetInstance()
{
	if( !instance ) {
		instance = new MessagesQueue();
	}
	return instance;
}

void MessagesQueue::PushMessageFront( SimpleMessage *m )
{
	m->next = actualQueueBegin;
	if( !actualQueueBegin ) {
		actualQueueEnd = m;
	}
	actualQueueBegin = m;
}

void MessagesQueue::PushMessageBack( SimpleMessage *m )
{
	m->next = nullptr;

	if( actualQueueEnd ) {
		actualQueueEnd->next = m;
	} else {
		actualQueueEnd = m;
		actualQueueBegin = m;
	}
}

void MessagesQueue::SwapQueue()
{
	delete prevQueue;
	prevQueue = actualQueueBegin;
	actualQueueBegin = actualQueueEnd = nullptr;
}
