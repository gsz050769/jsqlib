/**
 *	Json libarary (jlib) used to create and read JSON messages in an eay way.
 *	Copyright (C) 2021  Georg Schmitz
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 *	@file libjson.c
 *	@author Georg Schmitz
 *	@version 0.0 21/01/21
 *
 *	jlib is an easy to use json librayr. Json objects can easily reffered to by a
 *	qualifier string of format : 
 *  
 *	"<level1_key>:<ljsType_xxx>/<level1_key>:<ljsType_xxx>/..."
 *
 *	example given:  
 * 
 *		ljs_add_string(my_json,"person:ljsType_object/Adresse:ljsType_object/Strasse:ljsType_string","Bond Street");
 *  
 *		creates this JSON content
 * 
 *		{
 *			"person" : {
 *				"Adresse" : {
 *					"Strasse" : "Bond Street"
 *				}
 *			}
 *  
 *		}
 *
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h> 
#include <stdlib.h> 
#include <string.h>

#include "libjson.h"
#include "libjson_qual.h"
#include "libjson_write.h"
#include "libjson_print.h"
#include "libjson_free.h"
#include "libjson_read.h"
#include "libjson_parse.h"
#include "libjson_memory.h"

static bool ljs_strend(char * str,  char *end)
{
    int len_str  = strlen(str);
    int len_end  = strlen(end); 
    if (len_str >= len_end)
    {
        return (0 == memcmp(end, str + (len_str - len_end), len_end));
    }
    return 0;
}

/**
    create an initialized json object
    @param -
    @return ljs object, or NULL in case init fails
*/
ljs * ljs_init(void)
{
	ljs * ljsRet= NULL;
	ljsRet = libjson_malloc(sizeof(ljs));
	if(ljsRet!=NULL)
	{
		memset(ljsRet,0,sizeof(ljs));
		ljsRet->type=ljsType_root;
		ljsRet->child=NULL;
		ljsRet->next=NULL;
		//printf("[LJS] %s %p \n",__FUNCTION__,ljsRet);
		return ljsRet;
	}
	return NULL;
}

/**
    free a ljs object and all it childs, currently only root can be passed
    @param	pointer to ljs object to be freed
    @return	0 = ok, -1 = error
*/
int ljs_free(ljs *js)
{
	if(js)
	{
		ljs_free_object(js,1);
	}
	return 0;
}

/**
    parse a json string into ljs structure
    @param	pointer to ljs object
    @return	0 = ok, -1 = error
*/
ljs* ljs_add_parse(char * in)
{
	return (ljs_parse_from_string(in));
}

/**
    parse a json string into ljs structure
    @param	pointer to ljs object
    @return	0 = ok, -1 = error
*/
bool ljs_add_parse_ok(int * line, char ** err)
{
	ljs_parse_ok(line, err);
}

/**
    add bool object to json object
    @param	pointer to ljs the object where element is inserted
    @return	0 = ok, -1 = error
*/
int ljs_add_bool(ljs *js, char * qualifier, bool val)
{
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_BOL)) || (ljs_strend(qualifier,LJS_QUAL_2_BOL)) ) )
	{
	  return (ljs_write(js,qualifier,(void*) (&val)) );
	}
	return -1;
}

/**
    add null object to json object
    @param	pointer to ljs the object where element is inserted
    @return	0 = ok, -1 = error
*/
int ljs_add_null(ljs *js, char * qualifier)
{
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_NUL)) || (ljs_strend(qualifier,LJS_QUAL_2_NUL)) ) )
	{
	  return (ljs_write(js,qualifier,NULL) );
	}
	return -1;
}

/**
    add string object to json object
    @param	pointer to ljs the object where element is inserted
    @return	0 = ok, -1 = error
*/
int ljs_add_string(ljs *js, char * qualifier, char *  val)
{
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_STR)) || (ljs_strend(qualifier,LJS_QUAL_2_STR)) ) )
	{
	  return (ljs_write(js,qualifier,(char*)val) );
	}
	return -1;
}

/**
    add integer object to json object
    @param	pointer to ljs the object where bool object is inserted
    @return	0 = ok, -1 = error
*/
int ljs_add_number(ljs *js, char * qualifier, double val)
{
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_NUM)) || (ljs_strend(qualifier,LJS_QUAL_2_NUM)) ) )
	{
	  return (ljs_write(js,qualifier,(void*) (&val)) );
	}
	return -1;
}


/**
    add null ljs * to json of type object to json object
    @param	pointer to ljs the object where element is inserted
    @return	0 = ok, -1 = error
*/
int ljs_add_object(ljs *js, char * qualifier, ljs* jsAdd)
{
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_OBJ)) || (ljs_strend(qualifier,LJS_QUAL_2_OBJ)) ) )
	{
	  return (ljs_write(js,qualifier,(void*) jsAdd) );
	}
	return -1; 
}

/**
    add null ljs * to json of type array to json object
    @param	pointer to ljs the object where element is inserted
    @return	0 = ok, -1 = error
*/
int ljs_add_array(ljs *js, char * qualifier, ljs* jsAdd)
{
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_ARR)) || (ljs_strend(qualifier,LJS_QUAL_2_ARR)) ) )
	{
	  return (ljs_write(js,qualifier,(void*) jsAdd) );
	}
	return -1; 
}

/**
    ...
    @param	...
    @return	...
*/
int   ljs_read_bool(ljs * js, char * qualifier, bool * result)
{
	bool * tmp=NULL;
	int res=-1;
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_BOL)) || (ljs_strend(qualifier,LJS_QUAL_2_BOL)) ) )
	{
		res=ljs_read(js,qualifier, (void**) &tmp);
		*result=*tmp;
	}
	return res;
}

/**
    ...
    @param	...
    @return	...
*/
int  ljs_read_null(ljs * js, char * qualifier)
{
	void * tmp=NULL;
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_NUL)) || (ljs_strend(qualifier,LJS_QUAL_2_NUL)) ) )
	{
		return (ljs_read(js,qualifier, &tmp));
	}
	return -1;
}

/**
    ...
    @param	...
    @return	...
*/
int  ljs_read_string(ljs * js, char * qualifier, char ** result)
{
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_STR)) || (ljs_strend(qualifier,LJS_QUAL_2_STR)) ) )
	{
		return (ljs_read(js,qualifier, (void**) result));
	}
	return -1;
}


/**
    ...
    @param	...
    @return	...
*/
int ljs_read_number(ljs * js, char * qualifier, double * result)
{
	double * tmp=NULL;
	int res=-1;
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_NUM)) || (ljs_strend(qualifier,LJS_QUAL_2_NUM)) ) )
	{
		res=ljs_read(js,qualifier, (void**) &tmp);
		if (tmp)
		{
			*result=*tmp;
		}
	}
	return res;
}

/**
    ...
    @param	...
    @return	...
*/
int  ljs_read_object(ljs * js, char * qualifier, ljs ** result)
{
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_OBJ)) || (ljs_strend(qualifier,LJS_QUAL_2_OBJ)) ) )
	{
		return (ljs_read(js,qualifier, (void**) result));
	}
	return -1;
}

/**
    ...
    @param	...
    @return	...
*/
int  ljs_read_array(ljs * js, char * qualifier, ljs ** result)
{
	if( (js) && ( (ljs_strend(qualifier,LJS_QUAL_1_ARR)) || (ljs_strend(qualifier,LJS_QUAL_2_ARR)) ) )
	{
		return (ljs_read(js,qualifier, (void**) result));
	}
	return -1;
}

/**
    ...
    @param	...
    @return	...
*/
ljs *  ljs_read_get_ref(ljs * js, char * qualifier)
{
	if(js)
	{
		return (ljs_read_ref(js,qualifier));
	}
	return NULL;
}

ljsType ljs_read_get_parent_type(ljs *js)
{
	//printf("[LJS] %s %p \n",__FUNCTION__,js);
	while(js)
	{
		if (js->type==ljsType_root)
		{
			if(js->prev)
			{
				return js->prev->type;
			}
		}
		js=js->prev;
	}
	return ljsType_invalid;
}

ljsType ljs_read_type(ljs *js)
{
	while(js)
	{
		return js->type;
	}
	return ljsType_invalid;
}

ljs * ljs_read_get_parent(ljs *js)
{
	ljsType js_type;
	//printf("[LJS] %s start %p \n",__FUNCTION__,js);
	while(js)
	{
		js_type=js->type;
		if (js_type==ljsType_root) //js->type==ljsType_root) //js->type==ljsType_root)
		{
			if(js->prev)
			{
				return js->prev;
			}
		}
		js=js->prev;
	}
	return NULL;
}


/**
    print ljs object
    @param	pointer to ljs the object where element is inserted
    @return	0 = ok, -1 = error
*/
char * ljs_print(ljs * js, ljsFormat format)
{
	ljs_print_start();
	ljs_print_element(js,format);
	ljs_print_end();
	return NULL;
}

/**
    
    @param	pointer to ljs the object where element is inserted
    @return	
*/
char * ljs_print_malloc(ljs *js)
{
	return ljs_print_malloc_element(js);
}
