/* 
   Copyright (C) 2013 Ronnie Sahlberg <ronniesahlberg@gmail.com>
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#include <CUnit/CUnit.h>

#include "iscsi.h"
#include "scsi-lowlevel.h"
#include "iscsi-support.h"
#include "iscsi-test-cu.h"


void
test_verify12_flags(void)
{
	int ret;
	unsigned char *buf = alloca(block_size);

	logging(LOG_VERBOSE, LOG_BLANK_LINE);
	logging(LOG_VERBOSE, "Test VERIFY12 flags");

	ret = read12(sd, 0, block_size,
		     block_size, 0, 0, 0, 0, 0, buf,
		     EXPECT_STATUS_GOOD);
	CU_ASSERT_EQUAL(ret, 0);


	logging(LOG_VERBOSE, "Test VERIFY12 with BYTCHK==1");
	ret = verify12(sd, 0, block_size,
		       block_size, 0, 0, 1, buf,
		       EXPECT_STATUS_GOOD);
	if (ret == -2) {
		logging(LOG_NORMAL, "[SKIPPED] VERIFY12 is not implemented.");
		CU_PASS("[SKIPPED] Target does not support VERIFY12. Skipping test");
		return;
	}
	CU_ASSERT_EQUAL(ret, 0);
}
