﻿/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	Copyright (c) 2018-2019 As Project
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_RETOUCH_MULTIPLICATION_HPP
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_RETOUCH_MULTIPLICATION_HPP

/*#######################################################################################
	日本語リファレンス (Reference-JP)
	https://github.com/Kasugaccho/DungeonTemplateLibrary/wiki/dtl::retouch::Multiplication-(修正クラス)/
#######################################################################################*/

#include <DTL/Base/Struct.hpp>
#include <DTL/Macros/constexpr.hpp>
#include <DTL/Macros/nodiscard.hpp>
#include <DTL/Type/Forward.hpp>
#include <DTL/Type/SizeT.hpp>
#include <DTL/Range/RectBaseWithValue.hpp>
#include <DTL/Utility/DrawJagged.hpp>

/*#######################################################################################
	[概要] "dtl名前空間"とは"DungeonTemplateLibrary"の全ての機能が含まれる名前空間である。
	[Summary] The "dtl" is a namespace that contains all the functions of "DungeonTemplateLibrary".
#######################################################################################*/
namespace dtl {
	inline namespace retouch { //"dtl::retouch"名前空間に属する

/*#######################################################################################
	[概要] Multiplicationとは "Matrixの描画範囲を指定値で掛け算する" 機能を持つクラスである。
	[Summary] Multiplication is a class that multiplies the drawing range of Matrix.
#######################################################################################*/
		template<typename Matrix_Var_>
		class Multiplication : public ::dtl::range::RectBaseWithValue<Multiplication<Matrix_Var_>, Matrix_Var_>,
			public ::dtl::utility::DrawJagged<Multiplication<Matrix_Var_>, Matrix_Var_> {
		private:


			///// エイリアス (Alias) /////

			using Index_Size = ::dtl::type::size;
			using ShapeBase_t = ::dtl::range::RectBaseWithValue<Multiplication, Matrix_Var_>;
			using DrawBase_t = ::dtl::utility::DrawJagged<Multiplication, Matrix_Var_>;

			friend DrawBase_t;


			///// 基本処理 /////

			//STL
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				typename DTL_TYPE_ENABLE_IF<Matrix_::is_jagged::value, bool>::DTL_TYPE_EITYPE
				drawNormal(Matrix_&& matrix_, Args_&& ... args_) const noexcept {
				const Index_Size end_y_{ this->calcEndY(matrix_.getY()) };
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					const Index_Size end_x_{ this->calcEndX(matrix_.getX(row)) };
					for (Index_Size col{ this->start_x }; col < end_x_; ++col)
						matrix_.mul(col, row, this->draw_value, args_...);
				}
				return true;
			}

			//Normal
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				typename DTL_TYPE_ENABLE_IF<!Matrix_::is_jagged::value, bool>::DTL_TYPE_EITYPE
				drawNormal(Matrix_&& matrix_, Args_&& ... args_) const noexcept {
				const Index_Size end_x_{ this->calcEndX(matrix_.getX()) };
				const Index_Size end_y_{ this->calcEndY(matrix_.getY()) };
				for (Index_Size row{ this->start_y }; row < end_y_; ++row)
					for (Index_Size col{ this->start_x }; col < end_x_; ++col)
						matrix_.mul(col, row, this->draw_value, args_...);
				return true;
			}

		public:


			///// コンストラクタ (Constructor) /////

			using ShapeBase_t::ShapeBase_t;
		};
	}
}

#endif //Included Dungeon Template Library
