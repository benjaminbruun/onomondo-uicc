ss_add_test(suspend_test LIBS uicc milenage crypto storage $<$<TARGET_EXISTS:utils>:utils>
	RUN_IF CONFIG_USE_EXPERIMENTAL_SUSPEND_COMMAND)
