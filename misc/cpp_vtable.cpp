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

/*
 * @file
 * @brief Stub for C++ virtual tables
 */

/**
 *
 * @brief basic virtual tables required for classes to build
 *
 */

namespace __cxxabiv1 {
	class __class_type_info {
		virtual void dummy();
	};
	class __si_class_type_info {
		virtual void dummy();
	};
	void __class_type_info::dummy() { }  // causes the vtable to get created here
	void __si_class_type_info::dummy() { }  // causes the vtable to get created here
};
