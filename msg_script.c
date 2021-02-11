#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h> 
#include <stdlib.h> 
#include <string.h>

#include "libjson.h"


#define number_of_hs ((sizeof(hs_array))/(sizeof(hs)))

static ljs*  msg_hs_template_set_msg(void)
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

static ljs*  msg_hs_template_del_msg(void)
{
    ljs * template = NULL;

	template = ljs_init();
	ljs_add_string(template,"msgId:ljsType_string","xxxxx");
    ljs_add_string(template,"payload:ljsType_object/amsgId:ljsType_string","xxxxxxxxx");
	ljs_add_string(template,"payload:ljsType_object/sip_id:ljsType_string","xxxxx");
    return template;
}

static int idx=0;
static void msg_hs_mod(ljs* js,int idx ,char *sipid,char *msgid,char *text,char *prio,char *ttl)
{
    char msg_idx[40];
    idx=idx%10000;
    sprintf(msg_idx,"%d",idx);
    ljs_add_string(js,"msgId:ljsType_string",msg_idx);
    ljs_add_string(js,"payload:ljsType_object/sip_id:ljsType_string",sipid);
    ljs_add_string(js,"payload:ljsType_object/amsgId:ljsType_string",msgid);
    if(prio){ljs_add_string(js,"payload:ljsType_object/msg:ljsType_object/prio:ljsType_string",prio);}
    if(ttl){ljs_add_string(js,"payload:ljsType_object/msg:ljsType_object/ttl:ljsType_string",ttl);}
    if(text)
    {
        ljs_add_string(js,"payload:ljsType_object/msg:ljsType_object/title:ljsType_object/text:ljsType_string",text);
        ljs_add_string(js,"payload:ljsType_object/msg:ljsType_object/body:ljsType_array/1:ljsType_object/paragraph:ljsType_object/text:ljsType_string",text);
    }
}

// mosquitto_pub -u as1 --psk-identity as1 --psk 123456789012345678901234567890ab -t "as1/service1/xxl/api/req/status" -m '{"msgId": "gen_1","params":{}}' -p 8884 -h 192.168.178.89
static void msg_send(ljs* ljs_out, char *topic)
{
    char temp[1024];

    char *out=ljs_print_malloc(ljs_out);
    if(out)
    {
        sprintf(temp, "mosquitto_pub -u as1 --psk-identity as1 --psk 123456789012345678901234567890ab -t \'%s\' -m \'%s\' -p 8884 -h 192.168.178.89", topic, out);
        printf("command=%s\n",temp);
        int status = system(temp);
        printf("status=%d\n",status);
        printf("##########################################################################\n");
        free(out);
    }
    ljs_free(ljs_out);
}

// mosquitto_pub -t 'as1/general/xxl/api/req/status' -m '{"msgId": "gen_1","params":{}}'
static void status_send(void)
{
    ljs * js = NULL;
    char *out=NULL;
    char temp[1024];

	js = ljs_init();
	ljs_add_string(js,"msgId:ljsType_string","4711");
    ljs_add_object(js, "params:ljsType_object",NULL);
    out=ljs_print_malloc(js);
    if(out)
    {
        sprintf(temp, "mosquitto_pub -u as1 --psk-identity as1 --psk 123456789012345678901234567890ab -t \'%s\' -m \'%s\' -p 8884 -h 192.168.178.89", "as1/general/xxl/api/req/status", out);
        printf("command = %s\n",temp);
        int status = system(temp);
        printf("status=%d\n",status);
        printf("##########################################################################\n");
        free(out);
    }
    ljs_free(js);
}


static void pos_dect_send(char *token, int idxx)
{
    char * sipid=NULL;
    char msg_idx[40];
    idx=idx%10000;
    sprintf(msg_idx,"%d",idx);
    ljs* js=NULL;
    char *out=NULL;
    char temp[1024];
    char topic[200];

    
    if (token && (sipid=strtok(token,"|")))
    {
        js = ljs_init();
        ljs_add_string(js,"msgId:ljsType_string",msg_idx);
        ljs_add_string(js,"params:ljsType_object/sip_id:ljsType_string",sipid);
        ljs_add_string(js,"params:ljsType_object/mode:ljsType_string","dps");
        out=ljs_print_malloc(js);
        sprintf(topic,"as1/service2/sip_id/%s/req/position",sipid);
        sprintf(temp, "mosquitto_pub -u as1 --psk-identity as1 --psk 123456789012345678901234567890ab -t \'%s\' -m \'%s\' -p 8884 -h 192.168.178.89", topic, out);
        printf("command = %s\n",temp);
        int status = system(temp);
        printf("status=%d\n",status);
        printf("##########################################################################\n");
        free(out);
        ljs_free(js);
    }

}


 
static void pos_ble_send(char *token, int idx)
{
    char * sipid=NULL;
    char msg_idx[40];
    idx=idx%10000;
    sprintf(msg_idx,"%d",idx);
    ljs* js=NULL;
    char *out=NULL;
    char temp[1024];
    char topic[200];

    
    if (token && (sipid=strtok(token,"|")))
    {
        js = ljs_init();
        ljs_add_string(js,"msgId:ljsType_string",msg_idx);
        ljs_add_string(js,"params:ljsType_object/sip_id:ljsType_string",sipid);
        ljs_add_string(js,"params:ljsType_object/mode:ljsType_string","ble");
        ljs_add_array(js,"params:ljsType_object/company_ids:ljsType_array",NULL);
        ljs_add_string(js,"params:ljsType_object/timeout:ljsType_string","5");
        ljs_add_string(js,"params:ljsType_object/max_beacons:ljsType_string","4");
        ljs_add_string(js,"params:ljsType_object/req_info:ljsType_string","0F");
        out=ljs_print_malloc(js);
        sprintf(topic,"as1/service2/sip_id/%s/req/position",sipid);
        sprintf(temp, "mosquitto_pub -u as1 --psk-identity as1 --psk 123456789012345678901234567890ab -t \'%s\' -m \'%s\' -p 8884 -h 192.168.178.89", topic, out);
        printf("command = %s\n",temp);
        int status = system(temp);
        printf("status=%d\n",status);
        printf("##########################################################################\n");
        free(out);
        ljs_free(js);
    }
    
}

int main(int argc, const char *argv[])
{
    ljs *js=NULL;
    const char * sce_input_file;
    FILE *file = NULL;
    char line[255];
    char * token=NULL;
    char * sipid=token;
    char * ammsgid=NULL;
    char * prio=NULL;
    char * ttl=NULL;
    char * text=NULL;
    int    msgidx=0;


        /* get address (argv[1] if present) */
    if (argc > 1) {
        sce_input_file = argv[1];
    } else {
        sce_input_file = "msg.sce";
    }

    file = fopen(sce_input_file, "r");
    if(!file)
    {
        printf("unable to open file %s\n",sce_input_file);
        return -1;
    }
    printf("message scenario started with scenario input file=%s\n",sce_input_file);

    
    while (fgets(line, sizeof(line), file)) {
        token = strtok(line, ":");
        if (token && (strcmp(token,"S_MSG")==0))
        {
            token=strtok(NULL,":");
            printf("S_MSG: %s",token?token:"");
            if (token && (sipid=strtok(token,"|")))
            {
                
                if (ammsgid=strtok(NULL,"|"))
                {
                     if (prio=strtok(NULL,"|"))
                     {
                        if (ttl=strtok(NULL,"|"))
                        {
                            text=strtok(NULL,"|");
                            js=msg_hs_template_set_msg();
                            msg_hs_mod(js,msgidx,sipid,ammsgid,text,prio,ttl);
                            msg_send(js,"as1/msg/xxl/msgsrv/req/setMsg");
                            msgidx++;
                        }
                     }
                }
            }
            continue;
        }
        if (token && (strcmp(token,"D_MSG")==0))
        {
            token=strtok(NULL,":");
            printf("D_MSG: %s",token?token:"");
            if (token && (sipid=strtok(token,"|")))
            {
                
                if (ammsgid=strtok(NULL,"|"))
                {
                    js=msg_hs_template_del_msg();
                    msg_hs_mod(js,msgidx,sipid,ammsgid,NULL,NULL,NULL);
                    msg_send(js,"as1/msg/xxl/msgsrv/req/delMsg");
                    msgidx++;
                }
            }
            continue;
        }
        if (token && (strcmp(token,"WAIT")==0))
        {
            if(token=strtok(NULL,":"))
            {
                printf("WAIT: %s",token?token:"");
                sleep(atoi(token));
            }
            continue;
        }
        if (token && (strcmp(token,"RESTART")==0))
        {
            printf("RESTART scenario\n");
            rewind(file);
            continue;
        }
        if (token && (strcmp(token,"END")==0))
        {
            printf("END scenario\n");
            break;
        }
        if (token && (strcmp(token,"STATUS")==0))
        {
            status_send();
        }
        if (token && (strcmp(token,"POS_BLE")==0))
        {
            token=strtok(NULL,":");
            pos_ble_send(token,msgidx);
        }
        if (token && (strcmp(token,"POS_DECT")==0))
        {
            token=strtok(NULL,":");
            pos_dect_send(token,msgidx);
        }
    }
    fclose(file);
}