#include "list_functions.h"


static int IfLessFunc(void* _a, void* _b)
{
	if (*(int*)_a < *(int*)_b)
	{
		return 1;
	}
	return 0;
}

static void Swap(ListItr _a, ListItr _b)
{
	void* aElement = ListItr_Set(_a, ListItr_Get(_b));
	ListItr_Set(_b, aElement);
}

void BubbleUp(ListItr _begin, ListItr _end, LessFunction _less)
{
	ListItr nxt = ListItr_Next(_begin);
	
	while (ListItr_Equals(nxt, _end) == 0)
	{
		if (! _less(ListItr_Get(_begin), ListItr_Get(nxt)))
		{
			Swap(_begin, nxt);
		}
		_begin = nxt;
		nxt = ListItr_Next(_begin);
	}
}

ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	if (_begin != NULL && _end != NULL && _predicate != NULL)
	{
		while (ListItr_Equals(_begin, _end) == 0)
		{
			if (_predicate(ListItr_Get(_begin), _context) == 1)
			{
				return _begin;
			}
			_begin = ListItr_Next(_begin);
		}
	}
	
	return _end;
}

size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	size_t counter = 0;
	if (_begin != NULL && _end != NULL && _predicate != NULL)
	{
		while (ListItr_Equals(_begin, _end) == 0)
		{
			++counter;
						
			if (_predicate(ListItr_Get(_begin), _context) == 1)
			{				
				return counter;
			}
			_begin = ListItr_Next(_begin);
		}
	}
	
	return 0;
}

ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	if (_begin != NULL && _end != NULL && _action != NULL)
	{
		while (ListItr_Equals(_begin, _end) == 0)
		{
			if (_action(ListItr_Get(_begin), _context) == 0)
			{
				return _begin;
			}
			_begin = ListItr_Next(_begin);
		}
	}
	
	return _end;	
}

void ListItr_Sort(ListItr _begin, ListItr _end, LessFunction _less)
{
	if (_begin == NULL || _end == NULL || _less == NULL || ListItr_Equals(_begin, _end) == 1)
	{
		return;
	}
	
	while (ListItr_Equals(_begin, _end) == 0)
	{
		BubbleUp(_begin, _end, _less);
		_end = ListItr_Prev(_end);
	}
}

ListItr ListItr_Splice(ListItr _dest, ListItr _begin, ListItr _end)
{
	if (_begin == NULL || _end == NULL || _dest == NULL ||  ListItr_Equals(_begin, _end) == 1)
	{
		return _begin;
	}
	
	while (ListItr_Equals(_begin, _end) == 0)
	{
		ListItr_InsertBefore(_dest, ListItr_Get(_begin));
		_begin = ListItr_Next(_begin);
		ListItr_Remove(ListItr_Prev(_begin)); 
	}
	return _dest;
}

ListItr ListItr_Merge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd, ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{

	if (_destBegin == NULL || _firstBegin == NULL || _firstEnd == NULL || _secondBegin == NULL || _secondEnd == NULL || _less == NULL)
	{
		return NULL;
	}

	while (!ListItr_Equals(_secondBegin, _secondEnd) && !ListItr_Equals(_firstBegin, _firstEnd))
	{
		if (_less(ListItr_Get(_firstBegin), ListItr_Get(_secondBegin)) == 1)
		{
			ListItr_InsertBefore(_destBegin, ListItr_Get(_firstBegin));
			_firstBegin = ListItr_Next(_firstBegin);
			ListItr_Remove(ListItr_Prev(_firstBegin));
		}
		
		else
		{
			ListItr_InsertBefore(_destBegin, ListItr_Get(_secondBegin));
			_secondBegin = ListItr_Next(_secondBegin);
			ListItr_Remove(ListItr_Prev(_secondBegin));
		}

	}
	
	if (ListItr_Equals(_firstBegin, ListItr_Next(_firstEnd)) == 0)
	{
		while (ListItr_Equals(_firstBegin, ListItr_Next(_firstEnd)) == 0)
		{
			ListItr_InsertBefore(_destBegin, ListItr_Get(_firstBegin));
			_firstBegin = ListItr_Next(_firstBegin);
			ListItr_Remove(ListItr_Prev(_firstBegin));
		}
	}
	
	else
	{
		while (ListItr_Equals(_firstBegin, ListItr_Next(_firstEnd)) == 0)
		{
			ListItr_InsertBefore(_destBegin, ListItr_Get(_secondBegin));
			_secondBegin = ListItr_Next(_secondBegin);
			ListItr_Remove(ListItr_Prev(_secondBegin));
		}
	}
	return _destBegin;
}


List* ListItr_Cut(ListItr _begin, ListItr _end)
{
	List* newList = NULL;

	if (_begin == NULL || _end == NULL || ListItr_Equals(_begin, _end) == 1)
	{
		return NULL;
	}
	
	newList = List_Create();

	while (ListItr_Equals(_begin, _end) == 0)
	{
		List_PushTail(newList, ListItr_Get(_begin));
		_begin = ListItr_Next(_begin);
		ListItr_Remove(ListItr_Prev(_begin));
	}
	
	return newList;
}

List* ListItr_Unique(ListItr _begin, ListItr _end, EqualsFunction _equals)
{
	List* newList = NULL;
	if (_begin == NULL || _end == NULL || ListItr_Equals(_begin, _end) == 1)
	{
		return NULL;
	}
	ListItr_Sort(_begin, _end, IfLessFunc);	

	newList = List_Create();

	while (ListItr_Equals(_begin, ListItr_Prev(_end)) == 0)
	{
		if (_equals(ListItr_Get(_begin), ListItr_Get(ListItr_Next(_begin))) == 1)
		{
			List_PushTail(newList, ListItr_Get(_begin));
			_begin = ListItr_Next(_begin);
			ListItr_Remove(ListItr_Prev(_begin));
		}
		
		else
		{
			_begin = ListItr_Next(_begin);
		}
	}
	
	return newList;
}
