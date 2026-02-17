// Aligned memory buffer -*- C++ -*-

// Copyright (C) 2013-2026 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file ext/aligned_buffer.h
 *  This file is a GNU extension to the Standard C++ Library.
 */

#ifndef _ALIGNED_BUFFER_H
#define _ALIGNED_BUFFER_H 1

#ifdef _GLIBCXX_SYSHDR
#pragma GCC system_header
#endif

#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <bits/c++0x_warning.h>
#endif

namespace __gnu_cxx
{
  // A utility type containing a POD object that can hold an object of type
  // _Tp initialized via placement new or allocator_traits::construct.
  // Intended for use as a data member subobject, use __aligned_buffer for
  // complete objects.
  template<typename _Tp>
    struct __aligned_membuf
    {
      union {
	char c = '\0';
	_Tp _M_storage;
      };

      _GLIBCXX26_CONSTEXPR
      __aligned_membuf() {}

      // Can be used to avoid value-initialization zeroing _M_storage.
      _GLIBCXX26_CONSTEXPR
      __aligned_membuf(std::nullptr_t) { }

      _GLIBCXX26_CONSTEXPR
      ~__aligned_membuf() {}

      _GLIBCXX26_CONSTEXPR
      void*
      _M_addr() noexcept
      { return static_cast<void*>(&_M_storage); }

      _GLIBCXX26_CONSTEXPR
      const void*
      _M_addr() const noexcept
      { return static_cast<const void*>(&_M_storage); }

      _GLIBCXX26_CONSTEXPR
      _Tp*
      _M_ptr() noexcept
      { return &_M_storage; }

      _GLIBCXX26_CONSTEXPR
      const _Tp*
      _M_ptr() const noexcept
      { return &_M_storage; }
    };

#if _GLIBCXX_INLINE_VERSION
  template<typename _Tp>
    using __aligned_buffer = __aligned_membuf<_Tp>;
#else
  // Similar to __aligned_membuf but aligned for complete objects, not members.
  // This type is used in <forward_list>, <future>, <bits/shared_ptr_base.h>
  // and <bits/hashtable_policy.h>, but ideally they would use __aligned_membuf
  // instead, as it has smaller size for some types on some targets.
  // This type is still used to avoid an ABI change.
  template<typename _Tp>
    struct __aligned_buffer
    {
      union {
	char c = '\0';
	_Tp _M_storage;
      };

      _GLIBCXX26_CONSTEXPR
      __aligned_buffer() {}

      // Can be used to avoid value-initialization
      _GLIBCXX26_CONSTEXPR
      __aligned_buffer(std::nullptr_t) { }

      _GLIBCXX26_CONSTEXPR
      ~__aligned_buffer() {}
      
      _GLIBCXX26_CONSTEXPR
      void*
      _M_addr() noexcept
      {
        return static_cast<void*>(&_M_storage);
      }

      _GLIBCXX26_CONSTEXPR
      const void*
      _M_addr() const noexcept
      {
        return static_cast<const void*>(&_M_storage);
      }

      _GLIBCXX26_CONSTEXPR
      _Tp*
      _M_ptr() noexcept
      { return &_M_storage; }

      _GLIBCXX26_CONSTEXPR
      const _Tp*
      _M_ptr() const noexcept
      { return &_M_storage; }
    };
#endif

} // namespace

#endif /* _ALIGNED_BUFFER_H */
