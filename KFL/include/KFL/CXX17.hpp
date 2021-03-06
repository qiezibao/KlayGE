/**
 * @file CXX17.hpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of KFL, a subproject of KlayGE
 * For the latest info, see http://www.klayge.org
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may alternatively use this source under the terms of
 * the KlayGE Proprietary License (KPL). You can obtained such a license
 * from http://www.klayge.org/licensing/.
 */

#ifndef _KFL_CXX17_HPP
#define _KFL_CXX17_HPP

#pragma once

#ifdef KLAYGE_CXX17_CORE_IF_CONSTEXPR_SUPPORT
	#define KLAYGE_IF_CONSTEXPR(x) if constexpr (x)
#else
	#ifdef KLAYGE_COMPILER_MSVC
	#pragma warning(disable: 4127)
	#endif
	#define KLAYGE_IF_CONSTEXPR(x) if (x)
#endif

#ifdef KLAYGE_CXX17_CORE_STATIC_ASSERT_V2_SUPPORT
	#define KLAYGE_STATIC_ASSERT(x) static_assert(x)
#else
	#define KLAYGE_STATIC_ASSERT(x) static_assert(x, #x)
#endif

#endif		// _KFL_CXX17_HPP
