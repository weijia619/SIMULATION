#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
using namespace std;

//Weijia Chen
//12/03/2019
//sorted list class

template< class T >
SortedListClass< T >::SortedListClass()
{
  head = NULL;
  tail = NULL;
}

template< class T >
SortedListClass< T >::SortedListClass(
  const SortedListClass& rhs)
{
  if (rhs.head) {
    LinkedNodeClass< T >*currRhs = rhs.head;
    head = new LinkedNodeClass< T >(NULL, currRhs->getValue(), NULL);
    tail = head;
    while (currRhs->getNext()) {
      LinkedNodeClass< T >*newNode =
      new LinkedNodeClass< T >(tail, currRhs->getNext()->getValue(), NULL);
      tail = newNode;
      newNode->setBeforeAndAfterPointers();
      currRhs = currRhs->getNext();
    }
  }
}

template< class T >
SortedListClass< T >::~SortedListClass()
{
  this->clear();
}

template< class T >
void SortedListClass< T >::clear()
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

template< class T >
void SortedListClass< T >::insertValue(const T& valToInsert)
{
  //there are four cases
  //1. if the list is empty
  //2. the value should be insert as the head
  //3. the calue should be insert as the tail
  //4. others
  if (head == NULL)
  {
    LinkedNodeClass< T >*newNode =
    new LinkedNodeClass< T >(NULL, valToInsert, NULL);
    head = newNode;
    tail = newNode;
  }
  else if (valToInsert < head->getValue())
  {
    LinkedNodeClass< T >*newNode =
    new LinkedNodeClass< T >(NULL, valToInsert, head);
    newNode->setBeforeAndAfterPointers();
    head = newNode;
  }
  else if (valToInsert >= tail->getValue())
  {
    LinkedNodeClass< T >*newNode =
    new LinkedNodeClass< T >(tail, valToInsert, NULL);
    newNode->setBeforeAndAfterPointers();
    tail = newNode;
  }
  else
  {
    LinkedNodeClass< T >*curr = head;
    while (curr->getValue() < valToInsert)
    {
      curr = curr->getNext();
    }
    LinkedNodeClass< T >*newNode =
    new LinkedNodeClass< T >(curr->getPrev(), valToInsert, curr);
    newNode->setBeforeAndAfterPointers();
  }
}

template< class T >
void SortedListClass< T >::printForward() const
{
  cout << "Forward List Contents Follow:" << endl;
  LinkedNodeClass< T >*curr = head;
  while (curr)
  {
    cout << "  " << curr->getValue() << endl;
    curr = curr->getNext();
  }
  cout << "End Of List Contents" << endl;
}

template< class T >
void SortedListClass< T >::printBackward() const
{
  cout << "Backward List Contents Follow:" << endl;
  LinkedNodeClass< T >*curr = tail;
  while (curr)
  {
    cout << "  " << curr->getValue() << endl;
    curr = curr->getPrev();
  }
  cout << "End Of List Contents" << endl;
}

template< class T >
bool SortedListClass< T >::removeFront(T& theVal)
{
  //if the list is empty
  if (!head)
  {
    return false;
  }
  theVal = head->getValue();
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
bool SortedListClass< T >::removeLast(T& theVal)
{
  //if the list is empty
  if (!tail)
  {
    return false;
  }
  theVal = tail->getValue();
  //if there is only one node
  if (head == tail)
  {
    delete tail;
    head = NULL;
    tail = NULL;
    return true;
  }
  LinkedNodeClass< T >*tmp = tail;
  tail = tail->getPrev();
  tail->setNextPointerToNull();
  delete tmp;
  return true;
}

template< class T >
int SortedListClass< T >::getNumElems() const
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
bool SortedListClass< T >::getElemAtIndex(const int index, T& outVal) const
{
  if (index > this->getNumElems() - 1 || index < 0)
  {
    return false;
  }
  LinkedNodeClass< T >*curr = head;
  for (int i = 0; i < index; i++)
  {
    curr = curr->getNext();
  }
  outVal = curr->getValue();
  return true;
}
