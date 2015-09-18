/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _cache__h_
#define _cache__h_

#include <nanokernel.h>

#if defined(CONFIG_CACHE_FLUSHING)
#define _sys_cache_flush_sig(x) void (x)(vaddr_t virt, size_t size)

#if defined(CONFIG_ARCH_CACHE_FLUSH_DETECT)
	typedef _sys_cache_flush_sig(_sys_cache_flush_t);
	extern _sys_cache_flush_t *sys_cache_flush;
#else
	extern _sys_cache_flush_sig(sys_cache_flush);
#endif
#endif /* CACHE_FLUSHING */

#if defined(CONFIG_CACHE_LINE_SIZE_DETECT)
	extern size_t sys_cache_line_size;
#else
	#define sys_cache_line_size CONFIG_CACHE_LINE_SIZE
#endif

#endif /* _cache__h_ */
