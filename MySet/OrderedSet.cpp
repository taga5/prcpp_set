#include "OrderedSet.h"

int * OrderedSet::begin() const {
	return Set::begin() + m_start;
}

OrderedSet OrderedSet::getSmaller(const int x) const {
	int i = 0;
	while (i < m_size && x > (*this)[i]) i++;
	return OrderedSet(*this, 0, i);
}

OrderedSet OrderedSet::getLarger(const int x) const {
	int i = 0;
	while (i < m_size && x >= (*this)[i]) i++;
	return OrderedSet(*this, i, m_size - i);
}

Set OrderedSet::merge(const Set & set) const {
	const OrderedSet* os = dynamic_cast<const OrderedSet*>(&set);
	if (!os) return Set::merge(set);
	else {
		OrderedSet newset(m_size + os->m_size);
		int* p1 = begin();
		int* p2 = os->begin();
		int i = 0, j = 0, k = 0; //i to iterate through newvals, j to iterate through this, k to iterate through os
		while (k < os->m_size) { //while there is sth in os
			if (j < m_size && p1[j] < p2[k]) newset[i] = p1[j++]; //add and inc only j
			else if (j < m_size && p1[j] == p2[k]) { newset[i] = p1[j]; j++; k++; } //add and inc both if they are the same
			else newset[i] = p2[k++];
			i++;
		}
		newset.m_size = i;
		return newset;
	}
}