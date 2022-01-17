/* Test for decoding SMS on Nokia 6510 driver */

#include <gammu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

#include "../libgammu/protocol/protocol.h"	/* Needed for GSM_Protocol_Message */
#include "../libgammu/gsmstate.h"	/* Needed for state machine internals */

#include "../helper/message-display.h"

unsigned char data[] = {
    0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x9F, 0x00, 0x00, 0x02, 0x90, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B,
    0x00, 0x34, 0x00, 0x38, 0x00, 0x35, 0x00, 0x30, 0x00, 0x35, 0x00, 0x36, 0x00, 0x31, 0x00, 0x34,
    0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x44, 0x0B, 0x91, 0x84, 0x05, 0x65, 0x41, 0x46, 0xF0, 0x00, 0x08, 0x11, 0x20, 0x21, 0x91, 0x43,
    0x03, 0x40, 0x8C, 0x05, 0x00, 0x03, 0x7B, 0x02, 0x01, 0x00, 0x49, 0x00, 0x20, 0x00, 0x74, 0x00,
    0x6F, 0x00, 0x20, 0x00, 0x6A, 0x00, 0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x20, 0x00, 0x64, 0x00,
    0x6F, 0x00, 0x62, 0x00, 0x72, 0x00, 0x61, 0x00, 0x20, 0x00, 0x69, 0x00, 0x20, 0x00, 0x70, 0x00,
    0x65, 0x01, 0x42, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x20, 0x00, 0x6F, 0x00, 0x64, 0x00, 0x70, 0x00,
    0x6F, 0x00, 0x77, 0x00, 0x69, 0x00, 0x65, 0x00, 0x64, 0x01, 0x7A, 0x00, 0x21, 0x00, 0x20, 0x00,
    0x3A, 0x00, 0x29, 0x00, 0x20, 0x00, 0x43, 0x00, 0x6F, 0x00, 0x20, 0x00, 0x74, 0x00, 0x79, 0x00,
    0x20, 0x00, 0x67, 0x00, 0x61, 0x00, 0x64, 0x00, 0x61, 0x00, 0x73, 0x00, 0x7A, 0x00, 0x2C, 0x00,
    0x20, 0x00, 0x6A, 0x00, 0x61, 0x00, 0x6B, 0x00, 0x20, 0x00, 0x6F, 0x00, 0x62, 0x00, 0x63, 0x00,
    0x69, 0x01, 0x05, 0x01, 0x7C, 0x00, 0x61, 0x01, 0x07, 0x00, 0x2E, 0x00, 0x2E, 0x00, 0x20, 0x01,
    0x01, 0x3E, 0x01, 0x00, 0x01, 0x00, 0x08, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x01, 0x00, 0x0B, 0x00,
    0x01, 0x00, 0x0F, 0x00, 0x02, 0x00, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x01, 0x00, 0x2A, 0x00, 0x01, 0x00, 0x2D, 0x00, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x01, 0x00, 0x23, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x26,
    0x00, 0x01, 0x00, 0x03, 0x00, 0xB2, 0x00, 0x49, 0x00, 0x20, 0x00, 0x74, 0x00, 0x6F, 0x00, 0x20,
    0x00, 0x6A, 0x00, 0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x20, 0x00, 0x64, 0x00, 0x6F, 0x00, 0x62,
    0x00, 0x72, 0x00, 0x61, 0x00, 0x20, 0x00, 0x69, 0x00, 0x20, 0x00, 0x70, 0x00, 0x65, 0x01, 0x42,
    0x00, 0x6E, 0x00, 0x61, 0x00, 0x20, 0x00, 0x6F, 0x00, 0x64, 0x00, 0x70, 0x00, 0x6F, 0x00, 0x77,
    0x00, 0x69, 0x00, 0x65, 0x00, 0x64, 0x01, 0x7A, 0x00, 0x21, 0x00, 0x20, 0x00, 0x3A, 0x00, 0x29,
    0x00, 0x20, 0x00, 0x43, 0x00, 0x6F, 0x00, 0x20, 0x00, 0x74, 0x00, 0x79, 0x00, 0x20, 0x00, 0x67,
    0x00, 0x61, 0x00, 0x64, 0x00, 0x61, 0x00, 0x73, 0x00, 0x7A, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x6A,
    0x00, 0x61, 0x00, 0x6B, 0x00, 0x20, 0x00, 0x6F, 0x00, 0x62, 0x00, 0x63, 0x00, 0x69, 0x01, 0x05,
    0x01, 0x7C, 0x00, 0x61, 0x01, 0x07, 0x00, 0x2E, 0x00, 0x2E, 0x00, 0x20, 0x00, 0x50, 0x00, 0x6F,
    0x00, 0x7A, 0x00, 0x64, 0x00, 0x72, 0x00, 0x6F, 0x00, 0x77, 0x00, 0x69, 0x00, 0x65, 0x00, 0x6E,
    0x00, 0x69, 0x00, 0x61, 0x00, 0x20, 0x00, 0x64, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x20, 0x00, 0x4F,
    0x00, 0x6D, 0x00, 0x69, 0x00, 0x21, 0x00, 0x00, 0x02, 0x00, 0x0D, 0x2B, 0x34, 0x38, 0x35, 0x30,
    0x31, 0x32, 0x30, 0x30, 0x37, 0x37, 0x37, 0x00, 0x04, 0x00, 0x01, 0x00, 0x2B, 0x00, 0x1A, 0x00,
    0x2B, 0x00, 0x34, 0x00, 0x38, 0x00, 0x35, 0x00, 0x30, 0x00, 0x35, 0x00, 0x36, 0x00, 0x31, 0x00,
    0x34, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x00, 0x07, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01,
    0x00, 0x12, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x01, 0x00, 0x22, 0x00, 0x01, 0x00,
    0x01, 0x00,

};

const char text[] = "I to jest dobra i pełna odpowiedź! :) Co ty gadasz, jak obciążać.. ";
char decoded_text[200];

/* This is not part of API! */
extern GSM_Error N6510_DecodeFilesystemSMS(GSM_StateMachine * s, GSM_MultiSMSMessage * sms, GSM_File * FFF, int location);

int main(int argc UNUSED, char **argv UNUSED)
{
	GSM_Debug_Info *debug_info;
	GSM_StateMachine *s;
	GSM_File file;
	GSM_Error error;
	GSM_MultiSMSMessage sms;

	/* Init locales for proper output */
	GSM_InitLocales(NULL);

	debug_info = GSM_GetGlobalDebug();
	GSM_SetDebugFileDescriptor(stderr, FALSE, debug_info);
	GSM_SetDebugLevel("textall", debug_info);

	/* Allocates state machine */
	s = GSM_AllocStateMachine();
	test_result(s != NULL);

	debug_info = GSM_GetDebug(s);
	GSM_SetDebugGlobal(TRUE, debug_info);

	/* Init file */
	file.Buffer = malloc(sizeof(data));
	memcpy(file.Buffer, data, sizeof(data));
	file.Used = sizeof(data);
	file.ID_FullName[0] = 0;
	file.ID_FullName[1] = 0;
	GSM_GetCurrentDateTime(&(file.Modified));

	/* Parse it */
	error = N6510_DecodeFilesystemSMS(s, &sms, &file, 0);

	/* Display message */
	DisplayMultiSMSInfo(&sms, FALSE, TRUE, NULL, NULL);
	DisplayMultiSMSInfo(&sms, TRUE, TRUE, NULL, NULL);

	/* Free state machine */
	GSM_FreeStateMachine(s);

	/* Check expected text */
	/* We do not compare full text due to locales problem */
	EncodeUTF8(decoded_text, sms.SMS[0].Text);
	test_result(strcmp(text, decoded_text) == 0);

	gammu_test_result(error, "N6510_DecodeFilesystemSMS");

	return 0;
}

/* Editor configuration
 * vim: noexpandtab sw=8 ts=8 sts=8 tw=72:
 */
