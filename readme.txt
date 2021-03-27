/**
 *    Json libarary (jlib) used to create and read JSON messages in an eay way.
 *    Copyright (C) 2021  Georg Schmitz
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
//
//	VERSION 1.0 initial version
//	
//	Set of functions used to create and read JSON messages in an easy way.
//	
//	include <libjson.h>
//
//	Access to an JSON is object is realized by an so called qualifier string
//	(qual). A qual string is built up from a chain of key + JSON object type:
//	
//
//	qual = "<key>:<json_data_type>/<key>:<json_data_type>/..."
//	
//	with
//		<key> = json key of the JSON object
//		<json_data_type> ?  enum ljsType as string:
//	      OBJ   object
//        ARR   array
//        BOOL  bool
//	      STR   string
//        NO    number
//        NULL  null
//
//	e.g. 
//	
//	ljs * my_json = ljs_init();
//	ljs_add_string(my_json,"person:OBJ/firstname:STR","Georg");
//	ljs_add_string(my_json,"person:OBJ/lastname:STR","Schmitz");
//	ljs_print(my_json,ljsFormat_pretty);
//	ljs_free(my_json);
//	
//	{
//		"person" : {
//			"firstname" : "Georg",
//			"lastname" : "Schmitz"
//		}
//	}
//
//	ToDo:
//		- extensive testing 
//

	

