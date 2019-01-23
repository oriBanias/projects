#ifndef __QUERY_H__
#define __QUERY_H__

/*Map_Result HashMap_Find(const HashMap* _map, const void* _searchKey, void** _pValue)*/

void* RetrieveSubscriptor(char* _msisdn, HashMap* _map);

void CreateReport(HashMap* _map, KeyValueActionFunction _action, void* _context);

#endif /* __QUERY_H__ */
