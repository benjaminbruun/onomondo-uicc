# Copyright (c) 2024 Onomondo ApS. All rights reserved.
# SPDX-License-Identifier: GPL-3.0-only

# Passes on exit code alone. tlv8_test.err is what the test logs to stderr; it is
# not compared.
ss_add_test(tlv8_test LIBS uicc NO_REFERENCE)
