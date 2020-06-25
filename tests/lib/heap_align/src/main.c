/*
 * Copyright (c) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr.h>
#include <ztest.h>
#include <sys/sys_heap.h>

#define HEAP_SZ 0x1000

uint8_t __aligned(8) heapmem[HEAP_SZ];

/* Heap metadata sizes */
uint8_t *heap_start, *heap_end;

/* Note that this test is making whitebox assumptions about the
 * behavior of the heap in order to exercise coverage of the
 * underlying code: that chunk headers are 8 bytes, that heap chunks
 * are returned low-adddress to high, and that freed blocks are merged
 * immediately with adjacent free blocks.
 */
static void check_heap_align(struct sys_heap *h,
			     size_t prefix, size_t align, size_t size)
{
	void *p, *q, *r, *s;

	p = sys_heap_alloc(h, prefix);
	zassert_true(prefix == 0 || p != NULL, "prefix allocation failed");

	q = sys_heap_aligned_alloc(h, align, size);
	zassert_true(q != NULL, "first aligned allocation failed");
	zassert_true((((uintptr_t)q) & (align - 1)) == 0, "block not aligned");

	r = sys_heap_aligned_alloc(h, align, size);
	zassert_true(r != NULL, "second aligned allocation failed");
	zassert_true((((uintptr_t)r) & (align - 1)) == 0, "block not aligned");

	/* Make sure ALL the split memory goes back into the heap and
	 * we can allocate the full remaining suffix
	 */
	s = sys_heap_alloc(h, (heap_end - (uint8_t *)r) - size - 8);
	zassert_true(s != NULL, "suffix allocation failed (%zd/%zd/%zd)",
				prefix, align, size);

	sys_heap_free(h, p);
	sys_heap_free(h, q);
	sys_heap_free(h, r);
	sys_heap_free(h, s);

	/* Make sure it's still valid, and empty */
	zassert_true(sys_heap_validate(h), "heap invalid");
	p = sys_heap_alloc(h, heap_end - heap_start);
	zassert_true(p != NULL, "heap not empty");
	q = sys_heap_alloc(h, 1);
	zassert_true(q == NULL, "heap not full");
	sys_heap_free(h, p);
}

static void test_aligned_alloc(void)
{
	struct sys_heap heap = {};
	void *p;

	sys_heap_init(&heap, heapmem, HEAP_SZ);

	p = sys_heap_alloc(&heap, 1);
	zassert_true(p != NULL, "initial alloc failed");
	sys_heap_free(&heap, p);

	/* Heap starts where that first chunk was, and ends one 8-byte
	 * chunk header before the end of its memory
	 */
	heap_start = p;
	heap_end = heapmem + HEAP_SZ - 8;

	for (size_t align = 8; align < HEAP_SZ / 4; align *= 2) {
		for (size_t prefix = 0; prefix <= align; prefix += 8) {
			for (size_t size = 8; size <= align; size += 8) {
				check_heap_align(&heap, prefix, align, size);
			}
		}
	}
}

void test_main(void)
{
	ztest_test_suite(lib_heap_align_test,
			 ztest_unit_test(test_aligned_alloc));

	ztest_run_test_suite(lib_heap_align_test);
}
