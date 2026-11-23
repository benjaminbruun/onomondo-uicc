ss_add_test(pin_test LIBS uicc milenage crypto storage $<$<TARGET_EXISTS:utils>:utils> FILES)
