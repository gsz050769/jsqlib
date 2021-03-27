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


int main(void)
{
	ljs * my_json = NULL;

	printf("\n");

	printf("[LJS] ljs start\n");

	my_json = ljs_init();
	ljs_add_string(my_json,"msgId:ljsType_string","gib_2020");
	ljs_add_string(my_json,"payload:ljsType_object/ipui:ljsType_string","0001020304");
	ljs_add_string(my_json,"payload:ljsType_object/msg:ljsType_object/ms_msg_id:ljsType_string","as1_fac_man_5");
	ljs_add_string(my_json,"payload:ljsType_object/msg:ljsType_object/server_msg_status:ljsType_string","new");
	ljs_add_string(my_json,"payload:ljsType_object/msg:ljsType_object/status_icon:ljsType_string","ico_accept");
	ljs_add_string(my_json,"payload:ljsType_object/msg:ljsType_object/status_text:ljsType_string","accept");
	ljs_add_string(my_json,"payload:ljsType_object/msg:ljsType_object/deletable:ljsType_string","true");
	ljs_add_string(my_json,"payload:ljsType_object/msg:ljsType_object/ttl:ljsType_string","1039");
	ljs_add_string(my_json,"payload:ljsType_object/msg:ljsType_object/msg_icon:ljsType_object/namer:ljsType_string","exclamation_mark");
	ljs_add_array(my_json, "payload:ljsType_object/msg:ljsType_object/body:ljsType_array",NULL);
	ljs_add_array(my_json, "payload:ljsType_object/msg:ljsType_object/reply_options:ljsType_array",NULL);
	
	ljs *my_body=NULL; 
	ljs_read_array(my_json,"payload:ljsType_object/msg:ljsType_object/body:ljsType_array",&my_body);
	ljs_add_string(my_body,"0:ljsType_object/msg_icon:ljsType_object/name:ljsType_string","info");
	ljs_add_string(my_body,"1:ljsType_object/paragraph:ljsType_object/text:ljsType_string","Machine defect");
	ljs_add_string(my_body,"1:ljsType_object/paragraph:ljsType_object/blink:ljsType_string","no");
	ljs_add_string(my_body,"1:ljsType_object/paragraph:ljsType_object/underline:ljsType_string","no");
	ljs_add_string(my_body,"1:ljsType_object/paragraph:ljsType_object/bold:ljsType_string","yes");
	ljs_add_string(my_body,"1:ljsType_object/paragraph:ljsType_object/align:ljsType_string","left");

	ljs *my_reply=NULL; 
	ljs_read_array(my_json,"payload:ljsType_object/msg:ljsType_object/reply_options:ljsType_array",&my_reply);
	ljs_add_string(my_reply,"0:ljsType_object/option_id:ljsType_string","1234534354");
	ljs_add_string(my_reply,"0:ljsType_object/reply:ljsType_object/text:ljsType_string","Accept");
	ljs_add_string(my_reply,"1:ljsType_object/option_id:ljsType_string","5623432423");
	ljs_add_string(my_reply,"1:ljsType_object/reply:ljsType_object/text:	","Reject");
	


	ljs_print(my_json,ljsFormat_pretty);  
	ljs_free(my_json);

	// ###############################################################
	// -1- example create json object: {"obj":{"arr":[null,"hallo"]}}
	//     using qualifier "obj:ljsTy ...
	printf("[LJS] #############################################################\n");
	printf("[LJS] output example 1:\n");
	my_json = ljs_init();
	ljs_add_string(my_json,"obj:ljsType_object/arr:ljsType_array/-1:ljsType_string","hallo");
	// print to console:
	ljs_print(my_json,ljsFormat_pretty);  
	// create string from json object 
	char * out=ljs_print_malloc(my_json);
	printf("[LJS] ljs json=%s\n",out);
	if (out)
	{
		free (out);  // user is needs to take care for memeory free
	}
	// free json root object
	ljs_free(my_json);

	// ###############################################################
	// -2- example create json object: from string, and access array index 1
	printf("[LJS] #############################################################\n");
	printf("[LJS] output example 2:\n");
	my_json=ljs_add_parse("{\"name\":\"donald\", \"address\":[\"Victotry street\",5,null]}");
	//my_json=ljs_add_parse("{\"name\":\"donald\",\"address\":[\"test\"]}");
	int idx=0;char *info=NULL;
	if(!ljs_add_parse_ok(&idx,&info))
	{
		printf("[LJS] parse error at idx=%d: %s\n",idx,info);
	}
	
	ljs_print(my_json,ljsFormat_pretty);  


	char * street=0;
	if (0==ljs_read_string(my_json,"address:ARR/0:STR",&street))
	{
		printf("[LJS] Street = %s\n",street);
	}

	double street_number=0;
	if (0==ljs_read_number(my_json,"address:ljsType_array/1:ljsType_number",&street_number))
	{
		printf("[LJS] Number = %d\n",(int)street_number);
	}
	street_number=0;
	if (0==ljs_read_number(my_json,"address:ARR/1:NO",&street_number))
	{
		printf("[LJS] Number agian = %d\n",(int)street_number);
	}
	ljs_free(my_json);


	my_json = ljs_init();
	ljs_add_string(my_json,"persons:ARR/0:OBJ/lastname:STR","Trump");
	ljs_add_string(my_json,"persons:ARR/0:OBJ/firstname:STR","Donald");
	ljs_add_number(my_json,"persons:ARR/0:OBJ/iq:NO",-100);
	ljs_add_bool(my_json,"persons:ARR/0:OBJ/active:BOOL",0);
	ljs_print(my_json,ljsFormat_pretty);  
	ljs_free(my_json);

	return 0;
}