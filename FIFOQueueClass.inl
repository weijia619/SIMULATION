#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
using namespace std;

//Weijia Chen
//12/03/2019
//FIFOQueueClass

template< class T >
FIFOQueueClass< T >::FIFOQueueClass()
{
  head = NULL;
  tail = NULL;
}

template< class T >
FIFOQueueClass< T >::~FIFOQueueClass()
{
  this->clear();
}

template< class T >
void FIFOQueueClass< T >::enqueue(
  const T& newItem)
{
  //if the queue is empty
  if (!head)
  {
    LinkedNodeClass< T >*newNode =
      new LinkedNodeClass< T >(NULL, newItem, NULL);
    head = newNode;
    tail = newNode;
  }
  else
  {
    LinkedNodeClass< T >*newNode =
      new LinkedNodeClass< T >(tail, newItem, NULL);
    newNode->setBeforeAndAfterPointers();
    tail = newNode;
  }
}

template< class T >
bool FIFOQueueClass< T >::dequeue(T& outItem)
{
  //if the list is empty
  if (!head)
  {
    return false;
  }
  outItem = head->getValue();
  //if there is only one node
  if (head == tail)
  {
    delete head;
    head = NULL;
    tail = NULL;
    return true;
  }
  LinkedNodeClass< T >*tmp = head;
  head = head->getNext();
  head->setPreviousPointerToNull();
  delete tmp;
  return true;
}

template< class T >
void FIFOQueueClass< T >::print() const
{
  LinkedNodeClass< T >*curr = head;
  while (curr)
  {
    cout << curr->getValue() << " ";
    curr = curr->getNext();
  }
  cout << endl;
}

template< class T >
int FIFOQueueClass< T >::getNumElems() const
{
  LinkedNodeClass< T >*curr = head;
  int count = 0;
  while (curr)
  {
    count++;
    curr = curr->getNext();
  }
  return count;
}

template< class T >
void FIFOQueueClass< T >::clear()
{
  LinkedNodeClass< T >*curr = head;
  while (curr) {
    LinkedNodeClass< T >*nextNode = curr->getNext();
    delete curr;
    curr = nextNode;
  }
  head = NULL;
  tail = NULL;
}