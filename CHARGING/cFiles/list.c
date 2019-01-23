#include "list_itr.h"
#include "list.h"
#include <stdlib.h>

typedef struct Node
{
	void* m_data;
	struct Node* mNext;
	struct Node* mPrev;
}Node;

struct List
{
	size_t magicNumber;
	Node mHead;
	Node mTail;
};

static void NodeRemove (Node* _node, Node* _prev, Node* _next)
{
	_prev->mNext = _node->mNext;
	_next->mPrev = _node->mPrev;
	free(_node);
}

static Node* NodeCreate(void* _data, Node* _prev, Node* _next) 
{
	Node* node = (Node*)malloc(1*sizeof(Node));
	if(node != NULL)
	{
		node->mNext = _next;
		node->mPrev = _prev;
		_prev->mNext = node;
		_next->mPrev = node;
		node->m_data = _data; 
	}
	
	return node;
}

List* List_Create(void)
{
	List* _pList = (List*)malloc(1*sizeof(List));
	
	if(NULL == _pList)
	{
		return NULL;
	}
	_pList->mTail.mPrev = &_pList->mHead;
	_pList->mHead.mNext = &_pList->mTail;
	_pList->mHead.mPrev = &_pList->mHead;
	_pList->mTail.mNext = &_pList->mTail;;
	_pList->magicNumber = 0xBEEFBEEF;
	
	
	return _pList;
}

void List_Destroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node* _head;
	Node* tmp;
	if(NULL == *_pList || NULL == _pList || (*_pList)->magicNumber != 0xBEEFBEEF || _elementDestroy==NULL)
	{
		return;
	}
	
	_head = (*_pList)->mHead.mNext; /* first node */

	while (_head != &((*_pList)->mTail))
	{
		tmp = _head;
		_head = _head->mNext;
		_elementDestroy((void*)tmp->m_data);
		free(tmp);
	}

	(*_pList)->magicNumber = 0xDEADBEEF;
	free(*_pList);
	*_pList = NULL;
	_pList = NULL;
	return;
}

List_Result List_PushHead(List* _pList, void* _item)
{
	Node* new_node;
	if(NULL == _pList || _pList->magicNumber != 0xBEEFBEEF )
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if (_item == NULL)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	new_node = NodeCreate(_item, &_pList->mHead, _pList->mHead.mNext );
	
	if(NULL == new_node)
	{
		return LIST_UNINITIALIZED_ERROR;
	}	
	return LIST_SUCCESS;
}

List_Result List_PushTail(List* _pList, void* _item)
{
	Node* new_node;
	if(NULL == _pList || _pList->magicNumber != 0xBEEFBEEF )
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if (_item == NULL)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	
	new_node = NodeCreate( _item, _pList->mTail.mPrev, &_pList->mTail);
	
	if(NULL == new_node)
	{
		return LIST_ALLOCATION_ERROR;
	}
	
	return LIST_SUCCESS;
}

List_Result List_PopHead(List* _pList, void** _pItem)
{
	Node* _node;
	if(NULL == _pList || _pList->magicNumber != 0xBEEFBEEF )
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if(_pList->mHead.mNext == &_pList->mTail)
	{
		return LIST_IS_EMPTY;
	}
	
	if (_pItem == NULL)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
		
	*_pItem = _pList->mHead.mNext->m_data;
	_node = _pList->mHead.mNext;
	NodeRemove(_node , _node->mPrev, _node->mNext);
	return LIST_SUCCESS;
}

List_Result List_PopTail(List* _pList, void** _pItem)
{
	Node* _node;
	if(NULL == _pList || _pList->magicNumber != 0xBEEFBEEF )
	{
		return LIST_UNINITIALIZED_ERROR;
	}

	if(_pList->mHead.mNext == &_pList->mTail)
	{
		return LIST_IS_EMPTY;
	}
	
	if (_pItem == NULL)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	_node = _pList->mTail.mPrev;
	*_pItem = _pList->mTail.mPrev->m_data;
	NodeRemove(_node ,_node->mPrev, _node->mNext);

	return LIST_SUCCESS;
}

size_t List_Size(const List* _pList)
{
	Node* _mHead;
	size_t counter = 0;
	if(NULL == _pList || _pList->magicNumber != 0xBEEFBEEF )
	{
		return counter;
	}
	if(_pList->mHead.mNext == &_pList->mTail)
	{
		return counter;
	}
	else
	{
		_mHead = _pList->mHead.mNext;
		while(_mHead != &(_pList->mTail))
		{
			_mHead = _mHead->mNext;
			++counter;
		}
	}
	return counter;
}

ListItr ListItr_Begin(const List* _list)
{
	return (ListItr)(_list->mHead.mNext);
}

ListItr ListItr_End(const List* _list)
{
	return (ListItr)(&_list->mTail);
}

int ListItr_Equals(const ListItr _a, const ListItr _b)
{ 
	if (_a == _b)
	{
		return 1;
	}
	return 0;
}

ListItr ListItr_Next(ListItr _itr)
{
	return (ListItr)(((Node*)_itr)->mNext);
}

ListItr ListItr_Prev(ListItr _itr)
{
	return (ListItr)(((Node*)_itr)->mPrev);
}

void* ListItr_Get(ListItr _itr)
{
	return ((Node*)_itr)->m_data;
}

void* ListItr_Set(ListItr _itr, void* _element)
{
	void* temp = ((Node*)_itr)->m_data;

	((Node*)_itr)->m_data = _element;

	return temp;
	
}

ListItr ListItr_InsertBefore(ListItr _itr, void* _element) 
{
	ListItr _newItr;
/*	if (ListItr_Equals(_itr, (ListItr_Prev(_itr))) == 1) 
	{
		return NULL;
	}  */
	_newItr = (ListItr)(NodeCreate( _element, ((Node*)_itr)->mPrev, ((Node*)_itr)));
	return _newItr;
}

void* ListItr_Remove(ListItr _itr)
{
	void* temp = ListItr_Get(_itr);	
	NodeRemove( (Node*)_itr, ((Node*)_itr)->mPrev, ((Node*)_itr)->mNext);
	return temp;
}






