#include "ProbabilityHeap.h"

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::initialize() {
	// You can do initializations inside this method.
	Key itemKey = this->HEAP_EMPTY;
	Probability itemProbability = this->SUSPECT_NOT_ON_HEAP;
	this->capacity = 51437;
	this->numberOfItems = 0;
	this->heap.resize(51437);
	int i;
	for (i = 0; i < 51437; i++)
	{
	    this->heap[i].setKey(itemKey);
	    this->heap[i].setValue(itemProbability);
	}
}

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::heapUp(vector<HashTableItem<Key, Probability> > &heap, int index) {
    HashTableItem<Key, Probability> temp;
    

    if (this->numberOfItems < 2)
    {
        return;
    }
	while (this->heap[(index-1)/2].getValue() < this->heap[index].getValue())
	{
	    temp = this->heap[index];
	    this->heap[index] = this->heap[(index-1)/2];
	    this->heap[(index-1)/2] = temp;
	    
	    this->hashTable.insert(this->heap[index].getKey(), index);
	    this->hashTable.insert(this->heap[(index-1)/2].getKey(), (index-1) / 2);
	    index = (index-1) / 2;
	    
	}
}

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::heapify(vector<HashTableItem<Key, Probability> > &heap, int index)
{
    int left = (index*2)+1;
    int right = (index*2)+2;
    HashTableItem<Key, Probability> temp;
    if (left < this->numberOfItems || right < this->numberOfItems)
    {
        if (this->heap[index].getValue() < this->heap[left].getValue() || this->heap[index].getValue() < this->heap[right].getValue())
        {
            if (this->heap[left].getValue() < this->heap[right].getValue())
            {
                temp = this->heap[index];
                this->heap[index] = this->heap[right];
                this->heap[right] = temp;
                this->hashTable.insert(this->heap[index].getKey(), index);
                this->hashTable.insert(this->heap[right].getKey(), right);
                heapify(this->heap, right);
            }
            else
            {
                temp = this->heap[index];
                this->heap[index] = this->heap[left];
                this->heap[left] = temp;
                this->hashTable.insert(this->heap[index].getKey(), index);
                this->hashTable.insert(this->heap[left].getKey(), left);
                heapify(this->heap, left);
            }
        }
    }
}


template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::insert(const Key& key, const Probability& probability) {
	// TODO
    Key itemKey = key;
    Probability itemProbability = probability;
    this->heap[this->numberOfItems].setKey(itemKey);
    this->heap[this->numberOfItems].setValue(itemProbability);
    this->numberOfItems += 1;
    this->heapUp(heap, this->numberOfItems - 1);
}

template<class Key, class Probability>
const Key ProbabilityHeap<Key, Probability>::deleteMax() {
	// TODO
    int root;
    Key itemKey = this->heap[0].getKey();
    Probability itemProbability = this->heap[0].getValue();
    Probability freeProbability = this->SUSPECT_NOT_ON_HEAP;
    Key freeKey = this->HEAP_EMPTY;
    if (this->numberOfItems == 0)
    {
        return this->HEAP_EMPTY;
    }
    root = 0;
    HashTableItem<Key, Probability> deleted;
    HashTableItem<Key, Probability> temp;
    deleted = this->heap[root];
    temp = this->heap[0];
    this->heap[0] = this->heap[numberOfItems-1];
    this->heap[numberOfItems-1].setKey(freeKey);
    this->heap[numberOfItems-1].setValue(freeProbability);
    this->numberOfItems -= 1;
    this->heapify(this->heap, 0);
    this->hashTable.remove(itemKey);
    return deleted.getKey();
}

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::updateProbability(const Key& key, const Probability& newProbability) {
	// TODO
    Key itemKey = key;
    Probability itemValue = newProbability;
    
    if (this->hashTable.contains(itemKey))
    {
        itemKey = (this->hashTable.find(itemKey))->getKey();
        
        this->heap[(this->hashTable.find(itemKey))->getValue()].setValue(itemValue);
        this->heapify(this->heap, (this->hashTable.find(itemKey))->getValue());
    }
    
}

template<class Key, class Probability>
const Probability& ProbabilityHeap<Key, Probability>::getProbability(const Key& key) const {
	// TODO
	Key itemKey = key;

	if ((this->hashTable.contains(itemKey)))
	{
	    return (this->hashTable.find(itemKey))->getValue();
	}

}

template<class Key, class Probability>
void ProbabilityHeap<Key, Probability>::print() {
	// You can implement this method for test purposes.
}