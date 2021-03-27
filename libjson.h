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

// *******************************************************
// Object types
// *******************************************************
#ifndef _LIBJSON_H_
#define _LIBJSON_H_
typedef enum ljsType
{
	ljsType_root,
    ljsType_object,
	ljsType_array,
	ljsType_null,
    ljsType_bool,
    ljsType_string,
    ljsType_number,
	ljsType_invalid
} ljsType;

// **************************************************************
// qualifier names old (depreciated for back wards compatibility)
// **************************************************************
#define  LJS_QUAL_1_OBJ "ljsType_object"
#define  LJS_QUAL_1_ARR "ljsType_array"
#define  LJS_QUAL_1_NUL "ljsType_null"
#define  LJS_QUAL_1_BOL	"ljsType_bool"
#define  LJS_QUAL_1_STR "ljsType_string"
#define  LJS_QUAL_1_NUM "ljsType_number"
// *******************************************************
// qualifier names new short
// *******************************************************
#define  LJS_QUAL_2_OBJ "OBJ"
#define  LJS_QUAL_2_ARR "ARR"
#define  LJS_QUAL_2_NUL "NULL"
#define  LJS_QUAL_2_BOL	"BOOL"
#define  LJS_QUAL_2_STR "STR"
#define  LJS_QUAL_2_NUM "NO"


// *******************************************************
// print formats 
// *******************************************************
typedef enum ljsFormat
{
	ljsFormat_compact,
	ljsFormat_pretty
} ljsFormat;

// *******************************************************
// internal data structure
// *******************************************************
typedef struct ljs
{
	ljsType type;
	struct ljs *next;
	struct ljs *prev;
	struct ljs *child;
	char * key;
	char * strVal;
	double doubleVal;
	bool boolean;
	double number;
} ljs;

// *******************************************************
// init and free of js objects
// *******************************************************
extern ljs * ljs_init(void);
extern int ljs_free(ljs *js);

// *******************************************************
// Interface add content to a json object 
// *******************************************************
extern ljs* ljs_add_parse(char * in);
extern bool ljs_add_parse_ok(int * line, char ** err);
extern int  ljs_add_bool(ljs *js, char * qualifier, bool val);
extern int  ljs_add_null(ljs *js, char * qualifier);
extern int  ljs_add_string(ljs *js, char * qualifier, char *  val);
extern int  ljs_add_number(ljs *js, char * qualifier, double val);
extern int  ljs_add_double(ljs *js, char * qualifier, double val);
extern int  ljs_add_object(ljs *js, char * qualifier, ljs* jsAdd);
extern int  ljs_add_array(ljs *js, char * qualifier, ljs* jsAdd);

// *******************************************************
// Interface read content from a json object 
// *******************************************************
// get value of different object types:
extern int  ljs_read_bool(ljs * js, char * qualifier, bool *res);
extern int  ljs_read_null(ljs * js, char * qualifier);
extern int  ljs_read_string(ljs * js, char * qualifier, char ** res);
extern int  ljs_read_number(ljs * js, char * qualifier, double * res);
extern int  ljs_read_double(ljs * js, char * qualifier, double * res);
extern int  ljs_read_object(ljs * js, char * qualifier, ljs ** res);  // first child (root element) of object
extern int  ljs_read_array(ljs * js, char * qualifier, ljs ** res);   // first child(root element) of array
// get pointer to any object type:
extern ljs* ljs_read_get_ref(ljs * js, char * qualifier);
extern ljs* ljs_read_get_parent(ljs *js);
extern ljsType ljs_read_get_parent_type(ljs *js);
extern ljsType ljs_read_type(ljs *js);



// *******************************************************
// Generate output from json object
// *******************************************************
extern char * ljs_print(ljs * js, ljsFormat format);
extern char * ljs_print_malloc(ljs *js);

#endif // _LIBJSON_H_