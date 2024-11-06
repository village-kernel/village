//###########################################################################
// vk_cast.h
// Declarations of the cast
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_CAST_H__
#define __VK_CAST_H__

#include "stdint.h"
#include "stddef.h"
#include "stdlib.h"


/// @brief Get method address
/// @tparam dst_type 
/// @tparam src_type 
/// @param src 
/// @return addr 
template<typename dst_type, typename src_type>
dst_type pointer_cast(src_type src)
{
	return *static_cast<dst_type*>(static_cast<void*>(&src));
}


/// @brief Get method address
/// @tparam dst_type 
/// @tparam src_type 
/// @param src 
/// @return addr 
template<typename dst_type, typename src_type>
dst_type union_cast(src_type src)
{
	union{ src_type s; dst_type d; } u;
	u.s = src;
	return u.d;
}

#endif //!__VK_CAST_H__
