//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     MAREK PRYMUS <xprymu01@vutbr.cz>
// $Date:       $2021-01-03
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author MAREK PRYMUS
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
	m_pHead = new Element_t;
	m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
	 Element_t *tmp = GetHead();
	 Element_t *tmp2 = tmp;
	 while(tmp != NULL && tmp->pNext != NULL){
	 	tmp2 = tmp;
	 	tmp = tmp->pNext;
	 	delete tmp2;
	 } 
}

void PriorityQueue::Insert(int value)
{
	if(m_pHead != NULL && value < m_pHead->value){
		Element_t *tmpHead = GetHead();
		while(tmpHead->pNext != NULL && tmpHead->pNext->value > value){
			tmpHead = tmpHead->pNext;
		}
		Element_t *tmp2 = tmpHead->pNext;
		tmpHead->pNext = new Element_t{
				.pNext = tmp2,
				.value = value
		};
	}
	else{
		Element_t *tmpHead = GetHead();
		m_pHead = new Element_t{
			.pNext = tmpHead,
			.value = value
		};
	}
}

bool PriorityQueue::Remove(int value)
{
	Element_t *tmp = GetHead();
	Element_t *tmp2 = GetHead();
	while(tmp != NULL){
		if(tmp->value == value){
			if(tmp == m_pHead){
				m_pHead = tmp->pNext;
				tmp == NULL;
				return true;
			}
			tmp2->pNext = tmp->pNext;
			tmp == NULL;
			return true;
		}
		tmp2 = tmp;
		tmp = tmp->pNext;
	}
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
	Element_t *tmp = GetHead();
	while(tmp != NULL){
		if(tmp->value == value){
			return tmp;
		}
		tmp = tmp->pNext;
	}
    return NULL;
}

size_t PriorityQueue::Length()
{
	Element_t *tmp = GetHead();
	int counter = 0;
	while(tmp != NULL){
		counter ++;
		tmp = tmp->pNext;
	}
	return counter;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
