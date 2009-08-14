// Camera.hpp
// KlayGE 摄像机类 头文件
// Ver 2.0.0
// 版权所有(C) 龚敏敏, 2003
// Homepage: http://klayge.sourceforge.net
//
// 2.0.0
// 初次建立 (2003.5.31)
//
// 修改记录
//////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#pragma once

#ifndef KLAYGE_CORE_SOURCE
#define KLAYGE_LIB_NAME KlayGE_Core
#include <KlayGE/config/auto_link.hpp>
#endif

#include <KlayGE/Vector.hpp>
#include <KlayGE/Matrix.hpp>

namespace KlayGE
{
	// 3D摄像机操作
	//////////////////////////////////////////////////////////////////////////////////
	class KLAYGE_CORE_API Camera
	{
	public:
		float3 const & EyePos() const
			{ return eyePos_; }
		float3 const & LookAt() const
			{ return lookat_; }
		float3 const & UpVec() const
			{ return upVec_; }
		float3 const & ViewVec() const
			{ return viewVec_; }

		float FOV() const
			{ return FOV_; }
		float Aspect() const
			{ return aspect_; }
		float NearPlane() const
			{ return nearPlane_; }
		float FarPlane() const
			{ return farPlane_; }

		float4x4 const & ViewMatrix() const
			{ return this->viewMat_; }
		float4x4 const & ProjMatrix() const
			{ return this->projMat_; }

		void ViewParams(float3 const & eyePos, float3 const & lookat,
			float3 const & upVec = float3(0, 1, 0));
		void ProjParams(float FOV, float aspect, float nearPlane, float farPlane);

		void Update();

		float4x4 const & LastViewMatrix() const
		{
			return last_view_mat_;
		}

		Camera();

	private:
		float3		eyePos_;			// 观察矩阵的属性
		float3		lookat_;
		float3		upVec_;
		float3		viewVec_;
		float4x4	viewMat_;

		float		FOV_;			// 投射矩阵的属性
		float		aspect_;
		float		nearPlane_;
		float		farPlane_;
		float4x4	projMat_;

		float4x4	last_view_mat_;
	};
}

#endif		// _CAMERA_HPP
