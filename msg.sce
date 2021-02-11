// Commands, syntax:
// STATUS:    = get status message
// S_MSG:     = setMsg <sip_id>|<a_msg_id>|<prio>|<ttl>|text|
// D_MSG:     = delMsg <sip_id>|<a_msg_id>
// POS_BLE:   = ble position req <sip_id>
// POS_BLE:   = dect position req <sip_id>
// WAIT:      = sleep <seconds>
// RESTART:   = start again   
// END:       = end scenrio here
// 
POS_BLE:4021|
END:
//
//
S_MSG:4021|4021_2|9|60|<=Prio9 _2=>|
WAIT:1
S_MSG:4021|4021_3|9|60|<=Prio9 _3=>|
WAIT:1
S_MSG:4021|4021_4|9|60|<=Prio9 _3=>|
END:
S_MSG:4021|4020_2|8|10|<=2=>|
WAIT:10
S_MSG:4021|4021_3|7|60|<=3=>|
WAIT:10
S_MSG:4021|4021_4|6|60|<=4=>|
WAIT:10
S_MSG:4021|4021_5|5|60|<=5=>|
WAIT:10
S_MSG:4021|4021_6|4|60|<=6=>|
WAIT:10
S_MSG:4021|4021_7|3|60|<=7=>|
WAIT:10
S_MSG:4021|4021_8|2|60|<=8=>|
WAIT:10
S_MSG:4021|4021_9|1|60|<=9=>|
WAIT:10
S_MSG:4021|4021_10|9|60|<=10=>|
WAIT:180
RESTART:

