/*
 * Author: Philipp Maier
 *
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <onomondo/softsim/log.h>
#include <onomondo/softsim/mem.h>
#include <onomondo/softsim/utils.h>
#include "src/softsim/uicc/tlv8.h"

static const uint8_t sample[] = { 0x81, 0x03, 0x01, 0x21, 0x00, 0x82, 0x02, 0x81, 0x02, 0x8d,
				  0x0c, 0x04, 'H',  'E',  'L',	'L',  'O',  ',',  'W',	'O',
				  'R',	'L',  'D',  0xc8, 0x04, 0x01, 0x02, 0x03, 0x04 };

static size_t count_ies(const struct ss_list *list)
{
	const struct tlv8_ie *ie;
	size_t n = 0;

	SS_LIST_FOR_EACH(list, ie, struct tlv8_ie, list) {
		n++;
	}
	return n;
}

/* Assert that list holds an IE with the given tag and exactly this value. */
static void check_ie(const struct ss_list *list, uint8_t tag, const char *value, size_t len)
{
	const struct tlv8_ie *ie = ss_tlv8_get_ie(list, tag);

	assert(ie);
	assert(ie->value);
	assert(ie->value->len == len);
	assert(memcmp(ie->value->data, value, len) == 0);
}

static void check_sample_ies(const struct ss_list *list)
{
	assert(list);
	assert(count_ies(list) == 4);
	check_ie(list, 0x81, "\x01\x21\x00", 3);
	check_ie(list, 0x82, "\x81\x02", 2);
	check_ie(list, 0x8d, "\x04HELLO,WORLD", 12);
	check_ie(list, 0xc8, "\x01\x02\x03\x04", 4);
}

static void ss_tlv8_decode_test(void)
{
	struct ss_list *decoded;

	fprintf(stderr, "\nTEST: decode a TLV8 encoded string\n");
	fprintf(stderr, "encoded input:  %s\n", ss_hexdump(sample, sizeof(sample)));

	fprintf(stderr, "decoded output:\n");
	decoded = ss_tlv8_decode(sample, sizeof(sample));
	ss_tlv8_dump(decoded, 0, STLV8, LDEBUG);
	check_sample_ies(decoded);
	ss_tlv8_free(decoded);
}

static void ss_tlv8_encode_test(void)
{
	struct ss_list *decoded;
	uint8_t encoded[1024];
	size_t rc;

	/* Set up TLV8 list */
	decoded = SS_ALLOC(struct ss_list);
	ss_list_init(decoded);

	ss_tlv8_new_ie(decoded, 0x81, 3, (uint8_t *)"\x01\x21\x00");
	ss_tlv8_new_ie(decoded, 0x82, 2, (uint8_t *)"\x81\x02");
	ss_tlv8_new_ie(decoded, 0x8d, 12, (uint8_t *)"\x04\x48\x45\x4c\x4c\x4f\x2c\x57\x4f\x52\x4c\x44");
	ss_tlv8_new_ie(decoded, 0xc8, 4, (uint8_t *)"\x01\x02\x03\x04");

	fprintf(stderr, "\nTEST: encode a binary TLV8 encoded string from decoded list\n");
	fprintf(stderr, "TLV8 data to be encoded:\n");
	ss_tlv8_dump(decoded, 2, STLV8, LDEBUG);
	rc = ss_tlv8_encode(encoded, sizeof(encoded), decoded);
	fprintf(stderr, "expected result: %s\n", ss_hexdump(sample, sizeof(sample)));
	fprintf(stderr, "encoded result:  %s\n", ss_hexdump(encoded, rc));
	assert(rc == sizeof(sample));
	assert(memcmp(encoded, sample, sizeof(sample)) == 0);
	ss_tlv8_free(decoded);
}

/* Decoding and re-encoding must reproduce the input exactly. */
static void ss_tlv8_roundtrip_test(void)
{
	struct ss_list *decoded;
	uint8_t encoded[1024];
	size_t rc;

	fprintf(stderr, "\nTEST: decode and re-encode a TLV8 encoded string\n");
	decoded = ss_tlv8_decode(sample, sizeof(sample));
	assert(decoded);
	rc = ss_tlv8_encode(encoded, sizeof(encoded), decoded);
	fprintf(stderr, "re-encoded result: %s\n", ss_hexdump(encoded, rc));
	assert(rc == sizeof(sample));
	assert(memcmp(encoded, sample, sizeof(sample)) == 0);
	ss_tlv8_free(decoded);
}

int main(int argc, char **argv)
{
	ss_tlv8_decode_test();
	ss_tlv8_encode_test();
	ss_tlv8_roundtrip_test();
	return 0;
}
