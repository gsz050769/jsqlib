// Commands, syntax:
// STATUS:     = get status message
// S_MSG:      = setMsg <sip_id>|<a_msg_id>|<prio>|<ttl>|text|
// S_MSG_FILE: = setMsg <sip_id>|<a_msg_id>|<file>|  setMsg from <file>
// D_MSG:      = delMsg <sip_id>|<a_msg_id>
// POS_BLE:    = ble position req <sip_id>|
// POS_DECT:   = dect position req <sip_id>|
// WAIT:       = sleep <seconds>
// RESTART:    = start script again   
// END:        = end scenrio here
// 
// 
WAIT: 1
STATUS:
WAIT: 1
S_MSG_FILE:4021|4021_1|tst_msg_position.json|
WAIT: 1
POS_DECT:4021|
WAIT: 100
END:
