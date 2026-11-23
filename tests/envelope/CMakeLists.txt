# Not run with external key loading: the OTA packet in the test was encrypted
# with the keys stored in files/, and the identity stub used for
# CONFIG_EXTERNAL_KEY_LOAD produces different crypto output.
ss_add_test(envelope_test LIBS uicc milenage crypto storage $<$<TARGET_EXISTS:utils>:utils> FILES
	RUN_IF NOT CONFIG_EXTERNAL_KEY_LOAD)
