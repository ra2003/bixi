/*
 * "Bixi" - Basic types management C89 library
 *
 *  Copyright (C) Alexey Shishkin 2017
 *
 *  This file is part of Project "Bixi".
 *
 *  Project "Bixi" is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Project "Bixi" is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Project "Bixi". If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <libbixi.h>
#include "../test.h"
#include "../hashes/tst_bxiuuid.h"

static void test_hashes_defines(void)
{
    printf("    defines:\n");

    TEST_BXI_MACRO_EXISTS(UUID_SIZE);
    TEST_BXI_MACRO_EXISTS(UUID_STR_SIZE);
}

static void test_hashes_uuid2str(void)
{
    char buffer[50];
    uuid_t bf = { 0x99, 0xbd, 0xd9, 0x12, 0x41, 0xcd, 0x40, 0x72,
                  0xa9, 0x65, 0x17, 0x44, 0x7b, 0x2f, 0xd1, 0x89 };

    printf("        checking: uuid2str\n");

    uuid2str(bf, buffer, UUID_HYPHEN);
    if (bxi_strcmp(buffer, "99bdd912-41cd-4072-a965-17447b2fd189"))
        test_failed();
}

static void test_hashes_uuidv3(void)
{
    char buffer[50];
    uuid_t res;
    uuid_t ns = { 0x99, 0xbd, 0xd9, 0x12, 0x41, 0xcd, 0x40, 0x72,
                  0xa9, 0x65, 0x17, 0x44, 0x7b, 0x2f, 0xd1, 0x89 };

    printf("        checking: uuidv3 -  ");

    uuidv3(res, ns, "Some random string");
    uuid2str(res, buffer, UUID_HYPHEN);

    printf("%s\n", buffer);
    if (bxi_strcmp(buffer, "fa0d83ce-44b3-3ee9-9e0b-277cf025bb5f"))
        test_failed();
}

static void test_hashes_uuidv4(void)
{
    char buffer[50];
    uuid_t res;

    printf("        checking: uuidv4 - ");

    uuidv4(res);
    uuid2str(res, buffer, UUID_CURLY);

    printf("%s\n", buffer);
}

static void test_hashes_uuidscmp(void)
{
    uuid_t cm1 = { 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
                   0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00 };
    uuid_t cm2 = { 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
                   0x77, 0x66, 0x55, 0x44, 0x00, 0x00, 0x00, 0x00 };

    printf("        checking: uuidscmp\n");

    if (uuidscmp(cm1, cm2) == 0)
        test_failed();
}

static void test_hashes_functions(void)
{
    printf("    functions:\n");
    test_hashes_uuid2str();
    test_hashes_uuidv3();
    test_hashes_uuidv4();
    test_hashes_uuidscmp();
}

void test_hashes_bxiuuid(void)
{

    print_info;
    test_hashes_defines();
    test_hashes_functions();

    print_passed();
}
