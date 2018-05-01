#ifndef WAVEFRONT_AUTO_VECTOR_H
#define	WAVEFRONT_AUTO_VECTOR_H

#include <vector>

namespace Wavefront
{

template <class T> class auto_vector
{
private:
  std::vector<T*> items;

public:
  ~auto_vector()
  {
    for(int index = 0; index < items.size(); index++)
    {
      delete items.at(index);
    }
  }

  void clear()
  {
    for(int index = 0; index < items.size(); index++)
    {
      delete items.at(index);
    }

    items.clear();
  }

  void add(T* item)
  {
    items.push_back(item);
  }

  T* at(int position)
  {
    return items.at(position);
  }

  int size()
  {
    return items.size();
  }

  void remove(int position)
  {
    delete items.at(position);

    items.erase(items.begin() + position);
  }

  void remove(T* ptr)
  {
    T* temp = NULL;

    for(int index = 0; index < items.size(); index++)
    {
      if(ptr == items.at(index))
      {
        temp = items.at(index);
        items.erase(items.begin() + index);
        delete temp;
        index--;
      }
    }
  }

  void swap(int sourcePosition, int destPosition)
  {
    T* temp = NULL;

    temp = items.at(sourcePosition);
    items.at(sourcePosition) = items.at(destPosition);
    items.at(destPosition) = temp;
  }

  void insert(int position, T* item)
  {
    items.insert(items.begin() + position, item);
  }
};

}

#endif

