#include "HashTable.h"

template <class Key, class Value>
HashTable<Key, Value>::HashTable() {
	// TODO
	this->table.resize(2);
	this->tableSize = 2;
	this->numberOfItems = 0;
}


template <class Key, class Value>
int HashTable<Key, Value>::newIndex(int index, int base) const {
	// TODO
	int stepSize = this->hashFunction2(base);

    index = ((stepSize + index) % this->tableSize);

    return index;
}

template <class Key, class Value>
bool HashTable<Key, Value>::insert(const Key& key, const Value& value) {
	// TODO
	Key itemKey = key;
	Value itemValue = value;
    if ((this->numberOfItems)*2 >= this->tableSize)
    {
        if (!this->contains(key))
        {
            this->rehash();
        }
    }
    int index;
    int stepSize;
    int base;
    index = this->hashFunction(key);
    if (this->table[index].deleted == true)
    {
        this->table[index].setKey(itemKey);
        this->table[index].setValue(itemValue);
        this->numberOfItems += 1;
        this->table[index].deleted = false;
        return true;
    }
    else if (this->table[index].active == false)
    {
        this->table[index].setKey(itemKey);
        this->table[index].setValue(itemValue);
        this->numberOfItems += 1;
        this->table[index].active = true;
        return true;
    }
    else
    {
        if (this->table[index].getKey() == key)
        {
            if (this->table[index].getValue() == value)
            {
                return false;
            }
            else
            {
                this->table[index].setValue(itemValue);
                return true;
            }
        }
        else
        {
            stepSize = this->hashFunction2(index);
            base = index;
            while (this->newIndex(index, base) != base)
            {
                index = this->newIndex(index, base);
                if (this->table[index].deleted == true)
                {
                    this->table[index].setKey(itemKey);
                    this->table[index].setValue(itemValue);
                    this->numberOfItems += 1;
                    this->table[index].deleted = false;
                    return true;
                }
                else if (this->table[index].active == false)
                {
                    this->table[index].setKey(itemKey);
                    this->table[index].setValue(itemValue);
                    this->numberOfItems += 1;
                    this->table[index].active = true;
                    return true;
                }
                else
                {
                    if (this->table[index].getKey() == key)
                    {
                        if (this->table[index].getValue() == value)
                        {
                            return false;
                        }
                        else
                        {
                            this->table[index].setValue(itemValue);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

template <class Key, class Value>
bool HashTable<Key, Value>::remove(const Key& key) {
	// TODO
    if (this->contains(key))
    {
        int index = this->hashFunction(key);
        if (this->table[index].getKey() == key && this->table[index].deleted == false && this->table[index].active == true)
        {
            this->table[index].deleted = true;
            this->numberOfItems -= 1;
            return true;
        }
        else
        {
            int stepSize = this->hashFunction2(index);
            int base = index;
            while (this->newIndex(index, base) != base)
            {
                index = this->newIndex(index, base);
                if (this->table[index].getKey() == key && this->table[index].deleted == false && this->table[index].active == true)
                {
                    this->table[index].deleted = true;
                    this->numberOfItems -= 1;
                    return true;
                }
            }
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <class Key, class Value>
bool HashTable<Key, Value>::contains(const Key& key) const {
	// TODO
	int index = this->hashFunction(key);
	
	if (this->table[index].getKey() == key && this->table[index].deleted == false && this->table[index].active == true)
	{
	    return true;
	}
    else
    {
        int base = index;
        while (this->newIndex(index, base) != base)
        {
            index = this->newIndex(index, base);
            if (this->table[index].getKey() == key && this->table[index].deleted == false && this->table[index].active == true)
            {
                return true;
            }
        }
        return false;
    }
}

template <class Key, class Value>
const HashTableItem<Key, Value>* HashTable<Key, Value>::find(const Key& key) const {
	// TODO
    if (this->contains(key))
    {

        int index = this->hashFunction(key);
        if (this->table[index].getKey() == key && this->table[index].deleted == false)
        {
            return &this->table[index];

        }
        else
        {
            int stepSize = this->hashFunction2(index);
            int base = index;
            while (this->newIndex(index, base) != base)
            {
                index = this->newIndex(index, base);
                if (this->table[index].getKey() == key && this->table[index].deleted == false)
                {
                    return &this->table[index];
                }
            }
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

template <class Key, class Value>
int HashTable<Key, Value>::getTableSize() const {
    // TODO
    return this->tableSize;
}

template <class Key, class Value>
int HashTable<Key, Value>::getNumberOfItems() const {
    // TODO
    return this->numberOfItems;
}

template <class Key, class Value>
int HashTable<Key, Value>::hashFunction(const Key& key) const {
	// TODO
	int i, result;
	result = 0;
	for (i = 0; key[i] != '\0' ; i++)
	{
	    result += key[i];

	}
	return (result % this->tableSize);	
}

template <class Key, class Value>
int HashTable<Key, Value>::hashFunction2(int key) const {
	// TODO
	if ((key * this->tableSize - 1) % this->tableSize < 0)
	{
	    return 0;
	}
	else
	{
	return ((key * this->tableSize - 1) % this->tableSize);
	}
}

template <class Key, class Value>
void HashTable<Key, Value>::rehash() {
	// TODO
	int i, count, j;
	vector<HashTableItem<Key, Value> > fake;
	count = 0;
	for (i = 0; i < this->tableSize; i++)
	{
	    if (this->table[i].active == true && this->table[i].deleted == false)
	    {
	        fake.push_back(this->table[i]);
	        this->table[i].active = false;
	        count += 1;
	    }
	}
	for (i = 0; i <= 14; i++)
	{
	    if (this->tableSize == primeNumbers[i])
	    {
	        j = primeNumbers[i+1];
	        break;
	    }
	}
	this->table.resize(j);
	this->tableSize = j;
	this->numberOfItems = 0;
	for (i = 0; i < count; i++)
	{
	    this->insert(fake[i].getKey(), fake[i].getValue());
	}
    
}

