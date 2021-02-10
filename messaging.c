#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h> 
#include <stdlib.h> 
#include <string.h>

#include "libjson.h"

typedef struct hs
{
    char id[11];
}hs;


hs hs_array[2] = 
{
    "4021",
    "4021"
};

#define number_of_hs ((sizeof(hs_array))/(sizeof(hs)))

static ljs*  msg_hs_template(void)
{
    ljs * template = NULL;

	template = ljs_init();
	ljs_add_string(template,"msgId:ljsType_string","xxxxx");
    ljs_add_string(template,"payload:ljsType_object/amsgId:ljsType_string","xxxxxxxxx");
	ljs_add_string(template,"payload:ljsType_object/sip_id:ljsType_string","xxxxx");
	ljs_add_string(template,"payload:ljsType_object/msg:ljsType_object/server_msg_status:ljsType_string","new");
    ljs_add_string(template,"payload:ljsType_object/msg:ljsType_object/prio:ljsType_string","6");
    ljs_add_string(template,"payload:ljsType_object/msg:ljsType_object/title:ljsType_object/text:ljsType_string","Title");
	ljs_add_string(template,"payload:ljsType_object/msg:ljsType_object/status_icon:ljsType_string","ico_accept");
	ljs_add_string(template,"payload:ljsType_object/msg:ljsType_object/status_text:ljsType_string","accept");
	ljs_add_string(template,"payload:ljsType_object/msg:ljsType_object/deletable:ljsType_string","true");
	ljs_add_string(template,"payload:ljsType_object/msg:ljsType_object/ttl:ljsType_string","1039");
	ljs_add_string(template,"payload:ljsType_object/msg:ljsType_object/msg_icon:ljsType_object/name:ljsType_string","exclamation_mark");
	ljs_add_array(template, "payload:ljsType_object/msg:ljsType_object/body:ljsType_array",NULL);
	ljs_add_array(template, "payload:ljsType_object/msg:ljsType_object/reply_options:ljsType_array",NULL);

	
	ljs *body=NULL; 
	ljs_read_array(template,"payload:ljsType_object/msg:ljsType_object/body:ljsType_array",&body);
	ljs_add_string(body,"0:ljsType_object/msg_icon:ljsType_object/name:ljsType_string","info");
	ljs_add_string(body,"1:ljsType_object/paragraph:ljsType_object/text:ljsType_string","Machine defect");
	ljs_add_string(body,"1:ljsType_object/paragraph:ljsType_object/blink:ljsType_string","no");
	ljs_add_string(body,"1:ljsType_object/paragraph:ljsType_object/underline:ljsType_string","no");
	ljs_add_string(body,"1:ljsType_object/paragraph:ljsType_object/bold:ljsType_string","yes");
	ljs_add_string(body,"1:ljsType_object/paragraph:ljsType_object/align:ljsType_string","left");

	ljs *reply=NULL; 
	ljs_read_array(template,"payload:ljsType_object/msg:ljsType_object/reply_options:ljsType_array",&reply);
	ljs_add_string(reply,"0:ljsType_object/option_id:ljsType_string","1234534354");
	ljs_add_string(reply,"0:ljsType_object/reply:ljsType_object/text:ljsType_string","Accept");
	ljs_add_string(reply,"1:ljsType_object/option_id:ljsType_string","5623432423");
	ljs_add_string(reply,"1:ljsType_object/reply:ljsType_object/text:	","Reject");
    return template;
}
// mosquitto_pub -u as1 --psk-identity as1 --psk 123456789012345678901234567890ab -t "as1/service1/xxl/api/req/status" -m '{"msgId": "gen_1","params":{}}' -p 8884 -h 192.168.178.89
static void msg_send(ljs* ljs_out)
{
    char temp[1024];

    char *out=ljs_print_malloc(ljs_out);
    if(out)
    {
        sprintf(temp, "mosquitto_pub -u as1 --psk-identity as1 --psk 123456789012345678901234567890ab -t \'%s\' -m \'%s\' -p 8884 -h 192.168.178.89", "as1/msg/xxl/msgsrv/req/setMsg", out);
        printf("temp=%s\n",temp);
        int status = system(temp);
        printf("status=%d msg %s\n",status,out);
        printf("\n");
        free(out);
    }
}

int main(void)
{
    int idx=0;
    int hs_idx=0;
    ljs *js=NULL;
    char msgid[100];
    int prio=11;
    char prioStr[10];

    while(1)
    {
        js=msg_hs_template();  // create template
        if(js) 
        {
            // modify msg id, ipui and ms msg id
            sprintf(msgid,"msg_%d",idx);
            ljs_add_string(js,"msgId:ljsType_string",msgid);   
            ljs_add_string(js,"payload:ljsType_object/sip_id:ljsType_string",hs_array[hs_idx].id);
            sprintf(msgid,"%s_%d",hs_array[hs_idx].id,idx);
            ljs_add_string(js,"payload:ljsType_object/amsgId:ljsType_string",msgid);
            ljs_add_string(js,"payload:ljsType_object/msg:ljsType_object/body:ljsType_array/1:ljsType_object/paragraph:ljsType_object/text:ljsType_string",msgid);
            sprintf(prioStr,"%d",prio);
            ljs_add_string(js,"payload:ljsType_object/msg:ljsType_object/prio:ljsType_string",prioStr);
            prio--; prio=prio%11;
            msg_send(js);
        }
        sleep(10);
        idx++;
        hs_idx++;
        if(hs_idx>=number_of_hs)
        {
            hs_idx=0;
        }
        if(idx>=1000)
        {
            idx=0;
        }

    }
}