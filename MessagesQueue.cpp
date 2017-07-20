/**
    Created 11 July 2017
    DeltaTime.cpp
    MIT License

    @author railmisaka
    @version 0.11 7/20/17 
*/

#include "MessagesQueue.h"

// ========================================
// MESSAGE
// ========================================

Message::Message(MESSAGE_INT c, MessageDataBase *v)
: code(c), value(v), next(nullptr)
{}

Message::~Message()
{
  delete value;
  if(next)
    delete next;
}

// ========================================
// MESSAGES QUEUE
// ========================================

MessagesQueue* MessagesQueue::instance = nullptr;

MessagesQueue::MessagesQueue()
: actualQueueBegin(nullptr), actualQueueEnd(nullptr), prevQueue(nullptr)
{}

MessagesQueue* MessagesQueue::getInstance()
{
  if(!instance)
  {
    instance = new MessagesQueue();
  }

  return instance;
}

void MessagesQueue::PushMessageBack(Message *m)
{
  actualQueueEnd->next = m;
}

void MessagesQueue::PushMessageFront(Message *m)
{
  m->next = actualQueueBegin;
  actualQueueBegin = m;
}

Message* MessagesQueue::getFirst()
{
  return prevQueue;
}

void MessagesQueue::SwapQueue()
{
  delete prevQueue;
  prevQueue = actualQueueBegin;
  actualQueueBegin = actualQueueEnd = nullptr;
}

