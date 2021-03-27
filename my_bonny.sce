// Commands, syntax:
// STATUS:     = get status message
// S_MSG:      = setMsg <sip_id>|<a_msg_id>|<prio>|<ttl>|text|
// S_MSG_FILE: = setMsg <sip_id>|<a_msg_id>|<file>|  setMsg from <file>
// D_MSG:      = delMsg <sip_id>|<a_msg_id>
// POS_BLE:    = ble position req <sip_id>
// POS_BLE:    = dect position req <sip_id>
// WAIT:       = sleep <seconds>
// RESTART:    = start script again   
// END:        = end scenrio here
// 
// 
//
// Send "my bonny is over ...." message to HS wait 10 seconds and delete message.
// Same for next HSs.
// HSs: 4021 4020 4013 4004 4011 4015
// Loop
// 
//
//
//
//
//
WAIT: 1
STATUS:
WAIT: 1
// next 4021
S_MSG_FILE:4021|4021_1|tst_msg_my_bonny.json|
WAIT: 10
D_MSG:4021|4021_1|
WAIT: 10
// next 4020
S_MSG_FILE:4020|4020_1|tst_msg_my_bonny.json|
WAIT: 10
D_MSG:4020|4020_1|
WAIT: 10
// next 4013
S_MSG_FILE:4013|4013_1|tst_msg_my_bonny.json|
WAIT: 10
D_MSG:4013|4013_1|
WAIT: 10
// next 4004
S_MSG_FILE:4004|4004_1|tst_msg_my_bonny.json|
WAIT: 10
D_MSG:4004|4004_1|
WAIT: 10
// next 4011
S_MSG_FILE:4011|4011_1|tst_msg_my_bonny.json|
WAIT: 10
D_MSG:4011|4011_1|
WAIT: 10
// next 4015
S_MSG_FILE:4015|4015_1|tst_msg_my_bonny.json|
WAIT: 10
D_MSG:4015|4015_1|
WAIT: 10
RESTART:

