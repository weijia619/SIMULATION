#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedNodeClass.h"
using namespace std;

//Weijia Chen
//12/03/2019
//LinkedNodeClass

template< class T >
LinkedNodeClass< T >::LinkedNodeClass(
  LinkedNodeClass< T >*inPrev,
  const T& inVal,
  LinkedNodeClass< T >*inNext)
{
  prevNode = inPrev;
  nextNode = inNext;
  nodeVal = inVal;
}

template< class T >
T LinkedNodeClass< T >::getValue() const
{
  return nodeVal;
}

template< class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getNext() const
{
  return nextNode;
}

template< class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getPrev() const
{
  return prevNode;
}

template< class T >
void LinkedNodeClass< T >::setNextPointerToNull()
{
  nextNode = NULL;
}

template< class T >
void LinkedNodeClass< T >::setPreviousPointerToNull()
{
  prevNode = NULL;
}

template< class T >
void LinkedNodeClass< T >::setBeforeAndAfterPointers()
{
  if (prevNode)
  {
    prevNode->nextNode = this;
  }
  if (nextNode)
  {
    nextNode->prevNode = this;
  }
}