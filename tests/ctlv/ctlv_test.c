/*
 * Copyright (c) 2024 Onomondo ApS. All rights reserved.
 *
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * Author: Philipp Maier
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <onomondo/softsim/log.h>
#include <onomondo/softsim/mem.h>
#include <onomondo/softsim/utils.h>
#include "src/softsim/uicc/ctlv.h"

static const uint8_t sample[] = { 0x81, 0x03, 0x01, 0x21, 0x00, 0x82, 0x02, 0x81, 0x02, 0x8d,
				  0x0c, 0x04, 'H',  'E',  'L',	'L',  'O',  ',',  'W',	'O',
				  'R',	'L',  'D',  0xc8, 0x04, 0x01, 0x02, 0x03, 0x04 };

static size_t count_ies(const struct ss_list *list)
{
	const struct cmp_tlv_ie *ie;
	size_t n = 0;

	SS_LIST_FOR_EACH(list, ie, struct cmp_tlv_ie, list) {
		n++;
	}
	return n;
}

/* Assert that list holds an IE with the given tag (without the CR bit), the
 * comprehension required flag set, and exactly this value. */
static void check_ie(const struct ss_list *list, uint16_t tag, const char *value, size_t len)
{
	const struct cmp_tlv_ie *ie = ss_ctlv_get_ie(list, tag);

	assert(ie);
	assert(ie->cr);
	assert(ie->value);
	assert(ie->value->len == len);
	assert(memcmp(ie->value->data, value, len) == 0);
}

static void check_sample_ies(const struct ss_list *list)
{
	assert(list);
	assert(count_ies(list) == 4);
	check_ie(list, 0x01, "\x01\x21\x00", 3);
	check_ie(list, 0x02, "\x81\x02", 2);
	check_ie(list, 0x0d, "\x04HELLO,WORLD", 12);
	check_ie(list, 0x48, "\x01\x02\x03\x04", 4);
}

static void ss_ctlv_decode_test(void)
{
	struct ss_list *decoded;

	fprintf(stderr, "\nTEST: decode a COMPREHENSION-TLV encoded string\n");
	fprintf(stderr, "encoded input:  %s\n", ss_hexdump(sample, sizeof(sample)));

	fprintf(stderr, "decoded output:\n");
	decoded = ss_ctlv_decode(sample, sizeof(sample));
	ss_ctlv_dump(decoded, 0, SCTLV, LDEBUG);
	check_sample_ies(decoded);
	ss_ctlv_free(decoded);
}

static void ss_ctlv_encode_test(void)
{
	struct ss_list *decoded;
	uint8_t encoded[1024];
	size_t rc;

	/* Set up COMPREHENSION-TLV list */
	decoded = SS_ALLOC(struct ss_list);
	ss_list_init(decoded);

	ss_ctlv_new_ie(decoded, 0x01, true, 3, (uint8_t *)"\x01\x21\x00");
	ss_ctlv_new_ie(decoded, 0x02, true, 2, (uint8_t *)"\x81\x02");
	ss_ctlv_new_ie(decoded, 0x0d, true, 12, (uint8_t *)"\x04\x48\x45\x4c\x4c\x4f\x2c\x57\x4f\x52\x4c\x44");
	ss_ctlv_new_ie(decoded, 0x48, true, 4, (uint8_t *)"\x01\x02\x03\x04");

	fprintf(stderr, "\nTEST: encode a binary COMPREHENSION-TLV encoded string from decoded list\n");
	fprintf(stderr, "COMPREHENSION-TLV data to be encoded:\n");
	ss_ctlv_dump(decoded, 2, SCTLV, LDEBUG);
	rc = ss_ctlv_encode(encoded, sizeof(encoded), decoded);
	fprintf(stderr, "expected result: %s\n", ss_hexdump(sample, sizeof(sample)));
	fprintf(stderr, "encoded result:  %s\n", ss_hexdump(encoded, rc));
	assert(rc == sizeof(sample));
	assert(memcmp(encoded, sample, sizeof(sample)) == 0);
	ss_ctlv_free(decoded);
}

/* Decoding and re-encoding must reproduce the input exactly. */
static void ss_ctlv_roundtrip_test(void)
{
	struct ss_list *decoded;
	uint8_t encoded[1024];
	size_t rc;

	fprintf(stderr, "\nTEST: decode and re-encode a COMPREHENSION-TLV encoded string\n");
	decoded = ss_ctlv_decode(sample, sizeof(sample));
	assert(decoded);
	rc = ss_ctlv_encode(encoded, sizeof(encoded), decoded);
	fprintf(stderr, "re-encoded result: %s\n", ss_hexdump(encoded, rc));
	assert(rc == sizeof(sample));
	assert(memcmp(encoded, sample, sizeof(sample)) == 0);
	ss_ctlv_free(decoded);
}

int main(int argc, char **argv)
{
	ss_ctlv_decode_test();
	ss_ctlv_encode_test();
	ss_ctlv_roundtrip_test();
	return 0;
}
