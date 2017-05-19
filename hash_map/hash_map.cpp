#include "hash_map.h"

template<class keytype, class valtype>
hash_map<keytype, valtype>::hash_map()
{
	table = new list<std::pair<keytype, valtype> >[SIZE]
}

template<class keytype, class valtype>
hash_map<keytype, valtype>::hash_map(int _s)
{
	table = new list<std::pair<keytype, valtype> >[_s];
	size = _s;
}

template<class keytype, class valtype>
void hash_map<keytype, valtype>::insert(keytype key, valtype val)
{
	std::hash<keytype> hashOFkey;
	int tmp = hashOFkey(key) % size;
	table[tmp].push_front(std::pair<keytype, valtype>(key, val));  //adding to start of list
	count++;

	if (count > 1 / 3 * size)
	{
		rehash();
	}
}

template<class keytype, class valtype>
void hash_map<keytype, valtype>::clear()
{
	delete table;
	table = new std::list<std::pair<keytype, valtype>>[size];
}

template<class keytype, class valtype>
void hash_map<keytype, valtype>::erase(keytype key)
{
	std::hash<keytype> hashOFkey;
	int tmp = hashOFkey(key) % size;
	for (auto it = table[tmp].begin(); it != table[tmp].end(); it++) //prohodimsya po spisku kotoriy hranitsya pot indexom tmp;
	{
		if (it->first == key)
		{
			table[tmp].erase(it);
			count--;
		}
		break;
	}
}


template<class keytype, class valtype>
int hash_map<keytype, valtype>::get_size()
{
	return count;
}

template<class keytype, class valtype>
bool hash_map<keytype, valtype>::empty()
{
	for (int i = 0; i < size; i++)
		if (!table[i].empty())
		{
			return 0;
		}
	return 1;
}



template<class keytype, class valtype>
void hash_map<keytype, valtype>::rehash()
{
	int new_size = size * 2;
	std::hash<keytype> hashOFkey;
	std::list<std::pair<keytype, valtype>> *tmp;  //tmp mass for rehashing;
	int new_index;

	tmp = new list<std::pair<keytype, valtype> >[new_size];

	for (int i = 0; i < size; i++)
	{
		for (auto it = table[i].begin(); it != table[i].end(); it++)
		{
			new_index = hashOFkey(it->first) % new_size;
			tmp[new_index].push_front(std::make_pair(it->first, it->second));
		}
	}
	delete table;
	table = tmp;
	size = new_size;
}

template<class keytype, class valtype>
valtype& hash_map<keytype, valtype>::operator[](keytype key)
{
	std::hash<keytype> hashOFkey;
	int tmp = hashOFkey % size;
	for (auto it = table[tmp].begin(); it != table[tmp].end(); it++)
	{
		if (it->first == key)
		{
			return it->second;
		}
	}
}


template<class keytype, class valtype>
void hash_map<keytype, valtype>::show(keytype k)
{
	std::hash<keytype> hashofkey;
	int tmp = hashofkey(k) % size;
	std::list<std::pair<keytype, valtype>>::iterator it = table[tmp].begin();
	std::cout << it->first << " " << it->second;
}

