#!/usr/bin/env python3

import os

# print("\nFormatting demos")
os.system('astyle --options=code-format.cfg --recursive "../program/*.c,*.h"')
