/**
    Created 11 July 2017
    MessagesQueue.h
    MIT License

    @author railmisaka
    @version 0.11 7/20/17 
*/

#ifndef __MESSAGES_QUEUE_H__
#define __MESSAGES_QUEUE_H__

#include "CustomTypes.h"
#include "MessageDataBase.h"

class MessagesQueue;  // forward

class Message
{
  friend class MessagesQueue;
  
public:
  Message(MESSAGE_INT c, MessageDataBase *v);
  ~Message();

  const MESSAGE_INT code;
  const MessageDataBase *value;
  
private:
  Message *next;  // list element
  
};


class TaskDispatcher; // forward

class MessagesQueue
{
friend class TaskDispatcher;

private:
  MessagesQueue();
  Message *actualQueueBegin;  // current step queue
  Message *actualQueueEnd;    // current step queue
  Message *prevQueue;         // prev step queue

  static MessagesQueue *instance;

public:
  // singlethon
  static MessagesQueue* getInstance();

public:
  void PushMessageBack(Message *m);
  void PushMessageFront(Message *m);
  Message *getFirst();

private:
  void SwapQueue();
};

#endif

