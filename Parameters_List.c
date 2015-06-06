#include "Parameters_List.h"
#include <string.h>

#define NULL 0

JDFROUTE jdfroute;
ROUTE route;
ZDMROUTE zdmroute;
PMROUTE  pmroute;


JDFROUTE jdfroute;
void jdfroute_initial(JDFROUTE *l)
{
	l->size = 0;
	l->set = NULL;
}

void jdfroute_push_back(JDFROUTE *l)
{
	jdfroute_insert(l,l->size);
}

void jdfroute_insert(JDFROUTE *l,int index)
{
	JDFPOINT * pre_set = l->set;
	int new_size = l->size + 1;
	int i,j;
	l->set = (JDFPOINT*)calloc(new_size,sizeof(JDFPOINT));
	if (pre_set != NULL)
	{
		for (i = 0,j = 0; i < l->size ;++i,++j)
		{
			if (i==index)++j;
			memcpy(& l->set[j],& pre_set[i],sizeof(JDFPOINT));
		}
		free(pre_set);
	}
	l->size = new_size;
}

void jdfroute_del(JDFROUTE *l,int index)
{
	JDFPOINT * pre_set = l->set;
	int new_size = l->size - 1;
	if (new_size == 0)
	{
		free(l->set);
		l->set = NULL;
	}
	else
	{
		int i,j;
		l->set = (JDFPOINT*)calloc(new_size,sizeof(JDFPOINT));
		for (i = 0,j = 0;i<l->size;++i)
		{
			if (i!=index)
				memcpy(& l->set[j++],& pre_set[i],sizeof(JDFPOINT));
		}
		free(pre_set);
	}
	l->size = new_size;
}

void jdfroute_clr(JDFROUTE *l)
{
	free(l->set);
	l->set = NULL;
	l->size = 0;
}




void route_initial (ROUTE *l)
{
	l->size = 0;
	l->set = NULL;
}

void route_push_back (ROUTE *l)
{
	route_insert(l,l->size);
}

void route_insert (ROUTE *l,int index)
{
	POINT * pre_set = l->set;
	int new_size = l->size + 1;
	int i,j;
	l->set = (POINT*)calloc(new_size,sizeof(POINT));
	if (pre_set != NULL)
	{
		for (i = 0,j = 0; i < l->size ;++i,++j)
		{
			if (i==index)++j;
			memcpy(& l->set[j],& pre_set[i],sizeof(POINT));
		}
		free(pre_set);
	}
	l->size = new_size;
}

void route_del (ROUTE *l,int index)
{
	POINT * pre_set = l->set;
	int new_size = l->size - 1;
	if (new_size == 0)
	{
		free(l->set);
		l->set = NULL;
	}
	else
	{
		int i,j;
		l->set = (POINT*)calloc(new_size,sizeof(POINT));
		for (i = 0,j = 0;i<l->size;++i)
		{
			if (i!=index)
				memcpy(& l->set[j++],& pre_set[i],sizeof(POINT));
		}
		free(pre_set);
	}
	l->size = new_size;
}

void route_clr (ROUTE *l)
{
	free(l->set);
	l->set = NULL;
	l->size = 0;
}



ZDMROUTE zdmroute;
void zdmroute_initial(ZDMROUTE *l)
{
	l->size = 0;
	l->set = NULL;
}

void zdmroute_push_back(ZDMROUTE *l)
{
	zdmroute_insert(l,l->size);
}

void zdmroute_insert(ZDMROUTE *l,int index)
{
	ZDMPOINT * pre_set = l->set;
	int new_size = l->size + 1;
	int i,j;
	l->set = (ZDMPOINT*)calloc(new_size,sizeof(ZDMPOINT));
	if (pre_set != NULL)
	{
		for (i = 0,j = 0; i < l->size ;++i,++j)
		{
			if (i==index)++j;
			memcpy(& l->set[j],& pre_set[i],sizeof(ZDMPOINT));
		}
		free(pre_set);
	}
	l->size = new_size;
}

void zdmroute_del(ZDMROUTE *l,int index)
{
	ZDMPOINT * pre_set = l->set;
	int new_size = l->size - 1;
	if (new_size == 0)
	{
		free(l->set);
		l->set = NULL;
	}
	else
	{
		int i,j;
		l->set = (ZDMPOINT*)calloc(new_size,sizeof(ZDMPOINT));
		for (i = 0,j = 0;i<l->size;++i)
		{
			if (i!=index)
				memcpy(& l->set[j++],& pre_set[i],sizeof(ZDMPOINT));
		}
		free(pre_set);
	}
	l->size = new_size;
}

void zdmroute_clr(ZDMROUTE *l)
{
	free(l->set);
	l->set = NULL;
	l->size = 0;
}



PMROUTE pmroute;

void pmroute_initial(PMROUTE *l)
{
	l->size = 0;
	l->set = NULL;
}


void pmroute_push_back(PMROUTE *l)
{
	pmroute_insert(l,l->size);
}


void pmroute_insert(PMROUTE *l,int index)
{
	PMPOINT * pre_set = l->set;
	int new_size = l->size + 1;
	int i,j;
	l->set = (PMPOINT*)calloc(new_size,sizeof(PMPOINT));
	if (pre_set != NULL)
	{
		for (i = 0,j = 0; i < l->size ;++i,++j)
		{
			if (i==index)++j;
			memcpy(& l->set[j],& pre_set[i],sizeof(PMPOINT));
		}
		free(pre_set);
	}
	l->size = new_size;
}



void pmroute_del(PMROUTE *l,int index)
{
	PMPOINT * pre_set = l->set;
	int new_size = l->size - 1;
	if (new_size == 0)
	{
		free(l->set);
		l->set = NULL;
	}
	else
	{
		int i,j;
		l->set = (PMPOINT*)calloc(new_size,sizeof(PMPOINT));
		for (i = 0,j = 0;i<l->size;++i)
		{
			if (i!=index)
				memcpy(& l->set[j++],& pre_set[i],sizeof(PMPOINT));
		}
		free(pre_set);
	}
	l->size = new_size;
}

void pmroute_clr(PMROUTE *l)
{
	free(l->set);
	l->set = NULL;
	l->size = 0;
}








